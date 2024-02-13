(@myF
	0 1
	%S0 <- 0
	mem %S0 0 <- rsp
	%S1 <- mem rsp 0
	rdi <- %S1
	mem rsp -8 <- :f1_ret
	call @myF2 0
	::f1_ret
	return
	)