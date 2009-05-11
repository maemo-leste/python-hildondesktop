/*** BEGIN file-header ***/
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
