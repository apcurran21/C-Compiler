void main () {
	int64 a, b, c, d
	a <- 1
	b <- 2
	c <- 3
	d <- 4
	while (a < d) :start :end
	:start
	{
	int64 scope 
	scope <- 1
	print(scope)
	}
	a <- a + 1
	
	:end
	if (b = c) :equal :notEqual
	:equal
	print(1)
	:notEqual
	print(0)
	return
}


