void main() {
  tuple t
  int64 l

  // Allocate the tuple
	t <- new Tuple(2)

  // Fetch the length
  l <- length t

  // Print the length of the tuple
  print(l)

	return
}
