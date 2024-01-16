 void main () {
	int[] array
	array <- new Array(5)
	int print1, print2
	print1 <- findLen(array)
	print2 <- sumfirst2(array)
	print(print1)
	print(print2)
	return
}
int sumfirst2 (int[] array) {
	int ret, temp
	ret <- array[0]
	temp <- array[1]
	ret <- ret + temp
	return ret

}

int findLen (int[] array) {
	int ret
	ret <- length array 0
	return ret
}

