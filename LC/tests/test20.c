void main() {
	int len
	int[] array

	array <- new Array(7)
	len <- length array 0

	len <- check(array, len)

	print (len)

	array <- new Array(9)
	len <- length array 0

	len <- check(array, len)

	print (len)

	return
}

int check(int[] array, int len) {
	int l 
	l <- length array 0
	if (l = len) {
		return 1
	}
	else {
		return 0
	}
}

