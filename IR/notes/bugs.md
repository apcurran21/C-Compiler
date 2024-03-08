## Failing Tests
* 24 - IR.cpp, calculate_array()
    ```
    43      void newArray::calculate_array(Function *f, std::ofstream &outputFile){
    44          for (auto num:this->args){
    45              auto number = dynamic_cast<Number *>(num);
    46              this->variableDimensions.push_back(number->value+"D");
    ```
    * args can be both numbers or variables so the dynamic cast will fail
* 23 - code_generator.cpp, storeInstruction::gen
    ```
    68        auto key_var = f->variableNameToPointer[key];
    69        if (f->variableToTypeMapping[key_var]->type == TypeEnum::int64){
    70          auto array = f->variableNameToArray[this->dst->print()];
    71          int offset_val = 8 + (array->args.size()*8);
    72          outputFile << "%offset <- " <<offset_val<<"\n\t"; 
    ```
    * key_var not in the dictionary, should always use .find() for looking up in maps.
* 27 - ^same bug
* 31 - code_generator.cpp, gen functions for returns
    ```
    %res <- %res - %v7
	return%res
	}
    ```
    * doesn't generate spacing
* 15 - same key_var bug
* 26 - same key_var bug
* 71 - same doesn't generate spacing bug




### Known parser bugs
* 14 - codegen
* 15 - codegen
* 16 - codegen
* 23 - codegen
* 24 - calculate_array


### Failing tests - 3/7
```
Test 31: test27.IR                                                                                            [FAILED]
Test 32: test31.IR                                                                                            [FAILED]
Test 33: test15.IR                                                                                            [FAILED]
Test 35: test26.IR                                                                                            [FAILED]
Test 37: test61.IR                                                                                            [FAILED]
Test 42: test42.IR                                                                                            [FAILED]
Test 43: test38.IR                                                                                            [FAILED]
Test 52: test83.IR                                                                                            [FAILED]
Test 56: test66.IR                                                                                            [FAILED]
Test 58: test47.IR                                                                                            [FAILED]
Test 63: test14.IR                                                                                            [FAILED]
Test 64: test43.IR                                                                                            [FAILED]
Test 65: test48.IR                                                                                            [FAILED]
Test 66: test103.IR                                                                                           [FAILED]
Test 70: test105.IR                                                                                           [FAILED]
Test 71: test55.IR                                                                                            [FAILED]
Test 72: test92.IR                                                                                            [FAILED]
Test 73: test74.IR                                                                                            [FAILED]
Test 75: test109.IR                                                                                           [FAILED]
Test 76: test35.IR                                                                                            [FAILED]
Test 77: test102.IR                                                                                           [FAILED]
Test 78: test16.IR                                                                                            [FAILED]
Test 79: test37.IR                                                                                            [FAILED]
Test 80: test33.IR                                                                                            [FAILED]
Test 82: test91.IR                                                                                            [FAILED]
Test 85: test54.IR                                                                                            [FAILED]
Test 89: test58.IR                                                                                            [FAILED]
Test 90: test104.IR                                                                                           [FAILED]
Test 91: test50.IR   
```