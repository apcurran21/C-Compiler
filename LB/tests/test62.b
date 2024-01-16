// gcd

void main() {
    int64 res
    // 1
    res <- gcd(541, 7919)
    print(res)
    return
}

int64 gcd(int64 a, int64 b) {
    if (b = 0) :initialConditionTrue :initialConditionFalse
    
    :initialConditionFalse
    int64 aModB
    int64 res
    aModB <- mod(a, b)
    res <- gcd(b, aModB)
    return res
    
    :initialConditionTrue
    return a
}

int64 mod(int64 a, int64 b) {
    int64 i
    int64 res
    i <- 0
    res <- a
    
    while (1 = 1) :intoWhile :exitWhile 
    {
        :intoWhile
        int64 bi
        bi <- b * i
        if (bi <= a) :into :exit
        :into
        res <- a
        res <- res - bi
        i <- i + 1
        continue
    }
    :exitWhile
    :exit
    return res
}
