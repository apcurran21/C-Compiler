void main() {
	:EntryPoint
	int64 a
	int64 b
	int64 c
	int64 d
	int64 e
	int64 f

	a <- 1
	b <- 2
	c <- 3
	d <- 4
	e <- 5
	f <- 6

	int64 sum
	sum <- foo(a, b, c, d, e, f)

	PrintArg(sum)

	return
}

int64 foo(int64 a, int64 b, int64 c, int64 d, int64 e, int64 f) {
	:EntryPoint
	int64 sum
	sum <- 0
	sum <- sum + a
	sum <- sum + b
	sum <- sum + c
	sum <- sum + d
	sum <- sum + e
	sum <- sum + f

	int64 g
	int64 h
	int64 i
	int64 j
	int64 k
	int64 l
	g <- 2
	h <- 3
	i <- 4
	j <- 5
	k <- 6
	l <- 7

	int64 res
	res <- bar(sum, g, h, i, j, k, l)

	return res
}

int64 bar(int64 a, int64 b, int64 c, int64 d, int64 e, int64 f, int64 g) {
	:EntryPoint
	int64 sum
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

void PrintArg(int64 arg) {
	:EntryPoint
	print(arg)
	return
}