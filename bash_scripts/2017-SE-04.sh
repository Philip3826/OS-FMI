#!/bin/bash

[ $# -ge 1 ] || exit 1
[ $# -lt 3 ] || exit 2
[ -d "$1" ] || exit 3

filename=""
if [ $# -eq 2 ]; then
        [ -f "$2" ] || exit 4
        filename=$2
fi


if [ -z $filename ]; then
        find $1 -type l -printf "%p %Y %l\n" | awk '$2 == "N" {count++} $2 != "N" && $3 != "" {print $1,"->",$3} END {print "Broken Symlinks:",count}'
else
        find $1 -type l -printf "%p %Y %l\n" | awk '$2 == "N" {count++} $2 != "N" && $3 != "" {print $1,"->",$3} END {print "Broken Symlinks:",count}' > $filename
fi
