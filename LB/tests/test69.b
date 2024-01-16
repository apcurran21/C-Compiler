void main () {
    // Create 2 arrays of size 10
    int64 ArrSize
    ArrSize <- 10

    // Create the arrays initialized with 0 through length-1
    int64[] Arr1, Arr2
    Arr1 <- Alloc1DArr (ArrSize)
    Arr2 <- Alloc1DArr (ArrSize)

    // Get the Sum of each array
    int64 Arr1Sum, Arr2Sum
    Arr1Sum <- CalcArrSum(Arr1)
    Arr2Sum <- CalcArrSum(Arr2)

    // Get sum and product of the arrays
    int64 SumOfArr, ProdOfArr
    SumOfArr <- Arr1Sum + Arr2Sum
    ProdOfArr <- Arr1Sum * Arr2Sum

    // Get the dot product of the arrays
    int64 DotProd
    DotProd <- Calc1DArrDot(Arr1, Arr2)

    // Print Array 1 sum
    print(Arr1Sum)
    
    // Print array 2 sum
    print(Arr2Sum)

    // Print sum, product, and dot prod of arrays
    print(SumOfArr)
    print(ProdOfArr)
    print(DotProd)

    return
}

int64 CalcArrSum(int64[] TargetArr) {
    // Initialize loop and sum vars
    int64 ArrLen, Count, ArrSum, CurrElm

    ArrLen <- length TargetArr 0
    Count <- 0
    ArrSum <- 0

    // Get offset and curr elm
    while (Count < ArrLen) :SumLoop :SumStop
    :SumLoop
    CurrElm <- TargetArr[Count]

    // Increment count and add to sum
    Count <- Count + 1
    ArrSum <- ArrSum + CurrElm
    continue
    
    :SumStop
    return ArrSum
}

int64[] Alloc1DArr(int64 ArrSize, int64 InitElmVal) {
    // create array of appropriate size
    int64[] NewArr
    NewArr <- new Array(ArrSize)

    int64 ArrLen, Count, ArrSum

    ArrLen <- length NewArr 0
    Count <- 0
    ArrSum <- 0

    // Get offset and curr elm
    while (Count < ArrLen) :AllocLoop :AllocStop
    :AllocLoop
    NewArr[Count] <- Count

    // Increment count
    Count <- Count + 1
    continue
    
    :AllocStop
    return NewArr
}

int64 Calc1DArrDot(int64[] Arr1, int64[] Arr2) {
    // Initialize loop and sum vars
    int64 ArrLen, Count, ArrDot, CurrElm1, CurrElm2, CurrElmProd

    ArrLen <- length Arr1 0
    Count <- 0
    ArrDot <- 0

    // Get offset and curr elm
    while (Count < ArrLen) :DotLoop :DotStop
    :DotLoop
    CurrElm1 <- Arr1[Count]
    CurrElm2 <- Arr2[Count]
    CurrElmProd <- CurrElm1 * CurrElm2

    // Increment count and add to sum
    Count <- Count + 1
    ArrDot <- ArrDot + CurrElmProd
    continue
    
    :DotStop
    return ArrDot
}