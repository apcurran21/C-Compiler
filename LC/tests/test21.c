 void main() {
	int ans
	ans <- mult(5, 7)
	ans <- testEqual(ans, 35)
	print(ans)
	return
}

int mult(int a, int b) {
	tuple t
	int ret, temp
	t <- new Tuple(2)
	t[0] <- a
	t[1] <- b

	ret <- t[0]
	temp <- t[1]
	ret <- ret * temp

	return ret
}

int testEqual(int a, int b) {
	if (a = b) {
		return 1
	}
	else {
		return 0
	}
}