#!/usr/bin/env bash
#
# Generate a blank spec file
#
# example:
#     bash newSpec.sh MyNewStyle
#
# A new file, `spec/MyNewStyle.txt` will be generated.   

NAME="../spec/$1.txt"

rm -f $NAME

for i in {1..6}; do
  for j in {1..8}; do
    echo "....." >> "$NAME"
  done
  if (($i != 6)); then
    echo >> "$NAME"
  fi	
done

echo "$NAME generated."
