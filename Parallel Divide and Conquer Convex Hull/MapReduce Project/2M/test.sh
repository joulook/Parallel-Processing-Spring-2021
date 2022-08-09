#!/bin/bash

for f in out*; do
java MapReduce "$f" "2000000"
done
