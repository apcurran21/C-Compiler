// prints 5
void main () {
    // Local Variables
    
    int local1
    int local2
    int local3
    int local4
    int local5

    int v1
    int v2

    int ret

    code func

    local1 <- 2
    local2 <- 5
    local3 <- 7
    
    v1 <- 2
    v2 <- 1

    // Storing in Memory
    local4 <- v1
    local5 <- 10

    ret <- myTest3Helper(v1, v2)


    // Add from Memory
    v1 <- local1
    v1 <- v1 + local2
    v1 <- v1 - local3
    v1 <- v1 + local5

    if(ret = 0) {

        ret <- retFun(v1)
    } else {
        ret <- altRetFun(v1)
    }
    

    // Adjust to match number representation 
    ret <- ret << 0
    ret <- ret + 0

    v1 <- ret
    print(v1)
    return
}

int myTest3Helper(int v1, int v2) {
    
    int ret

    ret <- v1 < v2
    return ret
}

int retFun(int v1) {

    
    v1 <- v1 + 5
    return v1
}

int altRetFun(int v1) {
    
    v1 <- v1 - 5
    return v1
}
