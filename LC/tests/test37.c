void main() {
	int a
	int b
	int c
	int d
	int e
	int f

	a <- 1
	b <- 2
	c <- 3
	d <- 4
	e <- 5
	f <- 6

	int sum
	sum <- foo(a, b, c, d, e, f)

	PrintArg(sum)

	return
}

int foo(int a, int b, int c, int d, int e, int f) {
	int sum
	sum <- 0
	sum <- sum + a
	sum <- sum + b
	sum <- sum + c
	sum <- sum + d
	sum <- sum + e
	sum <- sum + f

	int g
	int h
	int i
	int j
	int k
	int l
	g <- 2
	h <- 3
	i <- 4
	j <- 5
	k <- 6
	l <- 7

	int res
	res <- bar(sum, g, h, i, j, k, l)

	return res
}

int bar(int a, int b, int c, int d, int e, int f, int g) {
	int sum
	sum <- 0
	sum <- sum + a
	sum <- sum + b
	sum <- sum + c
	sum <- sum + d
	sum <- sum + e
	sum <- sum + f
	sum <- sum + g

	return sum
}

void PrintArg(int arg) {
	print(arg)
	return
}