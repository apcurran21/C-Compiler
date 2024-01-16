all: langs
	
langs: L1_lang L2_lang L3_lang IR_lang LA_lang LB_lang LC_lang

L1_lang:
	cd L1 ; make 

L2_lang:
	cd L2 ; make

L3_lang:
	cd L3 ; make

IR_lang:
	cd IR ; make

LA_lang:
	cd LA ; make

LB_lang:
	cd LB ; make

LC_lang:
	cd LC ; make

LD_lang:
	cd LD ; make

framework:
	./scripts/framework.sh

homework:
	./scripts/homework.sh

test:
	./scripts/tests.sh

rm_programs: langs
	cd L1 ; make test_programs ; make rm_tests_without_oracle
	cd L2 ; make test_programs ; make rm_tests_without_oracle
	cd L3 ; make test_programs ; make rm_tests_without_oracle
	cd IR ; make test_programs ; make rm_tests_without_oracle
	cd LA ; make test_programs ; make rm_tests_without_oracle
	cd LB ; make test_programs ; make rm_tests_without_oracle

rm_tests_without_oracle:
	cd L1 ; make rm_tests_without_oracle
	cd L2 ; make rm_tests_without_oracle
	cd L3 ; make rm_tests_without_oracle
	cd IR ; make rm_tests_without_oracle
	cd LA ; make rm_tests_without_oracle
	cd LB ; make rm_tests_without_oracle
	cd LC ; make rm_tests_without_oracle

generate_tests: langs
	./scripts/generateTests.sh

include_new_tests: langs
	./scripts/includeNewTests.sh

clean:
	rm -f *.bz2 ; 
	cd L1 ; make clean ; 
	cd L2 ; make clean ; 
	cd L3 ; make clean ; 
	cd IR ; make clean ; 
	cd LA ; make clean ; 
	cd LB ; make clean ; 
	cd LC ; make clean ; 
	cd C ; make clean ; 

.PHONY: langs L1_lang L2_lang L3_lang IR_lang LA_lang LB_lang LC_lang LD_lang framework homework tests run_programs generate_tests include_new_tests clean
