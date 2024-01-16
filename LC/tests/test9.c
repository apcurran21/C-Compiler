// prints {s:9, 1, 7, 69, 69, 69, 0, 0, 0, 0} with recursion 
void main () {
    
    int[] ret

    int[] ar
    ar <- new Array(7)
    ar[0] <- 0
    ar[1] <- 0
    ar[2] <- 0


    ret <- func1(ar)
    print(ret)
    return
}

int[] func1(int[] v1) {
    
    int[] ret

    int t1
    int t2
    int t3
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

int[] recurse(int[] v1, int num) {
    
    int[] ret


    int t1
    int t2
    int t3
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
    if(num = 0) {
        return v1
    } else {
        ret <- recurse(v1, num)
        return ret

    }
    return v1
    
}
