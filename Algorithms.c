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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "PaschalComputus.h"

struct tm util_get_tm(YMD);
static enum _algo_idx _algo_idx(const char*);
static YMD util_convert_g(const int);
static YMD util_convert_gregorian(const JDN);
static YMD util_convert_jc(const JDN);
static YMD gc_get_pascha_jo(const YEAR_NUM);

YMD jc_get_pascha_alebedev(const YEAR_NUM year) {
	/** Ref: http://alebedev.narod.ru/app/app01.html **/
	int a = year%19, b = year % 4, c = year % 7,
	d = (19*a + 15) % 30,
	e = (2*b + 4*c + 6*d + 6) % 7,
	z = (d+e);
	int month = (z+25)/35 + 3,
	day = z+22-31*(month/4), y = year;
	YMD r = {y,month,day};
	return r;
}

YMD jc_get_pascha_jo(const YEAR_NUM year) {
	/** Ref: https://orthodoxwiki.org/Paschalion#The_Orthodox_Proposal_of_1923 **/
	int
	G = year%19,
	I = ((19*G)+15)%30,
	J = (year+(year/4) + I)%7,
	L = I - J,
	em = 3+((L+40)/44),
	ed = L + 28 - 31 * (em/4),
	y = year;
	YMD r = {y,em,ed};
	return r;
}

YMD jc_get_pascha_dveri(const YEAR_NUM year) {
	/** Ref: http://synpress-classic.dveri.bg/pasha/index.htm **/
	/**
		Year - номер на годината
		a = Year mod 19
		b = Year mod 4
		c = Year mod 7
		d = (19 * a + 15) mod 30
		e = (2 * b + 4 * c + 6 * d + 6) mod 7,

		Ако (d + e) > 10, то Пасхата по стар стил ще бъде (d + e - 9) април, в противен случай - (22 + d + e) март 
	**/
	int a = year%19, b = year%4, c=year%7, d=(19*a +15) % 30, e = (2*b + 4*c + 6*d + 6) % 7;
	YMD r;
	r.year = year;
	if (10 <= (d + e)) {
		r.month = 4;
		r.day = d+e-9;
	} else {
		r.month = 3;
		r.day = 22+d+e;
	}
	return r;
}

/**
 Table.
**/

/**
**/
typedef struct _MD {
 int day;
 int month;
} MD;

static MD G[19] = {
{12,4},{29,3},{19,4},{5,4},{29,3},{12,4},{5,4},{19,4},{12,4},{29,3},
{19,4},{5,4},{29,3},{19,4},{5,4},{22,3},{12,4},{5,4},{19,4}
};
static int _gr[] = {5,11,16,22};

static MD B[19] = {
 {6,4},{30,3},{20,4},{6,4},{23,3},{13,4},{6,4},{20,4},{13,4},{30,3},
{20,4},{6,4},{30,3},{13,4},{6,4},{23,3},{13,4},{30,3},{20,4}
};
static int _br[] = {4,10,21,27};

static MD A[19] = {
{7,4},{31,3},{14,4},{7,4},{24,3},{14,4},{31,3},{21,4},{14,4},{31,3},
{21,4},{7,4},{31,3},{14,4},{7,4},{24,3},{14,4},{31,3},{21,4}
};
static int _ar[] = {9,15,20,26};

static MD Z[19] = {
{8,4},{1,4},{15,4},{8,4},{25,3},{15,4},{1,4},{22,4},{8,4},{1,4},
{22,4},{8,4},{25,3},{15,4},{8,4},{25,3},{15,4},{1,4},{22,4},
};
static int _zr[] = {3,8,14,25};

static MD S[19] = {
{9,4},{26,3},{16,4},{9,4},{26,3},{16,4},{2,4},{23,4},{9,4},{2,4},
{16,4},{9,4},{26,3},{16,4},{2,4},{26,3},{16,4},{2,4},{23,4}
};
static int _sr[] = {2,13,19,24};

static MD E[19] = {
{10,4},{27,3},{17,4},{3,4},{27,3},{17,4},{3,4},{24,4},{10,4},{3,4},
{17,4},{10,4},{27,3},{17,4},{3,4},{27,3},{10,4},{3,4},{24,4},
};
static int _er[] = {1,7,12,18};

