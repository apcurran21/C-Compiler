#!/bin/bash

# Initialize counters
passed=0
failed=0

# Batch processing parameters
START=${1:-0}   # Default to 0 if no start argument is provided
COUNT=${2:-100} # Default to 100 if no count argument is provided
current=0       # Current test counter

# Navigate to the test directory
cd tests/liveness

# Process each test file
for i in *.L2f ; do
  # Only process tests within the specified range
  if [ $current -lt $START ]; then
    ((current++))
    continue
  fi
  if [ $current -ge $(($START + $COUNT)) ]; then
    break
  fi

  # If the output already exists, skip the current test
  if ! test -f ${i}.out ; then
    ((current++))
    continue
  fi
  echo $i

  # Generate the binary
  pushd ./ > /dev/null
  cd ../../
  ./liveness tests/liveness/${i} &> tests/liveness/${i}.out.tmp
  cmp tests/liveness/${i}.out.tmp tests/liveness/${i}.out
  if ! test $? -eq 0 ; then
    echo "  Failed"
    ((failed++))
  else
    echo "  Passed"
    ((passed++))
  fi
  popd > /dev/null
  ((current++))
done

let total=passed+failed

echo "########## SUMMARY"
echo "Test passed: $passed out of $total"
