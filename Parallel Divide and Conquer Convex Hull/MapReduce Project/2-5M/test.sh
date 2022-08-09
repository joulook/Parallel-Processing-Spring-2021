#!/bin/bash

for f in out*; do
java MapReduce "$f" "2500000"
done
