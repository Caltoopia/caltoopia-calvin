#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "logging.h"

int MLOG_USE_COLORS = 0;

void
mlog_enable_colors(void)
{
  MLOG_USE_COLORS = 1;
}

void
mlog_disable_colors(void)
{
  MLOG_USE_COLORS = 0;
}



