fun multx ([ ], a) = a
  | multx (x :: L, a) = multx (L, x * a);

fun Multx ([ ], a) = a
  | Multx (r :: R, a) = Mult (R) * mult' (r, a);
