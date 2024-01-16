void main() {
	int[][][][] mat
	int len
	len <- 7

	mat <- Populate4DArray(len, len, len, len)


	int val
	val <- 200

	tuple res
	res <- RetrieveElement(mat, val)

	print(res)

	return
}

int[][][][] Populate4DArray(int d1, int d2, int d3, int d4) {
	int[][][][] mat
	mat <- new Array(d1,d2,d3,d4)

	mat[3][4][0][0] <- 100
	mat[3][4][0][1] <- 100
	mat[3][4][0][2] <- 100
	mat[3][4][0][3] <- 100
	mat[3][4][1][4] <- 100
	mat[3][4][2][0] <- 200
	mat[3][4][3][0] <- 100
	mat[3][4][4][0] <- 100
	mat[3][5][0][0] <- 100
	mat[3][6][0][0] <- 100

	mat[6][4][0][0] <- 100
	mat[6][4][0][1] <- 100
	mat[6][4][0][2] <- 100
	mat[6][4][0][3] <- 100
	mat[6][4][1][4] <- 100
	mat[6][4][2][0] <- 200
	mat[6][4][3][0] <- 10
	mat[6][4][4][0] <- 110
	mat[6][5][0][0] <- 12
	mat[6][6][0][0] <- 154

	return mat
}


tuple RetrieveElement(int[][][][] mat, int val) {
	tuple res
	res <- new Tuple(4)

	int i, j, k, l

	i <- 0
	j <- 0
	k <- 0
	l <- 0


	int d1_len, d2_len, d3_len, d4_len

	d1_len <- length mat 0
	d2_len <- length mat 1
	d3_len <- length mat 2
	d4_len <- length mat 3

	
	while (i < d1_len){
		j <- 0
		while(j < d2_len) {
			k <- 0
			while(k < d3_len) {
				l <- 0
				while(l < d2_len) {
					int curVal
					curVal <- mat[i][j][k][l]

					if(curVal = val) {
						res[0] <- i
						res[1] <- j
						res[2] <- k
						res[3] <- l
					} else {}

					l <- l + 1
				}
				k <- k + 1
			}
			j <- j + 1
		}
		i <- i + 1
	}


	return res

}
