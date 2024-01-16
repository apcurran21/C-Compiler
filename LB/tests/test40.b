int64 mod(int64 x, int64 y) {
    int64 r
    if (x = 0) :mgood :misneg
    
    :misneg
    if (x > -1) :mloop :ret_early
    :ret_early
    return 0

    :mloop
    x <- x - y
    if (x = 0) :mgood :misneg

    :mgood
    return 1
}

int64 prime(int64 arg) {
    int64 inputIs2
    int64 halfarg
    int64 counter
    int64 pstatus
    int64 reloop

    counter <- 1
    if (arg = 2) :is_prime :prime_loop

    while (counter <= halfarg) :prime_loop :is_prime
    :prime_loop
    halfarg <- arg >> 1
    counter <- counter + 1
    pstatus <- mod(arg, counter)
    if (pstatus = 1) :not_prime :maybe_prime

    :maybe_prime
    continue

    :is_prime
    return 1

    :not_prime
    return 0
}

int64 gpf(int64 arg) {
    int64 argIsPrime
    int64 argNotPrime
    int64 possiblePrime
    int64 modulo
    int64 cndIsPrime
    int64 sad
    
    argIsPrime <- prime(arg)
    if (argIsPrime = 0) :not_itself :itself

    :itself
    return arg
    
    :not_itself
    possiblePrime <- arg >> 1
    possiblePrime <- possiblePrime + 1

    // This loop can't be easily converted without needless verbosity
    //while (cndIsPrime = 0) :gpf_loop :done
    :gpf_loop
    if (possiblePrime < 2) :gpf_done_sad :not_sad

    :not_sad
    possiblePrime <- possiblePrime - 1
    modulo <- mod(arg, possiblePrime)
    if (modulo = 0) :gpf_loop :nloop

    :nloop
    cndIsPrime <- prime(possiblePrime)
    if (cndIsPrime = 0) :gpf_loop :done

    :done
    return possiblePrime
    :gpf_done_sad
    return -1
}

void main() {
    int64 result
    result <- gpf(33030)
    print(result)
    return
}