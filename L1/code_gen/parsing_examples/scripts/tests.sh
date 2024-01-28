#!/bin/bash

function generateTests {

  # Fetch the inputs
  srcLang=$1 ;
  echo "Considering $srcLang" ;

  # Go the to compiler directory
  pushd ./ &> /dev/null ;
  cd $srcLang ;

  # Generate the oracle of the new tests
  make test ;
  echo "" ;

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