static MD D[19] = {
{11,4},{28,3},{18,4},{4,4},{28,3},{11,4},{4,4},{25,4},{11,4},{28,3},
{18,4},{11,4},{28,3},{18,4},{4,4},{28,3},{11,4},{4,4},{18,4},
};
static int _dr[] = {0,6,17,23};

int compareushort (const void* a, const void* b) {
 int r = ( *(int*)a - *(int*)b );
/**
#ifdef DBG
 printf("%d comparedto %d returns %d\r\n", *(int*)a, *(int*)b, r);
#endif
**/
 return r;
}

YMD jc_get_pascha_vlevitskim(const YEAR_NUM year) {
	/** Ref: http://alebedev.narod.ru/tab/tab11.html **/
	int rm = (int) (year % 28);

	int *pItem;
	MD *md;
	       if(NULL != bsearch(&rm, _gr, 4, sizeof(int), compareushort)) {
		md = G;
	} else if(NULL != bsearch(&rm, _br, 4, sizeof(int), compareushort)) {
		md = B;
	} else if(NULL != bsearch(&rm, _ar, 4, sizeof(int), compareushort)) {
		md = A;
	} else if(NULL != bsearch(&rm, _zr, 4, sizeof(int), compareushort)) {
		md = Z;
	} else if(NULL != bsearch(&rm, _sr, 4, sizeof(int), compareushort)) {
		md = S;
	} else if(NULL != bsearch(&rm, _er, 4, sizeof(int), compareushort)) {
		md = E;
	} else if(NULL != bsearch(&rm, _dr, 4, sizeof(int), compareushort)) {
		md = D;
	} else {
		md = NULL;
	}

	if (md) {
		int rl = year%19;


	MD m = md[rl];

	YMD r = {year,m.month,m.day};
	return r;
	} else {
	return (YMD) {0,0,0};
	}
}

struct tm util_get_tm(YMD ymd) {
	struct tm r;
	r.tm_year = ymd.year - 1900;
	r.tm_mon = ymd.month - 1;
	r.tm_mday = ymd.day;
	return r;
}

static const _calc _jc_get_pascha[5] = {
   jc_get_pascha_vlevitskim,
   jc_get_pascha_jo,
   jc_get_pascha_alebedev,
   jc_get_pascha_dveri,
   jc_get_pascha_jo
 };

static enum _algo_idx {
   vlevitskim, jo, alebedev, dveri, def
} algoidx;

static enum _algo_idx _algo_idx(const char* algo) {
 enum _algo_idx idx;
 if(strcmp(algo, "alebedev") == 0) {
   idx = alebedev;
 } else if (strcmp(algo, "vlevitskim") == 0) {
   idx = vlevitskim;
 } else if (strcmp(algo, "dveri") == 0) {
   idx = dveri;
 } else if (strcmp(algo, "jo") == 0) {
   idx = jo;
 } else {
   idx = def;
 }
 return idx;
}

_calc __jc_calc(const char* algo) {
 return _jc_get_pascha[_algo_idx(algo)];
}
_calc const* __jc_calcs() {
 return _jc_get_pascha;
}

_Bool ymd_equals(const YMD a, const YMD b) {
  _Bool result =
	a.year == b.year &&
	a.month == b.month &&
	a.day == b.day;
  return result;
}

JDN util_convert_jc_jdn(const YMD ymd) {
 int Y=ymd.year, M=ymd.month, D=ymd.day;
 JDN r = 367*Y-
(7 *
(Y + 5001 + (M - 9)/7)
)/4 + (275 * M)/9 + D + 1729777;
 return r;
}
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

static YMD util_convert_g(const int f) {
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
  return util_convert_g(f);
}

static YMD util_convert_jc(const JDN jdn) {
  return util_convert_g(jdn + gcp.j);
}

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

int util_jdn_weekday(const JDN jdn) {
 return (jdn%7) + 1;
}

static YMD gc_get_pascha_jo(const YEAR_NUM year) {
 YMD ymd = jc_get_pascha_jo(year);
 const JDN jdn = util_convert_jc_jdn(ymd);
 ymd = util_convert_gregorian(jdn);
 return ymd;
}

_calc __gc_calc() {
 return gc_get_pascha_jo;
}
