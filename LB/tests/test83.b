void main () {
	int64 ret 
	ret <- max (15, 5, 3, 11)
    ret <- ret << 1
    ret <- ret + 1
    print (ret)
    ret <- max (1, 5, 77, 15)
    ret <- ret << 1
    ret <- ret + 1
    print (ret)  
    return
}

int64 max(int64 v1, int64 v2, int64 v3, int64 v4){

	int64 test
	test <- v2 < v1
    if (test = 0) :entry2 :max2

    :entry2
    v1 <- v2
    goto :max2

    :max2
    test <- v3 < v1 
    if (test = 0) :entry3 :max3

    :entry3
    v1 <- v3
    goto :max3

    :max3
    test <- v4 < v1 
    if (test = 0) :entry4 :max4

    :entry4
    v1 <- v4
    goto :max4

    :max4
    
    return v1
}

