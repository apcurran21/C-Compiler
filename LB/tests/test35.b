// prints {s:9, 1, 7, 69, 69, 69, 0, 0, 0, 0} with recursion 
void main () {
    
    int64[] ret

    int64[] ar
    ar <- new Array(7)
    ar[0] <- 0
    ar[1] <- 0
    ar[2] <- 0


    ret <- func1(ar)
    print(ret)
    return
}

int64[] func1(int64[] v1) {
    
    int64[] ret

    int64 t1
    int64 t2
    int64 t3
    t1 <- v1[0]
    t2 <- v1[1]
    t3 <- v1[2]

    t1 <- t1 + 60
    v1[0] <- t1
    t2 <- t2 + 60
    v1[1] <- t2
    t3 <- t3 + 60
    v1[2] <- t3

    ret <- recurse(v1, 9)
    return ret
}

int64[] recurse(int64[] v1, int64 num) {
    
    int64[] ret


    int64 t1
    int64 t2
    int64 t3
    t1 <- v1[0]
    t2 <- v1[1]
    t3 <- v1[2]

    
    t1 <- t1 + 1
    v1[0] <- t1
    t2 <- t2 + 1
    v1[1] <- t2
    t3 <- t3 + 1
    v1[2] <- t3

    num <- num - 1
    if(num = 0) :done :notDone
    :notDone

    ret <- recurse(v1, num)
    return ret

    :done
    return v1
}