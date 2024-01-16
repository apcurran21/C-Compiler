// how many odd numbers there are in [0, n]?

void main() {
    int64 n
    int64 res
    int64 i
    n <- 120
    res <- 0
    i <- 0

    while (i <= n) :intoWhile :exitWhile 
    {
        :intoWhile
        int64 flag
        flag <- isOdd(i)
        if (flag = 1) :count :notCount
        
        :count
        res <- res + 1
        
        :notCount
        i <- i + 1
        continue
    }
    :exitWhile

    // 60
    print(res) 

    return
}

int64 isOdd(int64 a) {
    a <- a >> 1
    a <- a & 1
    if (a = 1) :yes :no
    
    :no
    return 0

    :yes
    return 1
}
