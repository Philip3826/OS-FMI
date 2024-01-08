#!/bin/bash

[ $# -eq 2 ] || exit 1
[ -f $1 ] || exit 2


sort -t ',' -k2 -k1,1n $1 | sed -E 's/,/\t/g' | uniq -f 1 | sed -E 's/\t/,/g' > $2