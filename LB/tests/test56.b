void main() {
int64[][][] a
int64 l1
int64 c1
int64 l2
int64 c2
int64 l3
int64 c3
int64 sum 
int64 tmp

a <- new Array(5,6,7)
l1 <- length a 0
l2 <- length a 1
l3 <- length a 2
c1 <- l1
c2 <- l2
c3 <- l3
sum <- 0

:first
c1 <- c1 - 1
tmp <- a[c1][0][0] 
sum <- tmp + sum

:second
c2 <- c2 -1
tmp <- a[0][c2][0] 
sum <- tmp + sum

:third
c3 <- c3 - 1
tmp <- a[0][0][c3]
sum <- tmp + sum

:last
print(sum)
return

}
