void main()
{
	int64 num_sides, lots_of_sides

	num_sides <- 15
	print (num_sides)

	num_sides <- num_sides - 1

	// Compute the number of degrees for 
	// an angle in a regular polygon with 
    // num_sides sides

	compute_num_degrees_angle_for_shape(num_sides)
	compute_many_degrees(num_sides)
	

	// Compute number of degrees of an angle 
	// for regular polygon with 87 sides
	lots_of_sides <- 87

	lots_of_sides <- lots_of_sides - 1

	compute_num_degrees_angle_for_shape(lots_of_sides)

	return
}

void compute_num_degrees_angle_for_shape(int64 sides)
{
	int64 decoded_sides, temp_1, division
	
	// No real decoding necessary
	decoded_sides <- sides + 1

	// Formula = ((n - 2) * 180) / n	
	// n - 2
	temp_1 <- decoded_sides - 2
	
	// (n - 2) * 180
	temp_1 <- temp_1 * 180 

	// ((n - 2) * 180) / n	 
	
	temp_1 <- temp_1 - 1
	decoded_sides <- decoded_sides - 1

	division <- divide(temp_1, decoded_sides)
	temp_1 <- division

	print(temp_1)

	return
}

void compute_many_degrees(int64 sides)
{
	int64 decoded_sides, nth_side, call_nth_side
	
	// No real decoding necessary
	decoded_sides <- sides + 1

	// Start at 3 --- triangle
	nth_side <- 3
	
	while (nth_side <= decoded_sides) :deg_body :deg_exit	
	{
		:deg_body

		call_nth_side <- nth_side - 1
		compute_num_degrees_angle_for_shape(call_nth_side)
		goto :deg_latch

		:deg_latch
		nth_side <- nth_side + 1
		continue
	}

	:deg_exit
	return
}

int64 divide(int64 numer, int64 denom)
{
	int64 temp, quotient, n, d, enc_temp, enc_quotient
	
	n <- numer + 1
	d <- denom + 1

	// Set temp and quotient
	enc_temp <- 1
	enc_quotient <- 0

	// No real decoding necessary 
	temp <- enc_temp
	quotient <- enc_quotient

	while (d <= n) :nd_loop_body :nd_loop_exit
	{	
		:nd_loop_body
		d <- d << 1
		temp <- temp << 1
		continue
	}

	:nd_loop_exit
	while (temp > 1) :t_loop_body :t_loop_exit
	{
		:t_loop_body
		d <- d >> 1
		temp <- temp >> 1
		if (n >= d) :quotient_calc :t_loop_latch

		:quotient_calc
		n <- n - d
		quotient <- quotient + temp
		goto :t_loop_latch

		:t_loop_latch
		continue
	}

	:t_loop_exit
	return quotient 
}
