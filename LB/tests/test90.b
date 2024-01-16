 void main() {
	int64[][] arr
	int64 arrsize, arrval,i,c,t

	
	arrsize <- 31
	arrval <- 3
	
	arr <- new Array(arrsize,arrval)
	arr[0][0] <- 43
	arr[1][0] <- 73
	arr[2][0] <- 29
	
	i <- 0
	arrsize <- arrsize >> 1
	:loop
	t <- arr[i][0]
	print(t)
	i <- i +1
	while(i<arrsize) :loop :exit
	:exit
	return
}
