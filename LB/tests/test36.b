// This test deals with some comparisons with arrays
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
    
    int64 meat
    int64 cheese
    int64 bread
    cheese <- choices[0]
    meat <- choices[1]
    bread <- choices[2]

    // Choose cheese
    if(cheese = 1) :havarti :swiss

    //swiss
    :swiss
    swissChoice()
    goto :cheese_ret

    //havarti
    :havarti
    havartiChoice()
    goto :cheese_ret

    :cheese_ret

    // Choose meat
    if(meat = 1) :salami :turkey

    //turkey
    :turkey
    turkeyChoice()
    goto :meat_ret

    //salami
    :salami
    salamiChoice()
    goto :meat_ret

    :meat_ret

    // Choose bread
    if(bread = 1) :sourdough :rye

    //rye
    :rye
    ryeChoice()
    goto :bread_ret

    //sourdough
    :sourdough
    sourdoughChoice()
    goto :bread_ret

    :bread_ret
    
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
