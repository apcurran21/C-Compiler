void main() {
	int[][] mat
	int len
	int width

	len <- 4
	width <- 4

	mat <- GetMatrix(len, width)

	int sum
	sum <- SumMatrix(mat)

	print(sum)

	return
}



int[][] GetMatrix(int len, int width) {
	int[][] mat
	mat <- new Array(len, width)

	mat[0][0] <- 10
	mat[1][1] <- 10
	mat[2][2] <- 10
	mat[0][1] <- 10
	mat[1][0] <- 10
	mat[2][1] <- 10
	mat[2][3] <- 10

	return mat
}


int SumMatrix(int[][] mat) {
	int len
	int width

	len <- length mat 0
	width <- length mat 1

	int i
	int j
	i <- 0
	j <- 0

	int sum
	sum <- 0

	int continueRow
	int continueCol





	while (i < len) {
		j <- 0
		while(j < width) {
			int curElement
			curElement <- mat[i][j]
			sum <- sum + curElement
			j <- j + 1
		}
		i <- i + 1
	}
	return sum
}
