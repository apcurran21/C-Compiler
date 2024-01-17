#!/bin/bash

if test $# -lt 2 ; then
  echo "USAGE: `basename $0` EXTENSION_FILE COMPILER" ;
  exit 1;
fi
extFile=$1 ;
compiler=$2 ;

passed=0 ;
failed=0 ;
testNumber=0 ;
alltests=0 ;
testsFailed="" ;
cd tests ; 
for i in *.${extFile} ; do
  let alltests=$alltests+1 ;

  # If the output already exists, skip the current test
  if ! test -f ${i}.out ; then
    continue ;
  fi
  printf "\r%100s"
  printf "\rTest ${testNumber}: %-100s " $i;
  let testNumber=${testNumber}+1 ;

  # Generate the binary
  pushd ./ &> /dev/null ;
  cd ../ ;
  didSucceed=0 ;
  ./${compiler} tests/${i} ;
  if test $? -eq 0 ; then
    valgrind ./a.out &> OUT ;
    numberOfErrors=`grep "???" OUT | wc -l | awk '{print $1}'` ;
    if test "$numberOfErrors" == "0" ; then
      didSucceed=1 ;
    fi
    rm OUT ;
  fi
  if test $didSucceed == "1" ; then
    let passed=$passed+1 ;
    printf "${green}[OK]${reset}";

  else
    let failed=$failed+1 ;
    echo "${red}[FAILED]${reset}";
    testsFailed="${i} ${testsFailed}";
    rm ${i} ${i}.out ;
  fi
  popd &> /dev/null ; 
done
let total=$passed+$failed ;
echo "" ;
echo "" ;

# Check corner cases
if test $total -eq 0 -a $alltests -gt 0; then
  echo "Warning: there are tests in \"${testsDir}\" but they do not have their oracle output" ;
  echo "" ;
  echo "Please create their oracle outputs in the following way. ";
  echo "Create a text file called like the test name with the \".out\" suffix and store it in \"${testsDir}\". ";
  echo "For example, if a test is called \"mytest.${extFile}\" then you need to have the oracle file \"${testsDir}/mytest.${extFile}.out\"" ;
  exit 0;
fi

# Print summary
echo "########## SUMMARY" ;
if test "${testsFailed}" != "" ; then
  echo "Failed tests: ${testsFailed}" ;
fi
echo "Test passed: $passed out of $total"
