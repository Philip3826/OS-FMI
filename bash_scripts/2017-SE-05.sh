#!/bin/bash

[ $# -eq 2 ] || exit 1
[ -d $1 ] || exit 2


find $1 -maxdepth 1 -type f | xargs -n 1 basename | awk -F "-" -v core=$2 '$1 == "vmlinuz" && $2 ~ /^[0-9]+\.[0-9]+\.[0-9]+$/ && $3==core {print}' | sed -E 's/\./-/g' | sort -t '-' -k 2,2n -k 3,3n -k 4,4n | tail -n 1 | awk -F "-" '{print $1"-"$2"."$3"."$4"-"$5}'