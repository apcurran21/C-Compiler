// calculates (and prints) the 20th term of the fibonacci sequence
// with fib(0) = fib(1) = 1

void main(){
        int64 n, result
        n <- 20
        result <- fib(n)
        print(result)
        return
}

int64 fib(int64 n){
        :entry
        int64 not_base
        if(n > 1) :recurse :base

        :base
        return 1

        :recurse
        int64 n_sub_1, fib_n_sub1, n_sub_2, fib_n_sub_2, result
        n_sub_1 <- n - 1
        fib_n_sub1 <- fib(n_sub_1)
        n_sub_2 <- n - 2
        fib_n_sub_2 <- fib(n_sub_2)
        result <- fib_n_sub1 + fib_n_sub_2
        return result
}
