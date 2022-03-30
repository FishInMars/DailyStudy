fun mult' ([ ], a) = a
  | mult' (x :: L, a) = mult' (L, x * a);

fun Mult' ([ ], a) = a
  | Mult' (r :: R, a) = Mult' (R) * mult' (r, a);
