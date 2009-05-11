
/* Generated data (by glib-mkenums) */

/* -*- Mode: C; c-basic-offset: 4 -*-
 * python-hildon - Python bindings for the Hildon toolkit.
 *
 * hildon-types: definitions that should be in hildon
 *               itself but are not yet.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#include "hildondesktop-types.h"

/* enumerations from "/usr/include/libhildondesktop-1/libhildondesktop/hd-home-plugin-item.h" */

GType
h_dhome_plugin_item_resize_type_get_type (void)
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


/* enumerations from "/usr/include/libhildondesktop-1/libhildondesktop/hd-plugin-loader.h" */

GType
h_dplugin_loader_error_code_get_type (void)
{
    static GType etype = 0;
    if (etype == 0) {
        static const GEnumValue values[] = {
            { HD_PLUGIN_LOADER_ERROR_UNKNOWN, "HD_PLUGIN_LOADER_ERROR_UNKNOWN", "unknown" },
            { HD_PLUGIN_LOADER_ERROR_OPEN, "HD_PLUGIN_LOADER_ERROR_OPEN", "open" },
            { HD_PLUGIN_LOADER_ERROR_SYMBOL, "HD_PLUGIN_LOADER_ERROR_SYMBOL", "symbol" },
            { HD_PLUGIN_LOADER_ERROR_INIT, "HD_PLUGIN_LOADER_ERROR_INIT", "init" },
            { HD_PLUGIN_LOADER_ERROR_KEYFILE, "HD_PLUGIN_LOADER_ERROR_KEYFILE", "keyfile" },
            { HD_PLUGIN_LOADER_ERROR_UNKNOWN_TYPE, "HD_PLUGIN_LOADER_ERROR_UNKNOWN_TYPE", "unknown-type" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static ("HDPluginLoaderErrorCode", values);
    }
    return etype;
}


/* enumerations from "/usr/include/glib-2.0/glib/gdate.h" */

GType
g_date_dmy_get_type (void)
{
    static GType etype = 0;
    if (etype == 0) {
        static const GEnumValue values[] = {
            { G_DATE_DAY, "G_DATE_DAY", "day" },
            { G_DATE_MONTH, "G_DATE_MONTH", "month" },
            { G_DATE_YEAR, "G_DATE_YEAR", "year" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static ("GDateDMY", values);
    }
    return etype;
}

GType
g_date_weekday_get_type (void)
{
    static GType etype = 0;
    if (etype == 0) {
        static const GEnumValue values[] = {
            { G_DATE_BAD_WEEKDAY, "G_DATE_BAD_WEEKDAY", "bad-weekday" },
            { G_DATE_MONDAY, "G_DATE_MONDAY", "monday" },
            { G_DATE_TUESDAY, "G_DATE_TUESDAY", "tuesday" },
            { G_DATE_WEDNESDAY, "G_DATE_WEDNESDAY", "wednesday" },
            { G_DATE_THURSDAY, "G_DATE_THURSDAY", "thursday" },
            { G_DATE_FRIDAY, "G_DATE_FRIDAY", "friday" },
            { G_DATE_SATURDAY, "G_DATE_SATURDAY", "saturday" },
            { G_DATE_SUNDAY, "G_DATE_SUNDAY", "sunday" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static ("GDateWeekday", values);
    }
    return etype;
}

GType
g_date_month_get_type (void)
{
    static GType etype = 0;
    if (etype == 0) {
        static const GEnumValue values[] = {
            { G_DATE_BAD_MONTH, "G_DATE_BAD_MONTH", "bad-month" },
            { G_DATE_JANUARY, "G_DATE_JANUARY", "january" },
            { G_DATE_FEBRUARY, "G_DATE_FEBRUARY", "february" },
            { G_DATE_MARCH, "G_DATE_MARCH", "march" },
            { G_DATE_APRIL, "G_DATE_APRIL", "april" },
            { G_DATE_MAY, "G_DATE_MAY", "may" },
            { G_DATE_JUNE, "G_DATE_JUNE", "june" },
            { G_DATE_JULY, "G_DATE_JULY", "july" },
            { G_DATE_AUGUST, "G_DATE_AUGUST", "august" },
            { G_DATE_SEPTEMBER, "G_DATE_SEPTEMBER", "september" },
            { G_DATE_OCTOBER, "G_DATE_OCTOBER", "october" },
            { G_DATE_NOVEMBER, "G_DATE_NOVEMBER", "november" },
            { G_DATE_DECEMBER, "G_DATE_DECEMBER", "december" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static ("GDateMonth", values);
    }
    return etype;
}


/* Generated data ends here */

