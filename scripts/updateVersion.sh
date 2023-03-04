#!/usr/bin/env bash

FROM=$1
TO=$2

sed -i "s/${FROM}/${TO}/" ../library.json
git add ../library.json
git commit -m "Bump v${FROM} → v${TO}" && git tag "v${TO}"
