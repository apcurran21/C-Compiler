void main () {
	int64 var1, var2, var3, var4, ret

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

int64 even (int64 var1) {
	:loop1
	int64 test, ret
	test <- var1 < 0
	if (test = 0) :ok2 :odd1
	:ok2
	test <- var1 = 0
	if (test = 0) :ok3 :correct1
	:ok3
	var1 <- var1 - 2
	goto :loop1
	:odd1
	ret <- 0
	return ret
	:correct1
	ret <- 1
	return ret
}




