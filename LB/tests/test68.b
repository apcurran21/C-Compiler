void main () {
    // Create 2 arrays of size 10
    int64 ArrSize
    ArrSize <- 10

    // Create the arrays initialized with 2 and 4
    int64[] Arr1, Arr2
    Arr1 <- Alloc1DArr (ArrSize, 2)
    Arr2 <- Alloc1DArr (ArrSize, 4)

    // Get the Sum of each array
    int64 Arr1Sum, Arr2Sum
    Arr1Sum <- CalcArrSum(Arr1)
    Arr2Sum <- CalcArrSum(Arr2)

    // Get sum and product of the arrays
    int64 SumOfArr, ProdOfArr
    SumOfArr <- Arr1Sum + Arr2Sum
    ProdOfArr <- Arr1Sum * Arr2Sum

    // Print Array 1 sum
    print(Arr1Sum)
    
    // Print array 2 sum
    print(Arr2Sum)

    // Print sum and product of arrs
    print(SumOfArr)
    print(ProdOfArr)

    return
}

int64 CalcArrSum(int64[] TargetArr) {
    // Initialize loop and sum vars
    int64 ArrLen, Count, ArrSum, ContLoop, CurrElm

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

    int64 ArrLen
    int64 Count
    int64 ArrSum
    int64 ContLoop

    ArrLen <- length NewArr 0
    Count <- 0
    ArrSum <- 0


    while (Count < ArrLen) :AllocLoop :AllocStop
    // Get offset and curr elm
    :AllocLoop
    NewArr[Count] <- InitElmVal

    // Increment count
    Count <- Count + 1
    continue
    
    :AllocStop
    return NewArr
}

