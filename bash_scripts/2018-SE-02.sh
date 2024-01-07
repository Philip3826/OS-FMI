#!/bin/bash
# Not working properly, needs some work with the seperators in the second loop
[ $# -eq 2 ] || exit 1
[ -f $1 ] || exit 2
[ -d $2 ] || exit 3

touch $2/dict.txt
count=1
while read name ; do
        touch $2/$count.txt
        echo "$name:$count" >> $2/dict.txt
        ((count++))
done< <(sed 's/([^)]*)//g' $1 | awk -F ":" '{print $1}' | sed 's/[[:space:]]*$//' | sort | uniq)

while read name quote ; do
        num=$(egrep "$name" $2/dict.txt | awk -F ":" '{print $2}')
        echo "$quote" >> $2/$num.txt
done< <(sed 's/([^)]*)//g' $1)