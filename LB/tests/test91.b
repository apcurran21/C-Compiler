void main () {
int64 num,divisor
int64 rem,c,i

num <- 100
divisor <- 19

if(divisor=0) :divbyzero :notzero
:divbyzero
print(-1)
return
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
print(num)
return
}
