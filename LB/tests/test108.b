 void main() {
	:EntryPoint


	int64 len
	len <- 10

	int64[] arr

	arr <- GetArray(len)
	PrintArray(arr)


	int64 res
	res <- FindElement(100, arr, len)

	print(res)

	return
}


 int64[] GetArray(int64 len) {
	:EntryPoint
	int64[] arr


	arr <- new Array(len)

	int64 targetInd
	int64 targetVal

	targetInd <- 2
	targetVal <- 100

	arr[targetInd] <- targetVal

	return arr
}




 int64 FindElement(int64 target, int64[] arr, int64 len) {
	:EntryPoint
	int64 ind
	ind <- 0
	goto :LoopStart

	:LoopStart
	int64 isDone
	isDone <- ind = len
	while (ind < len) :EnterLoop :ExitLoop

	:EnterLoop
	int64 foundValue
	int64 cur
	cur <- arr[ind]
	if (cur = target) :Breakout :Continue

	:Breakout
	break

	:Continue
	ind <- ind + 1
	continue

	:ExitLoop
	return ind
}


 void PrintArray(int64[] arr) {
	:EntryPoint
	print(arr)
	return
}
