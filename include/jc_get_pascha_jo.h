#include "common.h"
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