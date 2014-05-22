#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

#include <time.h>

#define runtimeError(instance, ...) m_critical(__VA_ARGS__)

#define RESET   "\033[0m"
#define RED     "\033[31;1m"
#define YELLOW  "\033[33;1m"

#define GREEN   "\033[32m"
#define BLUE    "\033[35m"

#define LOG(COL, ...) do { \
  time_t t1; struct tm t;\
  time(&t1); localtime_r(&t1, &t); \
  printf("%02d:%02d.%02d (%15.15s:%4d) > ", t.tm_hour, t.tm_min, t.tm_sec, \
      __FUNCTION__, __LINE__); \
  printf(COL __VA_ARGS__); \
  puts(RESET);\
} while (0)


#define m_message(...) LOG(GREEN, __VA_ARGS__)
#define m_info(...) LOG(BLUE, __VA_ARGS__)
#define m_warning(...) LOG(YELLOW, __VA_ARGS__)
#define m_critical(...) do { LOG(RED, __VA_ARGS__); exit(1); } while (0)

#endif
