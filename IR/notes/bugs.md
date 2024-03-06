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