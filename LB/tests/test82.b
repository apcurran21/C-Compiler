void main() {
	fib (0)

    fib (1)

    fib (15)

    fib (40)

    return
}

int64 next (int64 v1, int64 v2){ 
	int64 ret
    ret <- v1 + v2
    return ret
}

void fib(int64 v1) {
	int64 var1, var2, var3, var4, var5, var6, ret, test

	var1 <- v1
    var2 <- 0
    var3 <- 0
    var4 <- 1
    goto :loop
    :loop
    var6 <- var1
    var5 <- var2
    test <- var6 = var5 
    if (test = 0) :notend :end
    :notend
    var6 <- var3
    var6 <- var6 << 1
    var6 <- var6 + 1
    print (var6)

    var6 <- var3
    var5 <- var4
    ret <- next(var6, var5)

    var6 <- var4
    var3 <- var6
    var4 <- ret

    var6 <- var2
    var6 <- var6 + 1
    var2 <- var6
    goto :loop

    :end
    return


}
