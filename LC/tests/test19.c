void main () {
	int var1, var2, var3, var4, ret

	var1 <- 3
	var2 <- 6
	var3 <- 8
	var4 <- 90
	
	ret <- even(var1)
	print(ret)
	ret <- even(var2)
	print(ret)
	ret <- even(var3)
	print(ret)
	ret <- even(var4)
	print(ret)

	return
}

int even (int var1) {
	if (var1 < 0) {
		return 0
	}
	else {
		if (var1 = 0) {
			return 1
		}
		else {
			int ret 
			ret <- var1 - 2
			ret <- even(ret)
			return ret
		}
	}
}




