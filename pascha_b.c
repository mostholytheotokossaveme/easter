#include <stdio.h>
#include <time.h>
#include "include/common.h"
#include "include/ext.h"
#include "include/jc_get_pascha_jo.h"

typedef struct {
 int dow, doy, dsp, dspp, dsnp, year;
} DAY_VAR;

static DAY_VAR new_day(const YMD);
static const int SECONDS_PER_DAY = 3600*24;
static int days_between(struct tm source, struct tm target);

static int days_between(struct tm end, struct tm beginning) {
   time_t difference = difftime(mktime(&end), mktime(&beginning));
   int days = difference / SECONDS_PER_DAY;
   return days;
}

static DAY_VAR new_day(const YMD date) {
  _calc calc = jc_get_pascha_jo;
  struct tm d = util_get_tm(date);
  const YEAR_NUM year = d.tm_year + 1900;

  YMD prev_pascha = calc(year-1);
  struct tm pp = util_get_tm(prev_pascha);
  YMD this_pascha = calc(year);
  struct tm tp = util_get_tm(this_pascha);
  YMD next_pascha = calc(year+1);
  struct tm np = util_get_tm(next_pascha);

  DAY_VAR dv = {
	d.tm_wday,
	d.tm_yday,
	days_between(d, tp),
	days_between(d, pp),
	days_between(d, np),
	year
  };
  return dv;
}

int main(int argc, char* argv[]) {
   time_t t = time(NULL);
   struct tm* _2day = localtime(&t);
   const struct tm _day = *_2day;
   const YMD ymd = util_get_tmymd(_day);
   printf("%d %d %d\r\n", ymd.day, ymd.month, ymd.year);
   DAY_VAR dv = new_day(ymd);
   printf("Day of week: %d\nDay of year: %d\nDays: since Pascha\t%d\nDays since Previous Pascha %d Days until Next Pascha: %d\nYear:\t%d", dv.dow, dv.doy, dv.dsp, dv.dspp, dv.dsnp, dv.year);
}
