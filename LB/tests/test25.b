//returns the cirumference and area of a circle with the given radius
//then returns the surface area and volume of a sphere with the given radius
//note pi is approximated to 3 and 4/3 * pi is approximated to 4

void main()
{
   int64 radius, value
   radius <- 8
   value <- circ(radius)
   print (value)
   value <- area(radius)
   print (value)
   value <- SA(radius)
   print (value)
   value <- vol(radius)
   print (value)
   return
}

int64 circ(int64 r)
{
   int64 pi, d, c
   pi <- 3
   d <- 2 * r
   c <- d * pi
   return c
}

int64 area(int64 r)
{
   int64 pi, r2, a
   pi <- 3
   r2 <- r * r
   a <- r2 * pi
   return a
}

int64 SA(int64 r)
{
   int64 pi, r2, sa
   pi <- 3
   r2 <- r * r
   r2 <- r2 * 4
   sa <- r2 * pi
   return sa
}

int64 vol(int64 r)
{
   int64 factor, r2, r3, v
   factor <- 4
   r2 <- r * r
   r3 <- r2 * r
   v <- r3 * factor
   return v
}