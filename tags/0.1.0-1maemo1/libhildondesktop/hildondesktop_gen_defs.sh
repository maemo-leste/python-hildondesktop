#!/bin/bash
# Generates .defs and helper .c/.h files for hildondesktop
# Author: Anderson Lizardo <anderson.lizardo@indt.org.br>
set -e

codegen_dir="$(pkg-config --variable=codegendir pygtk-2.0)"

includedir=/usr/include/libhildondesktop-1/libhildondesktop
headers="$includedir/hd-home-plugin-item.h \
	$includedir/hd-status-plugin-item.h \
	$includedir/hd-status-menu-item.h"

echo Creating hildondesktop.defs...
python $codegen_dir/h2def.py $headers > hildondesktop.defs

cat >> hildondesktop.defs << "EOF"

; ugly hack to force new constructor API usage
; (hd_home_plugin_new does not exist)
(define-function hd_home_plugin_new
  (c-name "hd_home_plugin_new")
  (is-constructor-of "HDHomePluginItem")
  (return-type "GtkWidget*")
  (properties
    '("type" (optional))
  )
)
EOF

# Apply some transformations to the generated .defs
# fix object name parsed by codegen (seems to affect only HildonDesktop bindings)
function fix_object_name()
{
	defs_file=$1
	prefix=$2
	module=$3
	sed -i.bak "/^(define-object /{N;s/(define-object \(.*\n  (in-module \"\)$prefix\([^\"]\+\)/(define-object \2\1$module/g}" $defs_file
	diff -u $defs_file.bak $defs_file && echo "WARNING: $defs_file is unchanged" || true
	rm $defs_file.bak
}
# fix gtype-id definitions
function fix_gtype_id()
{
	defs_file=$1
	prefix_old=$2
	prefix_new=$3
	sed -i.bak "s/^  (gtype-id \"$prefix_old/  (gtype-id \"$prefix_new/g" $defs_file
	diff -u $defs_file.bak $defs_file && echo "WARNING: $defs_file is unchanged" || true
	rm $defs_file.bak
}

fix_object_name hildondesktop.defs HD HildonDesktop
fix_gtype_id hildondesktop.defs H_TYPE_D_ HD_TYPE_

echo Generating hildondesktop-types.c and hildondesktop-types.h...
glib-mkenums --template hildondesktop-types-template.h $headers > hildondesktop-types.h
glib-mkenums --template hildondesktop-types-template.c $headers > hildondesktop-types.c

# unfortunately, glib-mkenums also seems to parse hildon-desktop headers incorrectly...
# probably due to non-conforming naming scheme
function fix_types_prefix()
{
	file=$1
	prefix_old=$2
	prefix_new=$3
	prefix2_old=$4
	prefix2_new=$5
	sed -i.bak -e "s/^#define $prefix_old/#define $prefix_new/g" \
		   -e "s/$prefix2_old/$prefix2_new/g" $file
	diff -u $file.bak $file && echo "WARNING: $file is unchanged" || true
	rm $file.bak
}

fix_types_prefix hildondesktop-types.h H_TYPE_D HD_TYPE_ h_d hd_
fix_types_prefix hildondesktop-types.c H_TYPE_D HD_TYPE_ h_d hd_
