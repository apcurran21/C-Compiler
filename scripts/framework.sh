#!/bin/bash

function compile_language {
  local l=$1 ;

  pushd ./ ;
  cd $1 ;
  make all -j ;

  popd ;
}

dirName="322_framework" ;
origDir=`pwd` ;

# Compile all compilers and interpreters
compile_language "L1" ;
compile_language "L2" ;
compile_language "L3" ;
compile_language "IR" ;
compile_language "LA" ;
compile_language "LB" ;
compile_language "LC" ;

# Copy all files to an empty directory
mkdir ../$dirName ;
cd ../$dirName ;
cp -r "$origDir"/* ./ ;

# Remove compiler sources
rm */src/* ;

# Remove object files
rm -r */obj ;

# Copy the binary into a hidden directory
for i in L1 L2 L3 IR LA LB LC LD ; do
  cd $i ;
  mkdir -p .bin ;
  cp bin/* .bin/ ;
  cd ../ ;
done

# Create the package
cd ../ ;
tar cfj ${dirName}.tar.bz2 ${dirName} ;
mv ${dirName}.tar.bz2 src ;
rm -r ${dirName} ;
