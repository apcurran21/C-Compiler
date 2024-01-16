void main() {
	int64 f
	int64 s
	int64 n
	int64 l
	int64 t
	f <- 1
	s <- 1
	n <- 10
	l <- 0
	while (l <= n) :loop :exit
	:loop
	print(s)
	t <- s
	s <- s + f
	f <- t
	l <- l + 1
	continue
	:exit
	return
}
