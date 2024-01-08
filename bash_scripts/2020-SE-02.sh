#!/bin/bash

[ $# -eq 1 ] || exit 1
[ -f $1 ] || exit 2

for site in $(awk -F " " '{print $2}' $1 | uniq -c | sort -k1,1n | tail -n 3 | awk '{print $2}'); do
        echo "$site HTTP/2.0: $(egrep  $site $1 | egrep -c "HTTP/2.0") non-HTTP/2.0: $(egrep $site $1 | egrep -c -v "HTTP/2.0")"
        echo "$(egrep $site $1 | awk -F " " '$6 > 302 {print $1}' | uniq -c | sort -k1,1n | head -n 5)"
done
