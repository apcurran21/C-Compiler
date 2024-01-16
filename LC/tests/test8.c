// prints 69 with recursion 
void main () {
    
    int ret

    ret <- func1(0)
    print(ret)
    return
}

int func1(int v1) {
    
    int ret
    v1 <- v1 + 10
    ret <- func2(v1)
    return ret
}

int func2(int v1) {
    
    int ret
    v1 <- v1 + 20
    ret <- func3(v1)
    return ret
}

int func3(int v1) {
    
    int ret
    v1 <- v1 + 30
    ret <- recurse(v1, 9)
    return ret
}

int recurse(int v1, int num) {
    
    int ret

    v1 <- v1 + 1
    num <- num - 1
    if(num = 0) {
        return v1
    } else {
        ret <- recurse(v1, num)
        return ret
    }
    return 0
}
