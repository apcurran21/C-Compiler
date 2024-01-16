void main() {
    :entrance
    int64 r12
    int64 r13
    int64 r14
    int64 rdi
    int64 print_val
    int64 comp
    r12 <- 0
    r13 <- 2
    r14 <- 2
    print_val <- 1
    print(print_val)
    rdi <-3

    print_val <- 900099
    print_val <- print_val >> 5
    print_val <- print_val - 78
    print_val <- print_val * 8
    print(rdi)

    print_val <- r12
    print_val <- print_val + r13
    print_val <- print_val + 1
    print_val <- print_val - 1
    print_val <- print_val + 1

    r12 <- r13
    r13 <- print_val
    r13 <- r13 - 1
    r14 <- r14 + 2
    rdi <- print_val

    :return_label_f
    :a
    return
}
