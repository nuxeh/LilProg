#!/usr/bin/env bash

ALLSTYLES="../include/LilProgAllStyles.h"
rm -f $ALLSTYLES
echo "#ifndef __LILPROG_ALL_STYLES_H_" >> $ALLSTYLES
echo "#define __LILPROG_ALL_STYLES_H_" >> $ALLSTYLES
echo >> $ALLSTYLES

for f in ../spec/*.txt; do
  name=$(basename "$f" ".txt")
  cat "$f" | awk -f spec2bytes.awk -v styleName="$name"\
    > ../include/style"$name".h
  echo "#include \"style"$name".h\"" >> $ALLSTYLES
done	

echo >> $ALLSTYLES
echo "#endif" >> $ALLSTYLES
