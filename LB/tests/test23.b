void main(){
    int64 return_var 
    return_var <- fib(9)
    print(return_var)
    return
}

int64 fib(int64 p1){
    int64 p2, p3, p4, p5, p6
    if (p1 = 0) :ENDzero :TryOne
    :TryOne
    if (p1 = 1) :ENDone :Bigger
    :Bigger
    p2 <- p1 - 2
    p3 <- p1 - 1
    p4 <- fib(p2)
    p5 <- fib(p3)
    p6 <- p4 + p5
    return p6
    :ENDzero
    return 0
    :ENDone
    return 1
}