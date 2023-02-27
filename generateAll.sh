#!/usr/bin/env bash

for f in spec/*.txt; do
  name=$(basename "$f" ".txt")
  cat "$f" | awk -f spec2bytes.awk -v styleName="$name"\
    > include/style"$name".h
done	
