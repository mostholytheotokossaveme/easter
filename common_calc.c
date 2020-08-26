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
#include "include/common_calc.h"
#include "include/PaschalComputus.h"

static enum _algo_idx _algo_idx(const char*);

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

_calc jc_calc_any(const char* algo) {
 _calc r = _jc_get_pascha[_algo_idx(algo)];
 return r;
}

_calc const* jc_calcs() {
 return _jc_get_pascha;
}

_Bool ymd_equals(const YMD a, const YMD b) {
  _Bool result =
	a.year == b.year &&
	a.month == b.month &&
	a.day == b.day;
  return result;
}

