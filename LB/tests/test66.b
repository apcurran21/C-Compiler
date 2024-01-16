 void main() {
	int64 M1v11,M1v12,M1v13,M1v21,M1v22,M1v23,M1v31,M1v32,M1v33
	int64 M2v11,M2v12,M2v13,M2v21,M2v22,M2v23,M2v31,M2v32,M2v33

	M1v11 <- 55
	M1v12 <- 2
	M1v13 <- 63
	M1v21 <- 33
	M1v22 <- 6
	M1v23 <- 44
	M1v31 <- 3
	M1v32 <- 5
	M1v33 <- 37
	M2v11 <- 843
	M2v12 <- 96
	M2v13 <- 66
	M2v21 <- 83
	M2v22 <- 34
	M2v23 <- 27
	M2v31 <- 5
	M2v32 <- 10
	M2v33 <- 17

	M1v11 <- M1v11 + M2v11
	M1v12 <- M1v12 + M2v12	
	M1v13 <- M1v13 + M2v13
	M1v21 <- M1v21 + M2v21
	M1v22 <- M1v22 + M2v22
	M1v23 <- M1v23 + M2v23
	M1v31 <- M1v31 + M2v31
	M1v32 <- M1v32 + M2v32
	M1v33 <- M1v33 + M2v33
	print(M1v11)
	print(M1v12)
	print(M1v13)
	print(M1v21)
	print(M1v22)
	print(M1v23)
	print(M1v31)
	print(M1v32)
	print(M1v33)
	return
}
