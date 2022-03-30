fun Mult [ ] = 1 
  | Mult (r :: R) = mult(r) * Mult(R);
