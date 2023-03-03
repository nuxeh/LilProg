#!/usr/bin/env bash

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
