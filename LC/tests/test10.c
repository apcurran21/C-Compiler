// This test deals with some comparisons with arrays
// prints 1 0 0
void main () {
    int[] ar
    ar <- new Array(3)
    ar[0] <- 1
    ar[1] <- 0
    ar[2] <- 0
    buildASandwich(ar)
    return
}
void buildASandwich(int[] choices) {
    
    int meat
    int cheese
    int bread
    cheese <- choices[0]
    meat <- choices[1]
    bread <- choices[2]
// Choose cheese
    if(cheese = 1) {
        havartiChoice()
    } 
    else {
        
        swissChoice()
    }

        // Choose meat
    if(meat = 1) {
        salamiChoice()
    } 
    else {
        
        turkeyChoice()
    }

          // Choose bread
    if(bread = 1) {
        sourdoughChoice()
    } 
    else {
        
        ryeChoice()
    }
    return  
}
void havartiChoice() {
    
    print(1)
    return
}
void swissChoice() {
    
    print(0)
    return
}

void salamiChoice() {
    
    print(1)
    return
}

void turkeyChoice() {
    
    print(0)
    return
}


void sourdoughChoice() {
    
    print(1)
    return
}
void ryeChoice() {
    
    print(0)
    return
}
