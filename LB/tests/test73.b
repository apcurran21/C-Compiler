void main() 
{
	int64[] a, b
	
	int64 a_start, b_start, a_size, b_size
	a_start <- 23
	b_start <- 17
	
	a_size <- 20
	b_size <- 20

	// Build arrays
	a <- build_array(a_start, a_size)
	b <- build_array(b_start, b_size)

	// Compute dot product
	compute_dot_product(a, b)
	
	return	
}

int64[] build_array(int64 start, int64 size) {
	int64[] arr

	// Allocate array	
	arr <- new Array(size)
	
	int64 i, bounds, val_iter
	i <- 0
	bounds <- length arr 0
	
	// There's a bug in Simone's compiler (confirmed
	// by Enciro) where args used as assignment only
	// are treated as labels --- add 1 as a work around
	val_iter <- start + 1

	if (bounds = size) :start_build :print_warning

	// Warning --- if -1, then we know theres some
	// problem with bounds and size, return
	:print_warning
	print(-1)
	goto :build_exit
	
	:start_build
	while (i < bounds) :build_body :build_exit
	{
		:build_body
		arr[i] <- val_iter
		goto :build_latch
		
		:build_latch
		i <- i + 1
		val_iter <- val_iter + 1
		continue
	}

	:build_exit	
	return arr
}

void compute_dot_product(int64[] a, int64[] b) 
{
	int64 a_size, b_size, sum
	a_size <- length a 0
	b_size <- length b 0
	sum <- 0

	if (a_size = b_size) :start_dot_product :warning

	// Another negative printed, and return
	:warning
	print(-2)
	goto :exit	

	:start_dot_product
	int64 i, local, access_1, access_2
	i <- 0
	local <- 0
	while (i < a_size) :body :exit
	{
		:body		
		access_1 <- a[i]
		access_2 <- b[i]
		local <- access_1 * access_2
		sum <- sum + local
		i <- i + 1
		continue
	}

	:exit
	print(sum)
	return		
}

