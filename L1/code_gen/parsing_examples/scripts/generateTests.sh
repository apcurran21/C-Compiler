#!/bin/bash

function generateTests {

  # Fetch the inputs
  srcLang=$1 ;
  dstLang=$2 ;
  echo "Considering $srcLang" ;

  # Go the to compiler directory
  pushd ./ &> /dev/null ;
  cd $srcLang ;

  # Generate the tests
  added="0" ;
  cd tests ; 
  num=0 ;
  for i in *.${srcLang} ; do

    # If the output already exists, skip the current test
    if ! test -f ${i}.out ; then
      continue ;
    fi

    # Iterate over the optimization levels
    for optNumber in `seq 0 3` ; do
      optLevel="-O${optNumber}" ;

      # Generate the target language
      pushd ./ &> /dev/null ;
      cd ../ ;
      ./${srcLang}c ${optLevel} tests/${i} ;
      if test $? -ne 0 ; then
        popd &> /dev/null ; 
        continue ;
      fi
      inputFile="" ;
      if test -f tests/${i}.in ; then
        inputFile="`pwd`/tests/${i}.in" ;
        ./a.out < ${inputFile} &> tests/${i}.out.tmp ;
      else
        ./a.out &> tests/${i}.out.tmp ;
      fi
      cmp tests/${i}.out.tmp tests/${i}.out ;
      if test $? -ne 0 ; then
        popd &> /dev/null ; 
        continue ;
      fi
      echo "  Considering the test $i " ;

      # Check that the current file does not exist already in the tests of the compiler below
      found="0" ;
      pushd ./ &> /dev/null ;
      cd ../$dstLang/tests ;
      for j in *.${dstLang} ; do

        # Check if the current generated test for the target language is the same as the current target-language-test @prog
        cmp $j ../../${srcLang}/prog.${dstLang} &> /dev/null ;
        if test $? -eq 0 ; then

          # They are the same test.
          # So, there is no reason to generate a new test
          found="1" ;
          break ;
        fi
      done
      if test $found == "0" ; then

        # Find a unique name
        while true ; do
          testName="test${num}.${dstLang}" ;
          if ! test -f $testName ; then
            break ;
          fi
          let num=$num+1 ;
        done
        echo "    Add a new test named $testName" ;
        cp ../../${srcLang}/prog.${dstLang} $testName ;
        if test "$inputFile" != "" ; then
          cp $inputFile ./${testName}.in ;
        fi
        added="1" ;
      fi

      popd &> /dev/null ; 
      popd &> /dev/null ; 
    done
  done
  popd &> /dev/null ; 

  # Generate the oracles
  if test $added == "1" ; then
    echo "  Generate the oracles for the new tests added to $dstLang" ;
    pushd ./ &> /dev/null ;
    cd $dstLang ;
    make oracle ;
    popd &> /dev/null ;
  fi

  return ;
}

function generateLivenessTests {
  pushd ./ &> /dev/null ;

  # Prepare the directory
  cd L2/tests ;
  mkdir -p liveness ;

  # Initialize the variables
  let testNum=0;
  let added="0" ;

  # Consider all L2 tests
  for i in *.L2 ; do

    # If the output already exists, skip the current test
    if ! test -f ${i}.out ; then
      continue ;
    fi
    pushd ./ &> /dev/null ;
    echo "Generate liveness tests for $i" ;
    
    # Generate liveness tests for this L2 program
    cd liveness ;
    let tmpNumber=0;
    while true ; do

      # Find the next free number
      while true ; do
        if ! test -e test${testNum}.L2f ; then
          break ;
        fi
        let testNum=$testNum+1; 
      done

      # Generate the next test
      echo "  Function $tmpNumber" ;
      ../../bin/L2 -f $tmpNumber ../${i} > test${testNum}.L2f 

      # Check the test so-generated
      linesNum=`wc -l test${testNum}.L2f | awk '{print $1}'`
      if test "$linesNum" == "0" ; then

        # We finished all functions of the current L2 program
        echo "    No more functions exist" ;
        rm test${testNum}.L2f ;
        break ;
      fi
      testFound="1" ;
      for j in *.L2f ; do
        if test $j == test${testNum}.L2f ; then
          continue ;
        fi
        cmp $j test${testNum}.L2f &> /dev/null ;
        if test $? -eq 0 ; then

          # This test was already generated
          testFound="0" ;
          break ;
        fi
      done
      if test $testFound == "0" ; then
        let tmpNumber=$tmpNumber+1 ;
        rm test${testNum}.L2f ;
        continue ;
      fi
      
      # We generated a new test for liveness
      echo "  Generate `pwd`/test${testNum}.L2f" ;
      added="1" ;

      let tmpNumber=$tmpNumber+1 ;
    done

    popd &> /dev/null ; 
  done
  popd &> /dev/null ; 

  # Generate the oracles
  if test $added == "1" ; then
    echo "  Generate the oracles for liveness for the new tests added to L2" ;
    pushd ./ &> /dev/null ;
    cd L2 ;
    make oracle_liveness ;
    popd &> /dev/null ;
  fi

  return ;
}

function generateInterferenceTests {
  pushd ./ &> /dev/null ;

  # Prepare the directory
  cd L2/tests ;
  mkdir -p interference ;

  # Copy the files
  cd interference ;
  cp ../liveness/*.L2f ./ ;
  popd &> /dev/null ;

  # Generate the oracles
  echo "  Generate the oracles for interference for the new tests added to L2" ;
  pushd ./ &> /dev/null ;
  cd L2 ;
  make oracle_interference;
  popd &> /dev/null ;

  return ;
}

# Generate tests for all languages
generateTests "LC" "LB" ;
generateTests "LB" "LA" ;
generateTests "LA" "IR" ;
generateTests "IR" "L3" ;
generateTests "L3" "L2" ;
generateTests "L2" "L1" ;

# Generate tests for liveness
generateLivenessTests ;

# Generate tests for interference
generateInterferenceTests ;
