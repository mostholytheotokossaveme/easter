#ifdef REVISED_JULIAN
#include <time.h>
#ifndef RJepoch
 #define RJepoch 1
#endif
#define RJPriorYear(y) (y - 1)

typedef float RJ_FixedDays;
extern int rj_is_leap_year(const int);
extern RJ_FixedDays rj_get_fixed_days(const YMD);
extern YMD rj_get_ymd(const RJ_FixedDays);
extern int rj_weekday(const RJ_FixedDays);
#endif
