/*
 * This file is part of python-hildondesktop
 *
 * Copyright (C) 2006 Nokia Corporation.
 *
 * Author:  Lucas Rocha <lucas.rocha@nokia.com>
 * Contact: Karoliina Salminen <karoliina.t.salminen@nokia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <Python.h>
#include <pygobject.h>
#include <pygtk/pygtk.h>

#include <libhildondesktop/libhildondesktop.h>

#include "hd-plugin-loader-python.h"

#define HD_PLUGIN_LOADER_PYTHON_GET_PRIVATE(obj) \
        (G_TYPE_INSTANCE_GET_PRIVATE ((obj), HD_TYPE_PLUGIN_LOADER_PYTHON, HDPluginLoaderPythonPrivate))

G_DEFINE_TYPE (HDPluginLoaderPython, hd_plugin_loader_python, HD_TYPE_PLUGIN_LOADER);

struct _HDPluginLoaderPythonPrivate
{
  gboolean initialised;
};

static void
hd_plugin_loader_python_destroy_plugin (GtkObject *object, gpointer user_data)
{
  PyObject *pModule, *pObject;

  pObject = (PyObject *) g_object_get_data (G_OBJECT (object), "object");
  pModule = (PyObject *) g_object_get_data (G_OBJECT (object), "module");

  Py_DECREF (pObject);
  Py_DECREF (pModule);

  PyGC_Collect();
}

static PyObject *
hd_plugin_loader_python_import_module (gchar *module_name)
{
  PyObject *pModules, *pModule, *pReload;

  pModules = PyImport_GetModuleDict ();

  g_assert (pModules != NULL);

  pModule = PyDict_GetItemString (pModules, module_name);

  if (pModule == NULL)
  {
    pModule = PyImport_ImportModule (module_name);

    if (pModule == NULL)
    {
      PyErr_Print ();
      PyErr_Clear ();

      g_warning ("Could not initialize Python module '%s'", module_name);
    }
  }
  else
  {
    pReload = PyImport_ReloadModule (pModule);

    if (pReload == NULL)
    {
      PyErr_Print ();
      PyErr_Clear ();

      g_warning ("Could not reload Python module '%s'\n"
                 "Falling back to previous version",
                 module_name);

      Py_INCREF (pModule);
    }
  }

  return pModule;
}

/* Based on gobject.type_register() and gobject.new() implementations from pygobject */
static GObject *
hd_plugin_loader_python_create_object (PyObject    *pClass,
                                       const gchar *plugin_id)
{
  GObject *object = NULL;

  PyObject *pModule = PyImport_ImportModule ("gobject");
  if (pModule != NULL)
  {
    PyObject *pDict = PyModule_GetDict (pModule);
    PyObject *register_func = PyDict_GetItemString (pDict, "type_register");
    PyObject *new_func = PyDict_GetItemString (pDict, "new");
    if (register_func != NULL && new_func != NULL)
    {
      PyObject *pRes = PyObject_CallFunctionObjArgs (register_func, pClass, NULL);
      if (pRes != NULL)
      {
        Py_DECREF (pRes);
        PyObject *args = Py_BuildValue ("(O)", pClass);
        PyObject *kwargs = Py_BuildValue ("{ss}", "plugin_id", plugin_id);
        PyObject *pObject = PyObject_Call (new_func, args, kwargs);
        Py_DECREF (args);
        Py_DECREF (kwargs);
        if (pObject != NULL)
        {
          object = g_object_ref (((PyGObject *) pObject)->obj);
          g_object_set_data (object, "object", pObject);
        }
        else
        {
          PyErr_Print ();
          PyErr_Clear ();
          g_warning ("Could not create new plugin object");
        }
      }
      else
      {
        PyErr_Print ();
        PyErr_Clear ();
        g_warning ("Could not register type for plugin object");
      }
    }
    else
    {
      PyErr_Print ();
      PyErr_Clear ();
      g_warning ("Could not import functions from gobject");
    }
  }
  else
  {
    PyErr_Print ();
    PyErr_Clear ();
    g_warning ("Could not import gobject");
  }

  return object;
}

