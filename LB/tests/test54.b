void main() {
 :entrance
 int64[] arr
 arr <- new Array(100)
 int64 ret_val
 ret_val <- max(arr)
 return
}

int64 max(int64[] array) {
    :entrance
    int64 sizeOfArray
    int64 first
    int64 max2
    int64 index

  sizeOfArray <- length array 0
   first <- array[0]
   max2 <- first
   index <- 1

   :loop
   int64 currMultFactor
   int64 curr
   int64 temp
   int64 newMax
   int64 cont
   currMultFactor <- index * 8
   curr <- array[currMultFactor]
   temp <- array[currMultFactor]
   newMax <- temp - max2
    
   :cont
   int64 size
   size <- length array 0
   cont <- size - index

 :setNewMax
  max2 <- temp
  int64 max3
  max3 <- 1 
  return max3
}
