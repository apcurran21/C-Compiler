int64 succ(int64 uu1, int64 uu2, int64 uu3, int64 uu4, int64 uu5, int64 uu6, int64 n, int64 uu8, int64 uu9, int64 uu10) {
  int64 m
  m <- n + 1
  return m
}

int64 sum_to(int64 uu1, int64 uu2, int64 uu3, int64 uu4, int64 uu5, int64 uu6, int64 to) {
  int64 sum, from, tmp_rdx, rsp_16, tmp_rax
  sum <- 0
  from <- 0
  tmp_rdx <- to
  while (tmp_rdx >= from) :do :end_sum
  {
:do
    sum <- sum + from
    rsp_16 <- from
    tmp_rax <- succ(uu1, uu2, uu3, uu4, uu5, uu6, rsp_16, 8, 9, 10)
    from <- tmp_rax
    tmp_rdx <- to
    continue
  }
:end_sum
  return sum
}

void main() {
  int64 i
  int64 tmp_r12, tmp_rax, tmp_rdi, tmp_rdx, rsp_16
  i <- 0
:for_go
  while (i <= 20) :next_go :end_go
:next_go
    tmp_r12 <- i
    rsp_16 <- tmp_r12
    tmp_r12 <- tmp_r12 + 1
    tmp_rax <- sum_to(1, 2, 3, 4, 5, 6, rsp_16)
    tmp_rdi <- tmp_rax
    print(tmp_rdi)
    i <- tmp_r12
    continue
:end_go
  return
}
