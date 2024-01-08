#!/bin/bash

[ $# -ge 1 ] || exit 1
N=10
if [ $1 == "-n" ]; then
        [ $# -ge 2 ] || exit 2
        N=$2
        shift 2
fi
T=$(mktemp)
for file in $@; do
        idf=$(basename -s .log $file)
        tail -n $N  $file | sed -E "s/^(.{19}) (.*)$/\1 $idf \2/" >> $T
done

cat $T | sort -k1,2
rm -r $T
