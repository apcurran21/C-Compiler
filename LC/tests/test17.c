void main() {
	fib (0)

    fib (1)

    fib (15)

    fib (40)

    return
}


int fib(int v) {
	if (v = 1) {
        return 1
    }
    else {
        if (v = 0) {
            return 0
        }
        else {
            int v1
            int v2
            v1 <- v - 1
            v2 <- v - 2
            v1 <- fib(v1)
            v2 <- fib(v2)
            v2 <- v2 + v1
            return v2
        }
    }
    return 0


}
