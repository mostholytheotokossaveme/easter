/**
Eastern Orthodox Liturgical Calendar.

Свят, Свят, Свят е Господ Саваот

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

#include "PaschalComputus.h"
#include <time.h>

#define JC_PASCHA(y) jc_get_pascha_alebedev(y)
#define GC_PASCHA(y) __gc_calc()(y)

/**
 Returns day of week.
**/
static YMD eo_day_of_week_before(const YMD,const int/*i.e. 0-6 */);
static YMD eo_days_after(const YMD,const int);

/**
In addition, the feast day of the patron saint of a parish church or monastery is counted
as a Great Feast, and is celebrated with great solemnity.
**/
static enum GF {
 NATIVITY_OF_THE_THEOTOKOS,
 ELEVATION_OF_THE_HOLY_CROSS,
 PRESENTATION_OF_THE_THEOTOKOS,
 NATIVITY_OF_THE_LORD,
 ANNUNCIATION,
 TRANSFIGURATION,
 DORMINION_FALLING_ASLEEP
} gf;

static struct feast {
 enum GF gf;
 MD md;
} f;


static struct feast feasts[] = {
 {NATIVITY_OF_THE_THEOTOKOS, {21,9}}
};


