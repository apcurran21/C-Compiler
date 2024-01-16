// print all primes from 0 to 100
void main () {
    int64 limit

    limit <- 100
    sieve (limit)

    return
}

void sieve (int64 limit) {
    int64 argCheck, currentNum, cond

    currentNum <- 0

    while (currentNum <= limit) :start :end
    :start
        cond <- isPrime(currentNum)
        if (cond = 1) :prime :continue
        :prime
            printVal(currentNum)

        :continue
            currentNum <- currentNum + 1

        continue
    :end

    return
}

int64 isPrime (int64 val) {
    int64 cond, true, false, inc, inc_plus_two, inc_squared

    true <- 1 = 1
    false <- 1 = 0

    if (val < 4) :if1 :else1
    :if1
        if (val > 1) :if3 :else3
        :if3
            return true
        :else3
            return false

    :else1
        cond <- mod(val, 2)
        if (cond = 0) :or1_found :or1_next

        :or1_next
        cond <- mod(val, 3)
        if (cond = 0) :or1_found :out1

        :or1_found
            return false

    :out1

    inc <- 5
    inc_squared <- inc * inc

    while (inc_squared <= val) :while1_start :while1_end
    :while1_start
        cond <- mod(val, inc)
        if (cond = 0) :or_true :elif1

        :elif1
        inc_plus_two <- inc + 2
        cond <- mod(val, inc_plus_two)
        if (cond = 0) :or_true :or_false

        :or_true
        return false

        :or_false
        inc <- inc + 6
        inc_squared <- inc * inc

        continue
    :while1_end

    return true
}

int64 mod (int64 val, int64 divisor) {
    int64 remainder

    remainder <- val

    if (remainder >= divisor) :start :finish
    :start
        remainder <- remainder - divisor
        if (remainder >= divisor) :start :finish
    :finish

    return remainder
}

void printVal (int64 val) {
    print (val)
    return
}