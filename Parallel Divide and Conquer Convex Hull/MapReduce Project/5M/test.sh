#!/bin/bash

for f in out*; do
java MapReduce "$f" "5000000"
done
