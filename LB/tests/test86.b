 void main() {
	int64 ans
	ans <- mult(5, 7)
	ans <- testEqual(ans, 35)
	print(ans)
	return
}

int64 mult(int64 a, int64 b) {
	tuple t
	int64 ret, temp
	t <- new Tuple(2)
	t[0] <- a
	t[1] <- b

	ret <- t[0]
	temp <- t[1]
	ret <- ret * temp

	return ret
}

int64 testEqual(int64 a, int64 b) {
	int64 ret
	ret <- a = b
	if (ret = 0) :no :yes
	:no
	ret <- 0
	return ret
	:yes
	ret <- 1
	return ret
}
