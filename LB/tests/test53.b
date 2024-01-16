void main() {
    :entrance
    int64[] rax
    int64 var1
    int64 var2
    int64 var3
    int64 r14

    rax <- make_array()
    var1 <- 2
    var2 <- 1
    var3 <- var1 * 4
    :por_aqui_viene

    int64 temp
    temp <- 7
    var2 <- temp + var2

    var1 <- var1 + 2
    int64 len
    len <- 0
    int64 test

    :hello
    var2 <- var2 * 2
    len <- var2 + 1

    rax <- make_array2()
    print(rax) 
    return
}

int64[] make_array() {
    :entrance
    int64 arg1
    int64 arg2
    int64[] rax
    rax <- new Array(arg1)
    arg1 <- 201
    arg2 <- 17
    return rax
}

int64[] make_array2() {
    :entrance
    int64 arg1
    int64 arg2  
    int64[] rax  
    arg1 <- 21
    arg2 <- 9
    rax <- new Array(arg1)
    return rax
}
