void main() {
	int64 fac
	int64 var1
	int64 var2
	fac <- 1
	var1 <- 15
	var2 <- 2
	while (var2 <= var1) :loop :exit
	:loop
	print(fac)
	fac <- fac * var2
	var2 <- var2 + 1
	continue
	:exit
	return
}
	
