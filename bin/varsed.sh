#!/bin/bash
for i in $@
  do
  if [ "$i" == "$1" ]
    then
    :
  else
    echo $i >> /tmp/varsed
  fi
done
sed -i $1 /tmp/varsed
cat /tmp/varsed
rm -f /tmp/varsed
