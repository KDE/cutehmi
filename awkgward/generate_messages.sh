#!/bin/sh

# Script that generates Messages.sh, which is a part of KDE translation process.

separator="-"
prefix="cutehmi"$separator
suffix="_qt"
subdir=""
tag_file="l10n-kf5.tag"

usage()
{
	echo "usage: $0 cutehmi_dir [subdir] [prefix] [suffix] [separator]"
	echo "default subdir: $subdir"
	echo "default prefix: $prefix"
	echo "default suffix: $suffix"
	echo "default separator: $separator"
}

if [ $# -lt 1 ]; then
	echo "error: too few arguments"
	usage
	exit 1
fi

cutehmi_dir=$1

if [ $# -gt 1 ]; then
	subdir=$2
fi

if [ $# -gt 2 ]; then
	prefix=$3
fi

if [ $# -gt 3 ]; then
	suffix=$4
fi

if [ $# -gt 4 ]; then
	separator=$5
fi

extensions=`find $cutehmi_dir/$subdir -name $tag_file -exec dirname {} \;`
cutehmi_path=`readlink -f $cutehmi_dir`
messages_path=$cutehmi_path/$messages_file

for extension in $extensions
do
	extension_path=`readlink -f $extension`
	# Appending trailing slash to cutehmi_path removes also leading slash.
	stripped_path=${extension_path#$cutehmi_path\/}
	translation_file=$prefix`echo $stripped_path | sed 's|[./]|'$separator'|g'`$suffix.pot
	echo \$EXTRACT_TR_STRINGS \`find ./$stripped_path -name \\*.qml -o -name \\*.cpp -o -name \\*.hpp\` -I ./$stripped_path/include -o \$podir/$translation_file
done

