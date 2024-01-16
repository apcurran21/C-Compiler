void main()
{
	int64 num_sides, lots_of_sides

	num_sides <- 12
	print (num_sides)

	num_sides <- num_sides - 1
	
	// Compute the number of diagonals for 
	// a polygon with num_sides sides

	compute_num_diagonals_for_shape(num_sides)
	compute_many_diagonals(num_sides)
	

	// Compute number of diagonals for polygon 
	// with 51 sides
	lots_of_sides <- 51
	
	lots_of_sides <- lots_of_sides - 1

	compute_num_diagonals_for_shape(lots_of_sides)
	
	return
}

void compute_num_diagonals_for_shape(int64 sides)
{
	int64 decoded_sides, temp_1
	
	// No real decoding necessary
	decoded_sides <- sides + 1

	// Formula = (n * (n - 3)) / 2	
	// n - 3
	temp_1 <- decoded_sides - 3
	
	// n * (n - 3)
	temp_1 <- temp_1 * decoded_sides

	// (n * (n - 3)) / 2	 
	temp_1 <- temp_1 >> 1

	print(temp_1)

	return
}

void compute_many_diagonals(int64 sides)
{
	int64 decoded_sides, nth_side, call_nth_side
	
	// No real decoding necessary
	decoded_sides <- sides + 1

	// Start at 3 --- triangle
	nth_side <- 3
	
	while (nth_side <= decoded_sides) :diag_body :diag_exit
	{
		:diag_body
		call_nth_side <- nth_side - 1
		compute_num_diagonals_for_shape(call_nth_side)
		goto :diag_latch

		:diag_latch
		nth_side <- nth_side + 1
		continue
	}
	
	:diag_exit
	return
}


