void main() {
		int64 res
		res <- big_func(7,13,41,-4,123,-134,2)
		print(res)
		return
}

int64 big_func(int64 v1, int64 v2, int64 v3, int64 v4, int64 v5, int64 v6, int64 v7) {
		int64 res
		res <- 1
		res <- res * v1
		res <- res - v2
		res <- res + v3
		res <- res * v4
		res <- res & v5
		res <- res + v6
		res <- res - v7
		return res
}
