#!/bin/bash

function anonymize_tests {

  # Fetch the inputs
  local targetLang=$1 ;
  local langSuffix=$2 ;

  # Anonymize the tests of the target language
  echo "  Anonymize the tests (.$langSuffix) of $targetLang" ;
  pushd ./ &> /dev/null ;
  cd ${targetLang}/tests ;
  num=0 ;
  for currentTest in *.${langSuffix} ; do

    # Check if the current test has an oracle
    if ! test -f ${currentTest}.out ; then
      continue ;
    fi

    # The current test needs to be considered
    # - Check its name
    if [[ "$currentTest" =~ ^test[0-9]+.${langSuffix} ]] ; then
      continue ;
    fi

    # - We found a test that doesn't match the pattern
    # - Find a new name for the test
    while true ; do
      testName="test${num}.${langSuffix}" ;
      if ! test -f $testName ; then
        break ;
      fi
      let num=$num+1 ;
    done

    # - Rename the test
    echo "    Rename $currentTest to test${num}.${langSuffix}";
    mv ${currentTest} "test${num}.${langSuffix}" ;
    mv ${currentTest}.out "test${num}.${langSuffix}.out" ;
    if test -f ${currentTest}.in ; then
      mv ${currentTest}.in "test${num}.${langSuffix}.in" ;
    fi
  done

  popd &> /dev/null ;
  echo "" ;

  return ;
}

anonymize_tests "L1" "L1";
anonymize_tests "L2" "L2";
anonymize_tests "L3" "L3";
anonymize_tests "IR" "IR";
anonymize_tests "LA" "a";
anonymize_tests "LB" "b";
anonymize_tests "LC" "c";
anonymize_tests "LD" "d";
