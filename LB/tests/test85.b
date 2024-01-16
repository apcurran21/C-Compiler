void main() {
	int64 ret
	int64[] array

	array <- new Array(7)
	ret <- length array 0

	ret <- rand(array, ret)

	print (ret)

	array <- new Array(9)
	ret <- length array 0

	ret <- rand(array, ret)

	print (ret)

	return
}

int64 rand(int64[] array, int64 ret) {
	int64 ans, test, len
	goto :startCalcs
	:startCalcs
	ans <- 0 
	len <- 0
	test <- 0
	goto :keepGoing
	:keepGoing
	len <- length array 0
	test <- len = ret
	goto :good
	:cantreach
	ans <- 1
	test <- 0
	return 0
	:good
	ans <- array[0]
	test <- array[1]
	len <- array[2]
	ans <- ans + test
	ans <- ans + len
	return ans
	goto :end
	:end
	return 0
}

