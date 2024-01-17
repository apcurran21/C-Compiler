#!/bin/bash

# Fetch the inputs
if test $# -lt 3 ; then
  echo "USAGE: `basename $0` EXTENSION_FILE COMPILER TESTS_DIR" ;
  exit 1;
fi
extFile=$1 ;
compiler=$2 ;
testsDir=$3 ;

# Define the variables
origDir=`pwd` ;

# Check the tests directory
if ! test -d ${testsDir} ; then
  echo "The directory \"${testsDir}\" does not exist. Please create it and place your new tests there." ;
  exit 1 ;
fi

# Run the tests
cd ${testsDir} ; 
for i in *.${extFile} ; do

  # If the output already exists, skip the current test
  if test -f ${i}.out ; then
    continue ;
  fi
  echo "Generating the oracle for \"$i\"" ;

  # Generate the binary
  pushd ./ ;
  cd ${origDir} ;
  ./${compiler} ${testsDir}/${i} ;
  if test $? -ne 0 ; then
    echo "  Compilation error" ;

  else
    if test -f ${testsDir}/${i}.in ; then
      ./a.out < ${testsDir}/${i}.in &> ${testsDir}/${i}.out;
    else 
      ./a.out &> ${testsDir}/${i}.out ;
    fi
    if test $? -ne 0 ; then
      echo "  Runtime error" ;
      rm ${testsDir}/${i}.out ;
    fi
  fi
  popd ; 

  echo "" ;
done
