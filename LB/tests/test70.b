void main()
{
	int64 num_triangular_nums

	num_triangular_nums <- 10
	print(num_triangular_nums)
	
	num_triangular_nums <- num_triangular_nums - 1

	compute_triangular_num(num_triangular_nums)

	compute_many_tns(num_triangular_nums)

	return
}

void compute_triangular_num(int64 nums)
{
	int64 decoded_nums, temp_1

	// No real decoding necessary
	decoded_nums <- nums + 1

	// Formula = (n * (n - 1)) / 2	
	// n - 1
	temp_1 <- decoded_nums - 1
	
	// n * (n - 1)
	temp_1 <- temp_1 * decoded_nums

	// (n * (n - 1)) / 2	 
	temp_1 <- temp_1 >> 1

	print(temp_1)

	return
}

void compute_many_tns(int64 nums)
{
	int64 decoded_nums, nth_tn, call_nth_tn
	
	// No real decoding necessary
	decoded_nums <- nums + 1

	// Start at 1
	nth_tn <- 1
	
	while (nth_tn <= decoded_nums) :tn_body :tn_exit
	{
		:tn_body
		call_nth_tn <- nth_tn - 1
		compute_triangular_num(call_nth_tn)
		goto :tn_latch

		:tn_latch
		nth_tn <- nth_tn + 1
		continue
	}
	
	:tn_exit
	return
}


