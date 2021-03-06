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
#include "include/common.h"
#include "include/jdn_util.h"
#include "include/common_calc.h"
#include "include/ext.h"

void paschal_algo_check() {
    for (int i = 34; i < 5000; i++) {
	YMD r[5];
	for (int k = 0; k < 5; k++) {
	   r[k] = jc_calcs()[k](i);
	}
	for (int j = 0; j <= 2; j+=2) {
	  YMD r0 = r[0], r1 = r[1], r2 = r[2], r3 = r[3];
          _Bool r0r1 = ymd_equals(r0,r1);
          _Bool r2r1 = ymd_equals(r2,r1);
          _Bool r0r2 = ymd_equals(r0,r2);
          _Bool r3r2 = ymd_equals(r3,r2);
	  if (r0r1 && r2r1 && r0r2 && r3r2) {
	  } else {
	     printf("%d: %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d \r\n", i,
		r0.year, r0.month, r0.day,
		r1.year, r1.month, r1.day,
		r2.year, r2.month, r2.day,
		r3.year, r3.month, r3.day);
	  }
	}
    }
}

int main(int argc, char* argv[]) {
 if (argc > 2) {
    const int year = (int)atof(argv[1]);
    const char* algo = argv[2];
    YMD ymd = jc_calc_any()(year);
    int wd = -1;
    printf("%d/%d/%d\t", ymd.day, ymd.month, ymd.year);
    struct tm tmjc = util_get_tm(ymd);
    ymd = gc_calc_any()(year);
    struct tm tmgc = util_get_tm(ymd);
    printf("%d/%d/%d\r\n", ymd.day, ymd.month, ymd.year);

    printf("%s [%d]\r\n", asctime(&tmjc), tmjc.tm_yday);
    printf("%s [%d]\r\n", asctime(&tmgc), tmgc.tm_yday);
    return 0;
 } else {
    paschal_algo_check();
 }
 return 0;
}
