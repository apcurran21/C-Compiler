void main(){
    int64 var1
    int64 var2
    int64[][] my_V1
    var1 <- 2
    var2 <- 2
    my_V1 <- new Array(var1, var2)
    print(my_V1)
    my_V1[0][0] <- 1
    my_V1[0][1] <- 2
    print(my_V1)
    my_V1[1][0] <- 3
    my_V1[1][1] <- 4
    print(my_V1)
    arrayprint(my_V1)
    return

}

void arrayprint( int64[][] p1){
    int64 element
    element <- p1[0][0]
    print(element)
    element <- p1[0][1]
    print(element)
    element <- p1[1][0]
    print(element)
    element <- p1[1][1]
    print(element)
    return
}