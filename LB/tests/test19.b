void main(){
	int64[] a
	int64 al,i,temp,temp2,temp3
	a <- new Array(10)
	a[0] <- 0
	a[1] <- 1
	a[2] <- 2
	a[3] <- 3
	a[4] <- 4
	a[5] <- 5
	a[6] <- 6
	a[7] <- 7
	a[8] <- 8
	a[9] <- 9
	print(a)
	al <- length a 0
	print(al)
	i <- 0
	al <- al - 1
	temp <- a[i]
	while (i < al) :loop :exit
		:loop
		temp2 <- i + 1
		temp3 <- a[temp2]
		a[temp2] <- temp
		temp <- temp3
		i <- i + 1
		continue
	:exit
	a[0] <- temp3
	print(a)
	return
}

