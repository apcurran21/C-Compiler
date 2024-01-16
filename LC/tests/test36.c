void main() {
	int len
	len <- 10

	int[] arr1
	arr1 <- GetArray(len)
	PopulateArray1(arr1, len)

	printResultArray(arr1)


	int[] arr2
	arr2 <- GetArray(len)
	PopulateArray2(arr2, len)

	printResultArray(arr2)

	return
}

int[] GetArray(int len) {
	int val
	int[] arr
	val <- 1
	arr <- new Array(len)
	return arr
}

void PopulateArray1(int[] arr, int len) {
	int ind
	ind <- 0

	while (ind < len) {
		int value
		value <- ind * 8
		arr[ind] <- value
		ind <- ind + 1
	}

	return
}

void PopulateArray2(int[] arr, int len) {
	int ind
	ind <- 0

	while (ind < len) { 
		arr[ind] <- 5
		ind <- ind + 1
	} 

	return
}

void printResultArray(int[] arr) {
	print(arr)
	return
}
