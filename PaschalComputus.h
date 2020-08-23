/**
  день, месяц, год:
*/
#define PASCHAL_COMPUTUS_VERSION "0.1"

typedef int YEAR_NUM;  /** AD **/
typedef int MONTH_NUM; /** month in year **/
typedef int DAY_NUM;   /** day in month **/
typedef int JDN;

/** year month day **/
typedef struct ymd {YEAR_NUM year; MONTH_NUM month; DAY_NUM day;} YMD;

/**
 Ref: http://alebedev.narod.ru/tab/tab11.html
**/
extern YMD jc_get_pascha_vlevitskim(const YEAR_NUM);

/**
 Thanks God for showing me these.
 Ref:
  С.Куликов, Андрей Лебедев.
  http://alebedev.narod.ru/tab/tab17.html,
  http://alebedev.narod.ru/lib/lib07.html,
  http://alebedev.narod.ru/app/app01.html,
  alebedev@narod.ru **/
extern YMD jc_get_pascha_alebedev(const YEAR_NUM);

/**
 * Many notable mathematicians have developed algorithms for determining the date of
 * Orthodox Pascha over the centuries.
 * This simple and elegant one was devised by the brilliant mathematician Jacques Oudin in the 1940s:
 *
 * N.B. -- In this formula MOD is the modulus function,
 * in which the first number is divided by the second and only the remainder is returned.
 * Further, all division is integer division, in which remainders are discarded.
 * Thus 22 MOD 7 = 1 but 22 / 7 = 3.
 *
 * G = year MOD 19
 * I = ((19 * G) + 15) MOD 30
 * J = (year + (year/4) + I) MOD 7
 * L = I - J
 * Easter Month = 3 + ((L + 40)/44)
 * Easter Day = L + 28 - 31 * (Easter Month/4)
 *
 * Easter Month will be a number corresponding to a calendar month
 * (e.g., 4 = April) and Easter Day will be the day of that month.
 * Note that this returns the date of Pascha on the Julian calendar.
 * To get the corresponding date on the Gregorian calendar, add 13 days (14 days after March 1, 2100).
 * Source: https://orthodoxwiki.org/Paschalion#The_Orthodox_Proposal_of_1923
 */
extern YMD jc_get_pascha_jo(const YEAR_NUM);

extern YMD jc_get_pascha_dveri(const YEAR_NUM);

typedef YMD (*_calc)(const YEAR_NUM);

extern JDN util_convert_jc_jdn(const YMD);
extern YMD util_convert_jdn_jc(const JDN);

extern int util_jdn_weekday(const JDN jdn);

extern _calc __jc_calc(const char*);
extern _calc const *  __jc_calcs();
extern _calc __gc_calc();

extern _Bool ymd_equals(const YMD, const YMD);
extern enum c_type { julian, gregorian } c_type;
extern YMD convert_jdn(const JDN, const enum c_type);
