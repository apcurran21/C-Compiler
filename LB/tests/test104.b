void main() {
	:entryPoint
	int64 x
	int64 y
	int64 result1
	x <- 3
	y <- 3
	result1 <- findGCD(x, y)

	int64 x2
	int64 y2
	int64 result2
	x2 <- 30
	y2 <- 50

	result2 <- findGCD(x2, y2)

	int64 x3
	int64 y3
	int64 result3
	x3 <- 75
	y3 <- 80
	result3 <- findGCD(x3, y3)
	return
}

void findGCD(int64 a, int64 b) {
	:TestNumbers
	if (a < b) :Lesser :NotLesser

	:NotLesser
	int64 isEqual
	isEqual <- a = b
	if(a = b) :Equal :Greater

	:Greater
	a <- a - b
	printResult(a, b)
	findGCD(a, b)
	goto :Finished

	:Lesser
	b <- b - a
	printResult(a, b)
	findGCD(a, b)
	goto :Finished

	:Equal
	printResult(a, b)
	goto :Finished

	:Finished
	return 
}

void printResult(int64 a, int64 b) {
	:Entrypoint
	print(a)

	print(b)
	return
}
