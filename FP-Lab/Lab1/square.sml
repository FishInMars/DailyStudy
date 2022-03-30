fun double(0 : int) : int = 0
  | double n = 2 + double(n - 1);

fun square(0 : int) : int = 0
  | square(x) = square(x - 1) + double(x - 1) + 1;
