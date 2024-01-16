// This test deals with some calling convention stuff
// prints 2
void main () {
    myF()
    return
}
void myF() {
    myF2(2)
    return
} 
void myF2(int64 arg1) {
    // Save some callee saved registers and do stuff with them
    int64 v1
    int64 v2
    int64 v3
    int64 ret

    v2 <- v1
    v1 <- 2
    v1 <- v1 + 13
    v3 <- 3
    v1 <- v1 + v3

    // Call myF3
    ret <- myF3()

    print(arg1)
    
    return
}
int64 myF3() {
    int64 ret
    ret <- 2 <= 2
    return ret
}

