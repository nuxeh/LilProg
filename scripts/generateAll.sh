#!/usr/bin/env bash

ALLSTYLES="../include/LilProgAllStyles.h"
rm -f $ALLSTYLES
echo "#ifndef __LILPROG_ALL_STYLES_H_" >> $ALLSTYLES
echo "#define __LILPROG_ALL_STYLES_H_" >> $ALLSTYLES
echo >> $ALLSTYLES

for f in ../spec/*.txt; do
  git add "$f"
  name=$(basename "$f" ".txt")
  output="../include/style${name}.h"
  cat "$f" | awk -f spec2bytes.awk -v styleName="$name"\
    > "$output"
  git add "$output"
  echo "#include \"style"$name".h\"" >> $ALLSTYLES
done	

echo >> $ALLSTYLES
echo "#endif" >> $ALLSTYLES
git add $ALLSTYLES