static GObject *
hd_plugin_loader_python_open_module (HDPluginLoaderPython  *loader,
                                     const gchar           *plugin_id,
                                     GKeyFile              *keyfile,
                                     GError               **error)
{
  HDPluginLoaderPythonPrivate *priv;
  PyObject *pModule, *pDict;
  GObject *object = NULL;
  GError *keyfile_error = NULL;
  gchar *module_file = NULL;
  gchar *module_name = NULL;

  g_return_val_if_fail (HD_IS_PLUGIN_LOADER_PYTHON (loader), NULL);

  priv = loader->priv;

  module_file = g_key_file_get_string (keyfile,
                                       "Desktop Entry",
                                       "X-Path",
                                       &keyfile_error);
  g_strstrip (module_file);

  if (keyfile_error)
  {
    g_propagate_error (error, keyfile_error);

    return NULL;
  }

  /* Strip directory component from absolute paths */
  if (g_path_is_absolute (module_file))
  {
    module_name = g_path_get_basename (module_file);

    g_free (module_file);
  }
  else
  {
    module_name = module_file;
  }

  /* Strip extension from module_name */
  if (g_str_has_suffix (module_name, ".py"))
  {
    gchar *tmp = g_strndup (module_name, strlen (module_name) - 3);
    g_free (module_name);
    module_name = tmp;
  }

  pModule = hd_plugin_loader_python_import_module (module_name);

  if (pModule != NULL)
  {
    pDict = PyModule_GetDict (pModule);
    PyObject *pType = PyDict_GetItemString (pDict, "hd_plugin_type");
    if (pType != NULL)
    {
      object = hd_plugin_loader_python_create_object (pType, plugin_id);
      if (object != NULL)
      {
        g_object_set_data (object, "module", pModule);
        g_signal_connect (G_OBJECT (object),
                          "destroy",
                          G_CALLBACK (hd_plugin_loader_python_destroy_plugin),
                          NULL);
      }
      else
      {
        Py_DECREF (pModule);
        if (PyErr_Occurred ())
        {
          PyErr_Print ();
          PyErr_Clear ();
        }
        g_set_error (error,
                     hd_plugin_loader_error_quark (),
                     HD_PLUGIN_LOADER_ERROR_KEYFILE,
                     "Could not create plugin object in Python module '%s'", module_name);
      }
    }
    else
    {
      Py_DECREF (pModule);
      if (PyErr_Occurred ())
      {
        PyErr_Print ();
        PyErr_Clear ();
      }
      g_set_error (error,
                   hd_plugin_loader_error_quark (),
                   HD_PLUGIN_LOADER_ERROR_KEYFILE,
                   "Could not find \"hd_plugin_type\" in Python module '%s'", module_name);
    }
  }

  g_free (module_name);

  return object;
}

static GObject *
hd_plugin_loader_python_load (HDPluginLoader *loader,
                              const gchar    *plugin_id,
                              GKeyFile       *keyfile,
                              GError         **error)
{
  GObject *object = NULL;
  GError *local_error = NULL;

  g_return_val_if_fail (loader, NULL);

  if (!keyfile)
  {
    g_set_error (error,
                 hd_plugin_loader_error_quark (),
                 HD_PLUGIN_LOADER_ERROR_KEYFILE,
                 "A keyfile required to load plugins");

    return NULL;
  }

  /* Open the module and return plugin instance */
  object =
     hd_plugin_loader_python_open_module (HD_PLUGIN_LOADER_PYTHON (loader),
                                          plugin_id,
                                          keyfile,
                                          &local_error);

  if (local_error)
  {
    g_propagate_error (error, local_error);

    return NULL;
  }

  return object;
}

static void
hd_plugin_loader_python_finalize (GObject *loader)
{
  HDPluginLoaderPythonPrivate *priv;

  g_return_if_fail (loader != NULL);
  g_return_if_fail (HD_IS_PLUGIN_LOADER_PYTHON (loader));

  priv = HD_PLUGIN_LOADER_PYTHON (loader)->priv;

  if (priv->initialised)
  {
    Py_Finalize ();
  }

  G_OBJECT_CLASS (hd_plugin_loader_python_parent_class)->finalize (loader);
}

static void
hd_plugin_loader_python_init (HDPluginLoaderPython *loader)
{
  PyObject *pPath, *pStr;

  loader->priv = HD_PLUGIN_LOADER_PYTHON_GET_PRIVATE (loader);

  Py_Initialize ();
  loader->priv->initialised = TRUE;

  init_pygobject ();
  init_pygtk ();

  pStr = PyString_FromString (HD_DESKTOP_MODULE_PATH);
  pPath = PySys_GetObject ("path");
  PyList_Append (pPath, pStr);
}

static void
hd_plugin_loader_python_class_init (HDPluginLoaderPythonClass *class)
{
  GObjectClass *object_class;
  HDPluginLoaderClass *loader_class;

  object_class = G_OBJECT_CLASS (class);
  loader_class = HD_PLUGIN_LOADER_CLASS (class);

  object_class->finalize = hd_plugin_loader_python_finalize;

  loader_class->load = hd_plugin_loader_python_load;

  g_type_class_add_private (object_class, sizeof (HDPluginLoaderPythonPrivate));
}

G_MODULE_EXPORT gchar *
hd_plugin_loader_module_type (void)
{
  return "python"; /* FIXME: clean me up */
}

G_MODULE_EXPORT HDPluginLoader *
hd_plugin_loader_module_get_instance (void)
{
  return g_object_new (HD_TYPE_PLUGIN_LOADER_PYTHON, NULL);
}
