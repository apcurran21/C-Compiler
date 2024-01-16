void main () {
    // Create arrays of size 10 and size 20 
    int64 Arr1Size, Arr2Size
    Arr1Size <- 10
    Arr2Size <- 20

    // both initialized with 11
    int64[] Arr1, Arr2
    Arr1 <- Alloc1DArr (Arr1Size, 11)
    Arr2 <- Alloc1DArr (Arr2Size, 11)

    // Get sum of both arrays
    int64 Arr1Sum, Arr2Sum
    Arr1Sum <- CalcArrSum(Arr1)
    Arr2Sum <- CalcArrSum(Arr2)

    // Print the sum of the larger array
    int64 Arr1Larger
    if (Arr2Sum < Arr1Sum) :PrintArr1Sum :PrintArr2Sum

    // Print Array 1 sum
    :PrintArr1Sum
    print(Arr1Sum)
    return
    
    // Print array 2 sum
    :PrintArr2Sum
    print(Arr2Sum)
    return 
}

int64 CalcArrSum(int64[] TargetArr) {
    // Initialize loop and sum vars
    int64 ArrLen, Count, ArrSum, CurrElm, TempCount

    ArrLen <- length TargetArr 0
    Count <- 0
    ArrSum <- 0

    // Get offset and curr elm
    while (Count < ArrLen) :SumLoop :SumStop
    {
        :SumLoop
        CurrElm <- TargetArr[Count]

        // Increment count and add to sum
        TempCount <- Count
        Count <- TempCount + 1
        ArrSum <- ArrSum + CurrElm
        continue
    }
    :SumStop
    return ArrSum
}

int64[] Alloc1DArr(int64 ArrSize, int64 InitElmVal) {
    // create array of appropriate size
    int64[] NewArr
    NewArr <- new Array(ArrSize)

    int64 ArrLen, Count, TempCount

    ArrLen <- length NewArr 0
    Count <- 0

    // Get offset and curr elm
    while (Count < ArrLen) :AllocLoop :AllocStop
    {
        :AllocLoop
        NewArr[Count] <- InitElmVal
        // Increment count
        TempCount <- Count
        Count <- TempCount + 1
        continue
    }
    :AllocStop
    return NewArr
}