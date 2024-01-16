void main(){
	int64[][] A, B
	int64 Asize, Bsize, temp, temp2, v1, v2, v3
	
	A <- new Array(2,2)
	B <- new Array(2,2)
	A[0][0] <- 5
	A[0][1] <- 5
	A[1][0] <- 5
	A[1][1] <- 5

	B[0][0] <- 5
	B[0][1] <- 5
	B[1][0] <- 5
	B[1][1] <- 5

	Asize <- length A 1
	Bsize <- length B 1
	temp <- 0
	temp2 <- 0

	while ( temp < Asize) :innerloop :finish
		:innerloop
		while ( temp2 < Bsize) :continue :outerloop
		:continue
		v1 <- A[temp][temp2]
		v2 <- B[temp][temp2]
		v3 <- v1 + v2
		A[temp][temp2] <- v3
		temp2 <- temp2 + 1
		continue
	:outerloop
	temp2 <- 0
	temp <- temp + 1
	continue
	:finish
	print(A)
	return
}

