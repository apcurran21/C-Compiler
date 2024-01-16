// This test deals with some comparisons 
// prints 1 \n 0
void main () {
    buildASandwich(1,0)
    return
}
void buildASandwich(int cheese, int meat) {
    

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

