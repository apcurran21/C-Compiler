// calculates (and prints) the first 20 terms of the fibonacci sequence
// with fib(0) = fib(1) = 1

void main() {
	int64[] fib_arr
	fib_arr <- new Array(21)
	fib_arr[0] <- 1
	fib_arr[1] <- 1
	print(1)
	print(1)

	int64 i
	i <- 2

	while(i < 21) :loop_body :loop_end 
  {
		:loop_body
		int64 i_sub_2, fib_sub_2, i_sub_1, fib_sub_1, fib_i
		i_sub_2 <- i - 2
		fib_sub_2 <- fib_arr[i_sub_2]
		i_sub_1 <- i - 1
		fib_sub_1 <- fib_arr[i_sub_1]
		fib_i <- fib_sub_2 + fib_sub_1
		fib_arr[i] <- fib_i
		print(fib_i)
		i <- i + 1
		continue
	}
	:loop_end
    return
}
