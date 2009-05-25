/*** BEGIN file-header ***/
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
/*** END file-header ***/
/*** BEGIN file-production ***/

/* enumerations from "@filename@" */

/*** END file-production ***/
/*** BEGIN value-header ***/
GType
@enum_name@_get_type (void)
{
    static GType etype = 0;
    if (etype == 0) {
        static const G@Type@Value values[] = {
/*** END value-header ***/
/*** BEGIN value-production ***/
            { @VALUENAME@, "@VALUENAME@", "@valuenick@" },
/*** END value-production ***/
/*** BEGIN value-tail ***/
            { 0, NULL, NULL }
        };
        etype = g_@type@_register_static ("@EnumName@", values);
    }
    return etype;
}

/*** END value-tail ***/
