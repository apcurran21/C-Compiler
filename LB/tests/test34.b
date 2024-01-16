// prints 69 with recursion 
void main () {
    
    int64 ret

    ret <- func1(0)
    print(ret)
    return
}

int64 func1(int64 v1) {
    
    int64 ret
    v1 <- v1 + 10
    ret <- func2(v1)
    return ret
}

int64 func2(int64 v1) {
    
    int64 ret
    v1 <- v1 + 20
    ret <- func3(v1)
    return ret
}

int64 func3(int64 v1) {
    
    int64 ret
    v1 <- v1 + 30
    ret <- recurse(v1, 9)
    return ret
}

int64 recurse(int64 v1, int64 num) {
    
    int64 ret

    v1 <- v1 + 1
    num <- num - 1
    if(num = 0) :done :notDone
    :notDone

    ret <- recurse(v1, num)
    return ret

    :done
    return v1
}