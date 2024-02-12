(@myF
	0 1
	%S0<- 0
	mem %S0 0 <- %S0
	%S4665686 <- mem rsp 0
	rdi<- %S4665686
	mem %S4665686 0 <- %S4665686
	%S4665687 <- mem rsp 0
	mem :f1_ret -8 <- :f1_ret
	mem %S4665687 0 <- %S4665687
	%S4665688 <- mem rsp 0
	call @myF2 0
	::f1_ret
	return
	)