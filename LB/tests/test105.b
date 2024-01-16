void main() {
	:EntryPoint
	int64 len
	len <- 10

	int64[] arr1
	arr1 <- GetArray(len)
	PopulateArray1(arr1, len)

	printResultArray(arr1)


	int64[] arr2
	arr2 <- GetArray(len)
	PopulateArray2(arr2, len)

	printResultArray(arr2)

	return
}

int64[]GetArray(int64 len) {
	:EntryPoint
	int64 val
	int64[] arr
	val <- 1
	arr <- new Array(len)
	return arr
}

void PopulateArray1(int64[] arr, int64 len) {
	:EntryPoint
	int64 ind
	int64 stop
	ind <- 0

	while (ind < len) :LoopContinue :LoopEnd
	:LoopContinue
	int64 value
	value <- ind * 8
	arr[ind] <- value
	ind <- ind + 1
	continue

	:LoopEnd
	return
}

void PopulateArray2(int64[] arr, int64 len) {
	:EntryPoint
	int64 ind
	ind <- 0
	goto :LoopStart2

	:LoopStart2
	arr[ind] <- 5
	ind <- ind + 1
	while (ind < len) :LoopStart2 :Exit
	:Exit

	return
}

void printResultArray(int64[] arr) {
	:EntryPoint
	print(arr)
	return
}
