#ifndef COMMON_H
#define COMMON_H
typedef int YEAR_NUM;  /** AD **/
typedef int MONTH_NUM; /** month in year **/
typedef int DAY_NUM;   /** day in month **/
/** year month day **/
typedef struct {YEAR_NUM year; MONTH_NUM month; DAY_NUM day;} YMD;

typedef YMD (*_calc)(const YEAR_NUM);
#endif
