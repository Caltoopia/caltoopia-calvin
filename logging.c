#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "logging.h"

void
fail(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  fprintf(stderr, "failed: ");
  vfprintf(stderr, fmt, args);
  va_end(args);

  fprintf(stderr, "\n");

  exit(1);
}

void
warn(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  fprintf(stderr, "warning: ");
  vfprintf(stderr, fmt, args);
  va_end(args);

  fprintf(stderr, "\n");
}



