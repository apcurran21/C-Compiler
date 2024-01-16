void main () {
	int ret 
	ret <- max (15, 5, 3, 11)
    print (ret)
    ret <- max (1, 5, 77, 15)
    print (ret)  
    return
}

int max(int v1, int v2, int v3, int v4){

	if (v2 > v1) {
        v1 <- v2
    }
    else {

    }
    if (v3 > v1) {
        v1 <- v3
    }
    else {

    }
    if (v4 > v1) {
        v1 <- v4
    }
    else {

    }
    return v1;

}

