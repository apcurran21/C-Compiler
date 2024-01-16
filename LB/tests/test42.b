void main() {
	int64 loopvar
	int64 s
	loopvar <- 0
	while (loopvar < 20) :loop :exit
	:loop
	print(loopvar)
	s <- s>>1
	s <- s<<1
	if (s = loopvar) :even :odd
	:odd
	print(1)
	goto :check
	:even
	print(0)
	:check
	loopvar <- loopvar + 1
	continue
	:exit
	return
}
