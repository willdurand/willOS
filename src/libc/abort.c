#include <stdio.h>
#include <stdlib.h>

#if defined(__is_libk)
#include <kernel/panic.h>
#endif

__attribute__((__noreturn__)) void abort(void)
{
#if defined(__is_libk)
  PANIC("abort()");
#else
  // TODO: Abnormally terminate the process as if by SIGABRT.
  printf("abort() was called\n");
#endif

  while (1) {
    ;
  }
  __builtin_unreachable();
}
