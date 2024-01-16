// how many prime numbers there are in [0, n)?

void main() {
    int64 res
    res <- primeCount(120)
    // 30
    print(res) 
    return
}

int64 primeCount(int64 n) {
    int64[] isPrime
    isPrime <- new Array(n)

    int64 i
    i <- 0
    
    while (i < n) :intoFor :exitFor 
    {        
        :intoFor
        isPrime[i] <- 1

        i <- i + 1
        continue
    }
    :exitFor
    int64 res
    res <- 0
    i <- 2

    while (i < n) :forInto :forBreak 
    {
        :forInto
        int64 v
        int64 flag
        flag <- isPrime[i]
        if (flag = 1) :isPrime :forContinue
        
        :isPrime
        res <- res + 1
        int64 j
        j <- i * 2
        
        while (j < n) :innerForInto :innerForBreak 
        {    
            :innerForInto
            isPrime[j] <- 0
            j <- j + i
            continue
        }
        :innerForBreak
        :forContinue
        i <- i + 1
        continue
    }
    :forBreak
    return res
}
