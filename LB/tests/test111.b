void main(){
	int64[][] a,b,res
	int64 ja, ia, loop1v, loop2v, checkv
	a <- new Array(2,2)
	a[0][0] <- 1
	a[0][1] <- 2
	a[1][0] <- 3
	a[1][1] <- 4
	ja <- length a 1
	ia <- length a 0
	loop1v <- 0
	res <- new Array (2,2)
	int64 temp1
	int64 temp2

	while (loop1v < ia) :loop1init :return
		:loop1init
		loop2v <- 0
		while (loop2v < ja) :loop2c :loop2exit
			:loop2c
			temp1 <- a[loop2v][loop1v]
			res[loop1v][loop2v] <- temp1
			loop2v <- loop2v + 1
			continue
		:loop2exit
		loop1v <- loop1v + 1
		continue
	:return
	print(res)
	return
}
