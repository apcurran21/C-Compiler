void main() {
	int x
	int y
	int result1
	x <- 3
	y <- 3
	result1 <- findGCD(x, y)

	int x2
	int y2
	int result2
	x2 <- 30
	y2 <- 50

	result2 <- findGCD(x2, y2)

	int x3
	int y3
	int result3
	x3 <- 75
	y3 <- 80
	result3 <- findGCD(x3, y3)
	return
}

void findGCD(int a, int b) {
	if (a < b) {
		b <- b - a
		printResult(a, b)
		findGCD(a, b)
	} else {
		int isEqual
		isEqual <- a = b
		if(a = b) {
			printResult(a, b)
		} else {
			a <- a - b
			printResult(a, b)
			findGCD(a, b)
		}
	}
	
	return 
}

void printResult(int a, int b) {
	print(a)
	print(b)
	return
}