// This test deals with some comparisons with arrays, same as test 6 but with a loop
// prints 1 0 0
void main () {
    int64[] ar
    ar <- new Array(3)
    ar[0] <- 1
    ar[1] <- 0
    ar[2] <- 0
    buildASandwich(ar)
    return
}
void buildASandwich(int64[] choices) {
    
    int64 count
    int64 choice
    count <- 0
    while(count < 3) :body :exit 
    {
        :body
        choice <- choices[count]
        if(choice = 1) :first :second

        :first 
        firstChoice()
        count <- count + 1
        continue

        :second
        secondChoice()
        count <- count + 1
        continue
    }
    :exit
    return
}
void firstChoice() {
    
    print(1)
    return
}
void secondChoice() {
    
    print(0)
    return
}
