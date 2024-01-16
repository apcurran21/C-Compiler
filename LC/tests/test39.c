 void main() {
	int len
	len <- 10

	int[] arr

	arr <- GetArray(len)
	PrintArray(arr)


	int res
	res <- FindElement(100, arr, len)

	print(res)

	return
}


 int[] GetArray(int len) {
	int[] arr


	arr <- new Array(len)

	int targetInd
	int targetVal

	targetInd <- 2
	targetVal <- 100

	arr[targetInd] <- targetVal

	return arr
}




 int FindElement(int target, int[] arr, int len) {
	int ind
	ind <- 0

	int isDone
	isDone <- ind = len

	while (ind < len) {
		int foundValue
		int cur
		cur <- arr[ind]
		if (cur = target) {
			break
		} else {
			ind <- ind + 1
		}
	}

	return ind
}


 void PrintArray(int[] arr) {
	print(arr)
	return
}