#include "include/ext.h"

struct tm util_get_tm(const YMD ymd) {
        struct tm r;
        r.tm_sec = r.tm_min = r.tm_hour = 0;
        r.tm_year = ymd.year - 1900;
        r.tm_mon = ymd.month - 1;
        r.tm_mday = ymd.day;
        mktime(&r);
        return r;
}

YMD util_get_tmymd(const struct tm tm) {
  YMD r = {
	.year  = 	tm.tm_year + 1900,
	.month =        tm.tm_mon + 1,
	.day   =	tm.tm_mday
	};
	return r;
}

