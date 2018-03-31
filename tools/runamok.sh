#!/usr/bin/env bash

start=$(free -m)
for i in {1..1000}
do
  echo $i
  ../build/space_freighter | echo > /dev/null
done
echo "${start}"
echo
free -m

