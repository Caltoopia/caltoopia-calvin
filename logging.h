#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

#include <time.h>

#define runtimeError(instance, ...) m_critical(__VA_ARGS__)

#define RESET   "\033[0m"
#define RED     "\033[31;1m"
#define YELLOW  "\033[33;1m"

#define GREEN   "\033[32m"
#define BLUE    "\033[34m"

#define LOG(COL, ...) do { \
  time_t unlikely_variable_name_t1; struct tm unlikely_variable_name_t;\
  time(&unlikely_variable_name_t1); \
  localtime_r(&unlikely_variable_name_t1, &unlikely_variable_name_t); \
  printf("%02d:%02d.%02d (%15.15s:%4d) > ", unlikely_variable_name_t.tm_hour, \
      unlikely_variable_name_t.tm_min, unlikely_variable_name_t.tm_sec, \
      __FUNCTION__, __LINE__); \
  printf(COL __VA_ARGS__); \
  puts(RESET);\
} while (0)


#define m_message(...) LOG(GREEN, __VA_ARGS__)
#define m_info(...) LOG(BLUE, __VA_ARGS__)
#define m_warning(...) LOG(YELLOW, __VA_ARGS__)
#define m_critical(...) do { LOG(RED, __VA_ARGS__); exit(1); } while (0)

#endif
