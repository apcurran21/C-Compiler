YEAR=2023

all: performance

gcc: competition$(YEAR).c
	$@ -DDEBUG -mtune=generic -O0 $^ -o a.out 

clang: competition$(YEAR).c
	$@ -DDEBUG -mtune=generic -finline-hint-functions $^ -o a.out 

performance:
	/usr/bin/time -f'%E' ./a.out < ../LC/tests/competition$(YEAR).c.in; sleep 1 ;

clean:
	rm -f a.out *.txt ;
