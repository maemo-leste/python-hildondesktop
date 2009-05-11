#!/bin/bash
# Generates .defs and helper .c/.h files from installed -dev packages
# Author: Anderson Lizardo <anderson.lizardo@indt.org.br>
set -e

dev_packages="libhildondesktop1-dev"
#dev_packages="libhildon1-dev libhildonfm2-dev"
codegen_dir="$(pkg-config --variable=codegendir pygtk-2.0)"
#codegen_dir=$HOME/workspace/pygtk/pygtk-2.12.1-codegen
# contains some enums used in HildonWeekdayPicker
extra_headers="/usr/include/glib-2.0/glib/gdate.h"

mkdir -p defs

headers=""
for p in $dev_packages; do
	# Exclude hildon-fm.h due to MB#4450
	headers="$(dpkg -L $p | grep '\.h$' | grep -v 'hildon/hildon-fm\.h$') $headers"
done

echo Parsing .h files and creating .defs...
# Create empty hildon-includes.h (or empty existing one)
> hildondesktop-includes.h
for h in $headers; do
	$codegen_dir/h2def.py $h > defs/$(basename $h .h).defs
	echo "#include \"$h\"" >> hildondesktop-includes.h
done
$codegen_dir/createdefs.py hildondesktop.defs defs/*.defs

echo Generating hildondesktop-types.c and hildondesktop-types.h...
glib-mkenums --template hildondesktop-types-template.h $headers $extra_headers > hildondesktop-types.h
glib-mkenums --template hildondesktop-types-template.c $headers $extra_headers > hildondesktop-types.c
