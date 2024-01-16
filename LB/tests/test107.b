void main() {
	:EntryPoint
	int64 len
	len <- 10

	int64[] arr
	arr <- GetArray(len)
	print(arr)

	int64 res
	res <- FindPeak(arr, len)

	PrintResult(res)

	return 
}

int64[] GetArray(int64 len) {
	:EntryPoint

	int64[] arr
	arr <- new Array(len)

	int64 x
	x <- 1
	x <- x << 1
	x <- x + 1
	arr[0] <- x

	
	x <- 2
	x <- x << 1
	x <- x + 1
	arr[1] <- x

	
	x <- 3
	x <- x << 1
	x <- x + 1
	arr[2] <- x

	
	x <- 5
	x <- x << 1
	x <- x + 1
	arr[3] <- x

	
	x <- 1
	x <- x << 1
	x <- x + 1
	arr[4] <- x

	
	x <- 3
	x <- x << 1
	x <- x + 1
	arr[5] <- x

	
	x <- 2
	x <- x << 1
	x <- x + 1
	arr[6] <- x

	
	x <- 10
	x <- x << 1
	x <- x + 1
	arr[7] <- x

	
	x <- 11
	x <- x << 1
	x <- x + 1
	arr[8] <- x

	
	x <- 8
	x <- x << 1
	x <- x + 1
	arr[9] <- x

	return arr
}


int64 FindPeak(int64[] arr, int64 len) {
	:EntryPoint
	int64 max
	int64 ind
	max <- 0
	ind <- 0
	goto :LoopStart


	:LoopStart

	while ( ind < len ) :LoopContinue :LoopEnd

	:LoopContinue
	int64 cur
	int64 notMax
	cur <- arr[ind]
	if (max >= cur) :Continue :SetMax

	:SetMax
	max <- cur
	goto :Continue

	:Continue
	ind <- ind + 1
	continue

	:LoopEnd
	return max
}

void PrintResult(int64 res) {
	:EntryPoint
	print(res)
	return
}
