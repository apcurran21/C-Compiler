void main() {
	int64[][] mat
	int64 len
	int64 width

	len <- 4
	width <- 4

	mat <- GetMatrix(len, width)

	int64 sum
	sum <- SumMatrix(mat)

	print(sum)

	return
}



int64[][] GetMatrix(int64 len, int64 width) {
	int64[][] mat
	mat <- new Array(len, width)

	mat[0][0] <- 10
	mat[1][1] <- 10
	mat[2][2] <- 10
	mat[0][1] <- 10
	mat[1][0] <- 10
	mat[2][1] <- 10
	mat[0][0] <- 10
	mat[0][1] <- 10
	mat[2][3] <- 10

	return mat
}


int64 SumMatrix(int64[][] mat) {
	int64 len
	int64 width

	len <- length mat 0
	width <- length mat 1

	int64 i
	int64 j
	i <- 0
	j <- 0

	int64 sum
	sum <- 0

	int64 continueRow
	int64 continueCol




	:StartRow
	while (i < len) :ContinueRow :ExitRow


	:ContinueRow
	j <- 0

	:StartCol
	while(j < width) :ContinueCol :ExitCol

	:ContinueCol

	int64 curElement
	curElement <- mat[i][j]
	sum <- sum + curElement

	j <- j + 1
	continue


	:ExitCol
	i <- i + 1

	continue
	
	:ExitRow

	return sum
}
