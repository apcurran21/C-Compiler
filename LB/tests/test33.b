// This test deals with some comparisons 
// prints 1 \n 0
void main () {
    buildASandwich(1,0)
    return
}
void buildASandwich(int64 cheese, int64 meat) {
    

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

