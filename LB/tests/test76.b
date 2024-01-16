void main()
{
  int64 tmp_rax, tmp_rcx, tmp_rdi
  int64 i
  tmp_rcx <- 2
  i <- 1
  while (5 > i) :K1 :end_for_i
:K1
  {
    int64 j
    j <- 1
    while (5 > j) :K2 :end_for_j
:K2
    {
      int64 k
      tmp_rax <- tmp_rax - tmp_rax
      k <- tmp_rax
      k <- 1 + k
      while (1000 > k) :K3 :end_for_k
      {
:K3
        int64 old_rcx
        old_rcx <- tmp_rcx
        tmp_rdi <- k
        tmp_rdi <- tmp_rdi << 1
        print(tmp_rdi)
        tmp_rdi <- i
        tmp_rdi <- tmp_rdi * j
        tmp_rdi <- tmp_rdi * k
        print(tmp_rdi)
        tmp_rcx <- old_rcx
        k <- k << tmp_rcx
        continue
      }
:end_for_k
      j <- 1 + j
      continue
    }
:end_for_j
    i <- 1 + i
    continue
  }
  :end_for_i
  return
}
