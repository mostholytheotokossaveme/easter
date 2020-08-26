#include <stdio.h>
#include "include/common.h"
#include "include/jdn_util.h"
#include "include/common_calc.h"
#include "include/ext.h"

typedef struct {
 int dow, doy, dsp, dspp, dsnp, year;
} DAY_VAR;

static DAY_VAR new_day(const YMD );
static const int SECONDS_PER_DAY = 3600*24;
static int days_between(struct tm source, struct tm target);

static int days_between(struct tm end, struct tm beginning) {
   time_t difference = difftime(mktime(&end), mktime(&beginning));
   int days = difference / SECONDS_PER_DAY;
   return days;
}

static DAY_VAR new_day(const YMD date) {
  const _calc calc = jc_calc_any();
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
  printf("%d %d\r\n%d %d %d\r\n%d", dv.dow, dv.doy, dv.dsp, dv.dspp, dv.dsnp, year);
}
