#include "common.h"

typedef int JDN;
extern JDN util_convert_jc_jdn(const YMD);
extern YMD util_convert_jdn_jc(const JDN);
extern int util_jdn_weekday(const JDN jdn);
extern enum c_type { julian, gregorian } c_type;
extern YMD convert_jdn(const JDN, const enum c_type);
extern YMD util_convert_to_bz(const YMD);
