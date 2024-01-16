void main() {
	
	int len
	len <- 10

	int[] arr
	arr <- GetArray(len)
	print(arr)

	int res
	res <- FindPeak(arr, len)

	PrintResult(res)

	return 
}

int[] GetArray(int len) {
	

	int[] arr
	arr <- new Array(len)

	int x
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


int FindPeak(int[] arr, int len) {
	
	int max
	int ind
	max <- 0
	ind <- 0

	while (ind < len) {
		int cur
		cur <- arr[ind]
		if (cur >= max) {
			max <- cur
		} else {
			
		}

		ind <- ind + 1
	}

	return max
}

void PrintResult(int res) {
	
	print(res)
	return
}