/**
Царю Небесний, Утешителю, Дух на Истината,
който си навсякъде и всичко изпълваш,
дойди и се всели в нас, очисти ни от всяка сквернота,
и спаси, благии, нашите души!

Свети Боже, Свети Крепки, Свети Безсмъртни,
помилуй нас,
Свети Боже, Свети Крепки, Свети Безсмъртни,
помилуй нас,
Свети Боже, Свети Крепки, Свети Безсмъртни,
помилуй нас.

Слава на Отца и Сина и Светия Дух,
и сега, и винаги и вовеки веков. Амин.

Пресвета Троице, помилуй нас, Господи, очисти греховете ни,
Владико, прости беззаконията ни,
Свети, посети и изцери немощите ни, заради твоето Име.

Господи помилуй, Господи помилуй, Господи помилуй.

Слава на Отца и Сина и Светия Дух,
и сега, и винаги, и вовеки веков. Амин.

Отче наш, който си на небесата, да се свети Твоето Име,
да дойде Твоето Царство, да бъде Твоята Воля,
както на небето, така и на земята. Насъщния ни хляб дай ни днес,
и прости нам дълговете, както и ние прощаваме на нашите длъжници.
И не въведи нас в изкушение, но избави ни от лукавия.

Защото Твое е царството, и силата, и славата на Отца, и Сина,
и Светия Дух, и сега и винаги и вовеки веков. Амин.

---
Господи, Иисусе Христе, Сине Божий, помилуй ме грешния.
Пресвята Владичице, Богородице, спаси нас.
**/

#include "include/common.h"
#include "include/common_calc.h"
#include "include/jdn_util.h"
#include "include/PaschalComputus.h"

static YMD util_convert_jc(const JDN);
/*static JDN util_convert_jc_jdn(const YMD);*/

static YMD _util_convert_g(const int);
static YMD gc_get_pascha_jo(const YEAR_NUM);
static YMD util_convert_gregorian(const JDN);

JDN util_convert_jc_jdn(const YMD ymd) {
 int Y=ymd.year, M=ymd.month, D=ymd.day;
 JDN r = 367*Y-
(7 *
(Y + 5001 + (M - 9)/7)
)/4 + (275 * M)/9 + D + 1729777;
 return r;
}

/**
 Ref: https://en.wikipedia.org/wiki/Julian_day#Julian_or_Gregorian_calendar_from_Julian_day_number
**/
static struct GregorianCalendarParameters {
 const int y;
 const int v;
 const int j;
 const int u;
 const int m;
 const int s;
 const int n;
 const int w;
 const int r;
 const int B;
 const int p;
 const int C;
} gcp = {
 .y=4716,
 .v=3,
 .j=1401,
 .u=5,
 .m=2,
 .s=153,
 .n=12,
 .w=2,
 .r=4,
 .B=274277,
 .p=1461,
 .C=-38
};

static YMD _util_convert_g(const int f) {
 int e = gcp.r*f + gcp.v;
 int g = (e%gcp.p)/gcp.r;
 int h = gcp.u*g + gcp.w;
 YMD r;
 r.day = (h%gcp.s)/gcp.u + 1;
 r.month = ((h/gcp.s+gcp.m)%gcp.n)+1;
 r.year = e/gcp.p - gcp.y + (gcp.n+gcp.m-r.month)/gcp.n;
 return r;
}

static YMD util_convert_gregorian(const JDN jdn) {
  int j = gcp.j, B=gcp.B, C=gcp.C, J=jdn;
  int f = J + j + (((4*J + B)/146097)*3)/4 + C;
  return _util_convert_g(f);
}

static YMD util_convert_jc(const JDN jdn) {
  return _util_convert_g(jdn + gcp.j);
}

/**
 Converts a Julian Day Number to Julian or Gregorian calendar
 YMD as specified in "c_type ct"..
**/
YMD convert_jdn(const JDN jdn, const enum c_type ct) {
	switch (ct) {
		case julian:
		  return util_convert_jc(jdn);
		case gregorian:
		  return util_convert_gregorian(jdn);
		default:
		  return (YMD){0,0,0};
	}
}

/**
 Gets day of week for a Julian Day Number.
**/
int util_jdn_weekday(const JDN jdn) {
 return (jdn%7) + 1;
}

/**
 Gets Pascha YMD for a Gregorian calendar.
**/
static YMD gc_get_pascha_jo(const YEAR_NUM year) {
 YMD ymd = jc_get_pascha_jo(year);
 const JDN jdn = util_convert_jc_jdn(ymd);
 ymd = util_convert_gregorian(jdn);
 return ymd;
}

/**
 Gets a calculator of Pascha for a Gregorian calendar.
**/
_calc gc_calc_any() {
 return gc_get_pascha_jo;
}

/**
 Converts YMD from Gregorian/Julian era to Bizantium era.
Ref:
 http://orthochristian.com/97046.html
 orthodoxwiki.org
**/
YMD util_convert_to_bz(const YMD gc) {
 YMD r = gc;
 r.year = gc.month >= 9 && gc.month <=12 ? 5509 : 5508;
 return r;
}
