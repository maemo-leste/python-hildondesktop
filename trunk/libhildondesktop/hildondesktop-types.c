
/* Generated data (by glib-mkenums) */

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

#include "hildondesktop-types.h"

/* enumerations from "/usr/include/libhildondesktop-1/libhildondesktop/hd-home-plugin-item.h" */

GType
hd_home_plugin_item_resize_type_get_type (void)
{
    static GType etype = 0;
    if (etype == 0) {
        static const GEnumValue values[] = {
            { HD_HOME_PLUGIN_ITEM_RESIZE_NONE, "HD_HOME_PLUGIN_ITEM_RESIZE_NONE", "none" },
            { HD_HOME_PLUGIN_ITEM_RESIZE_VERTICAL, "HD_HOME_PLUGIN_ITEM_RESIZE_VERTICAL", "vertical" },
            { HD_HOME_PLUGIN_ITEM_RESIZE_HORIZONTAL, "HD_HOME_PLUGIN_ITEM_RESIZE_HORIZONTAL", "horizontal" },
            { HD_HOME_PLUGIN_ITEM_RESIZE_BOTH, "HD_HOME_PLUGIN_ITEM_RESIZE_BOTH", "both" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static ("HDHomePluginItemResizeType", values);
    }
    return etype;
}


/* Generated data ends here */

