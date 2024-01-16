void main(){
	int64 cprime, n, v, check, p
	cprime <- 91
	n <- 2
	v <- 0
	while (n < cprime) :loop :return
		:loop
		v <- isdiv(cprime,n)
		if(v = 1) :return :b1
		:b1
		n <- n + 1
		continue
	:return
	p <- v 
	print (p)
	return
}

int64isdiv (int64 d,int64 s){
	int64 check, sub, sub2
	if (s = 0) :error :b1
	:b1
	check <- d < 0
	if (d < 0) :negd :posd
	:posd
	check <- s < 0
	if (s<0) :posdnegs :posdposs
	:posdposs
	sub <- s
	goto :start
	:posdnegs
	sub <- s * -1
	goto :start
	:negd
	d <- d * -1
	check <- s < 0
	if (s < 0) :negdnegs :negdposs
	:negdposs
	sub <- s
	goto :start
	:negdnegs
	sub <- s * -1
	goto :start
	:start
	sub2 <- sub
	while (sub < d) :loop :returnfalse
		:loop
		sub <- sub + sub2
		if (d = sub) :returntrue :b2
		:b2
		continue
	:returntrue
	return 1
	:returnfalse
	return 0
	:error
	return -1
}


