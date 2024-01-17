#!/bin/bash

function generateTests {

  # Fetch the inputs
  srcLang=$1 ;
  echo "Considering $srcLang" ;

  # Go the to compiler directory
  pushd ./ &> /dev/null ;
  cd $srcLang ;

  # Generate the oracle of the new tests
  make oracle_new ;

  # Move the new tests
  cd tests/new ;
  for i in `ls` ; do
    if ! test $i ../$i ; then
      mv $i ../ ;
    fi
  done
 
  # Leave
  popd &> /dev/null ;
  return ;
}

generateTests "LC" ;
generateTests "LB" ;
generateTests "LA" ;
generateTests "IR" ;
generateTests "L3" ;
generateTests "L2" ;
generateTests "L1" ;
