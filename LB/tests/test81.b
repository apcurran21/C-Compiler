void main () {
	int64[] array
	array <- new Array(5)
	int64 print1, print2
	print1 <- findLen(array)
	print2 <- sumfirst2(array)
	print(print1)
	print(print2)
	return
}
int64 sumfirst2 (int64[] array) {
	int64 ret, temp
	ret <- array[0]
	temp <- array[1]
	ret <- ret + temp
	return ret

}

int64 findLen (int64[] array) {
	int64 ret
	ret <- length array 0
	return ret
}