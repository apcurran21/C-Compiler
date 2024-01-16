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

# Colors
red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

# Run the tests
passed=0 ;
failed=0 ;
testNumber=0 ;
alltests=0 ;
testsFailed="" ;
cd ${testsDir} ; 
ciscs="0" ;
for i in `ls -S -r *.${extFile}` ; do
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
  cd "${origDir}" ;
  didSucceed=0 ;
  ./${compiler} ${testsDir}/${i} &> /dev/null;
  if test $? -eq 0 ; then
    if test -f ${testsDir}/${i}.in ; then
      (./a.out || false) < ${testsDir}/${i}.in > ${testsDir}/${i}.out.tmp 2>&1;
    else
      (./a.out || false) > ${testsDir}/${i}.out.tmp 2>&1 ;
    fi
    cmp ${testsDir}/${i}.out.tmp ${testsDir}/${i}.out &> /dev/null ;
    if test $? -eq 0 ; then
      didSucceed=1 ;
    fi
  fi
  if test $didSucceed == "1" ; then
    let passed=$passed+1 ;
    printf "${green}[OK]${reset}";

    cisc=`grep "mem.* +=" prog.L2 | wc -l | awk '{print $1}'` ;
    if test "$cisc" != "0" ; then
      ciscs="1" ;
    fi
    cisc=`grep "mem.* -=" prog.L2 | wc -l | awk '{print $1}'` ;
    if test "$cisc" != "0" ; then
      ciscs="1" ;
    fi
    cisc=`grep "+=.*mem" prog.L2 | wc -l | awk '{print $1}'` ;
    if test "$cisc" != "0" ; then
      ciscs="1" ;
    fi
    cisc=`grep "\-=.*mem" prog.L2 | wc -l | awk '{print $1}'` ;
    if test "$cisc" != "0" ; then
      ciscs="1" ;
    fi
    cisc=`grep "cjump .*<.*" prog.L2 | wc -l | awk '{print $1}'` ;
    if test "$cisc" != "0" ; then
      ciscs="1" ;
    fi
    cisc=`grep "cjump .*>.*" prog.L2 | wc -l | awk '{print $1}'` ;
    if test "$cisc" != "0" ; then
      ciscs="1" ;
    fi
    cisc=`grep "<- mem " prog.L2 | awk '{if ($5 != 0 && $4 != "rsp") print $5}' | wc -l | awk '{print $1}'` ;
    if test "$cisc" != "0" ; then
      ciscs="1" ;
    fi
    cisc=`grep "mem .* <- " prog.L2 | awk '{if ($3 != 0 && $2 != "rsp") print $3}' | wc -l | awk '{print $1}'` ;
    if test "$cisc" != "0" ; then
      ciscs="1" ;
    fi

    cisc=`grep "@" prog.L2 | wc -l | awk '{print $1}'` ;
    if test "$cisc" != "0" ; then
      ciscs="1" ;
    fi
  else
    let failed=$failed+1 ;
    echo "${red}[FAILED]${reset}";
    testsFailed="${i} ${testsFailed}";
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
if test "$ciscs" == "0" ; then
  if test "$passed" == "$total" ; then
    echo "While all tests succeeded, you did not generate any complex instruction. "
    exit 0 ;
  fi
fi
echo "Test passed: $passed out of $total"
