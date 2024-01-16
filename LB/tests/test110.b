void main() {
	int64[][][][] mat
	int64 len
	len <- 7

	mat <- Populate4DArray(len, len, len, len)


	int64 val
	val <- 200

	tuple res
	res <- RetrieveElement(mat, val)

	print(res)

	return
}

int64[][][][] Populate4DArray(int64 d1, int64 d2, int64 d3, int64 d4) {
	int64[][][][] mat
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


tuple RetrieveElement(int64[][][][] mat, int64 val) {
	tuple res
	res <- new Tuple(4)

	int64 i, j, k, l

	i <- 0
	j <- 0
	k <- 0
	l <- 0


	int64 d1_len, d2_len, d3_len, d4_len

	d1_len <- length mat 0
	d2_len <- length mat 1
	d3_len <- length mat 2
	d4_len <- length mat 3

	
	while (i < d1_len) :body1 :exit1
	:body1
		j <- 0
		while(j < d2_len) :body2 :exit2
		:body2
			k <- 0
			while(k < d3_len) :body3 :exit3
			:body3
				l <- 0
				while(l < d2_len) :body4 :exit4
				:body4
					int64 curVal
					curVal <- mat[i][j][k][l]

					if(curVal = val) :setValue :cont
						:setValue
						res[0] <- i
						res[1] <- j
						res[2] <- k
						res[3] <- l
						:cont

					l <- l + 1
					continue
				:exit4

				k <- k + 1
				continue
			:exit3

			j <- j + 1
			continue
		:exit2

		i <- i + 1
		continue
	:exit1


	return res

}