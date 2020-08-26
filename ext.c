#include "include/ext.h"

struct tm util_get_tm(YMD ymd) {
        struct tm r;
        r.tm_sec = r.tm_min = r.tm_hour = 0;
        r.tm_year = ymd.year - 1900;
        r.tm_mon = ymd.month - 1;
        r.tm_mday = ymd.day;
        mktime(&r);
        return r;
}
