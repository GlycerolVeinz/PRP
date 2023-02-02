#ifndef __MY_ASSERT_H__
#define __MY_ASSERT_H__

#include <stdio.h>  //because of fprintf()
#include <stdlib.h> //because of exit() and malloc

#define myAssert(x, line, file) \
   if (!(x)) {\
      fprintf(stderr, "my_assert fail, line: %d, file %s\n", line, file);\
      exit(-1);\
      }
#endif
