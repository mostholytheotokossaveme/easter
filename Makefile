objects := main.o ext.o jc_get_pascha_alebedev.o jc_get_pascha_jo.o jc_get_pascha_vlevitskim.o jc_get_pascha_dveri.o common_calc.o jdn_util.o
incl = include/

all :  $(objects)
	cc -o main $(objects)

main.o : main.c ext.c $(incl)eo_liturgical_calendar.h $(incl)rj.h $(incl)jdn_util.h $(incl)common_calc.h $(incl)common.h $(incl)ext.h
common_calc.o : common_calc.c $(incl)PaschalComputus.h $(incl)common_calc.h $(incl)common.h
jdn_util.o : jdn_util.c $(incl)PaschalComputus.h $(incl)common.h
jc_get_pascha_alebedev.o : jc_get_pascha_alebedev.c $(incl)jc_get_pascha_alebedev.h $(incl)common.h
jc_get_pascha_jo.o : jc_get_pascha_jo.c $(incl)jc_get_pascha_jo.h $(incl)common.h
jc_get_pascha_vlevitskim.o : jc_get_pascha_vlevitskim.c $(incl)jc_get_pascha_vlevitskim.h $(incl)common.h
jc_get_pascha_dveri.o : jc_get_pascha_dveri.c $(incl)jc_get_pascha_dveri.h $(incl)common.h

pascha_b.o : pascha_b.c common_calc.c ext.c jc_get_pascha_jo.c $(incl)common.h $(incl)ext.h $(incl)jc_get_pascha_jo.h

ext.o : ext.c $(incl)ext.h
clean :
	rm main $(objects)

b : ext.o pascha_b.o jc_get_pascha_jo.o
	cc -o pascha_b pascha_b.o ext.o jc_get_pascha_jo.o

xml : include/xml/xml.c
	cc  -I/usr/include/libxml2 include/xml/xml.c -o xml -lxml2
