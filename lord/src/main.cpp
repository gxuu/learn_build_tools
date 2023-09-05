
#include <stdio.h>
#include "normal/math/basic_arithmetic.h"
#include "normal/strutil/util.h" 
#include "math/basic_arithmetic.h"
#include "strutil/str.h"



int main()
{
  // this is local
  hello();

  // normal lib
  hello_from_normal_lib();

  // must be local when def present, because they are added first 
  printf("%d\n", add(2, 3));
}
