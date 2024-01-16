void main () {

int64 n
n <- 25

int64 i,fib_n,fib_1
int64 sum
int64 prod
i <- 2
print(1)
print(1)

fib_n <-1
fib_1 <-1
sum<-fib_n+fib_1
prod <- fib_n*fib_1
int64 temp
{
:loop
temp <-fib_n
fib_n <- fib_n+fib_1
fib_1<-temp

prod <- fib_n*prod
prod <- remainder(prod,200)
if(prod=0) :set :unset
:set
prod<-50
:unset
sum <- sum + fib_n
print(fib_n)
i <- i+1
}
while(i<n) :loop :exit


:exit
print(sum)
print(prod)
return

}

int64 remainder (int64 n, int64 d) {
int64 num,divisor
int64 rem,c,i
num <- n
divisor <- d

if(divisor=0) :divbyzero :notzero
:divbyzero
print(-1)
return -1
:notzero

if(divisor<0) :divneg :divpos
:divneg
divisor <- -1 * divisor
:divpos

if(num<0) :numneg :numpos
:numneg
num <- -1 * num
:numpos

if(num<divisor):exit :loop

:loop
num <- num - divisor
if(num>=divisor) :loop :exit 

:exit
return num
}
