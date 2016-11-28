
CFLAGS= -I. -I${ORACLE_HOME}/precomp/public -I${ORACLE_HOME}/rdbms/public 

CC=cc  +DD64 -g 

LFLAGS=-L${ORACLE_HOME}/lib -lclntsh `cat ${ORACLE_HOME}/lib/ldflags`   `cat ${ORACLE_HOME}/lib/sysliblist`  -lm  -lpthread

ORADIR=${ORACLE_HOME}
ORAINCL=${ORADIR}/precomp/public
PROCFLAGS=\
		include=${ORAINCL} \
		include=${ORADIR}/include

PRECOMP= ${ORACLE_HOME}/bin/proc

OBJS=TpMain.o

all: TP

worker: ${OBJS}
	@echo "Compiling the $@ ..."
	${CC} -o $@ ${OBJS} ${LFLAGS} ${CFLAGS}
	mv TP ../bin/

TpMain.o: TpMain.c
	@echo "Compiling the $< ..."
	${CC} -c  ${CFLAGS} ${LFLAGS} $< -o $@

TpMain.c: TpMain.pc
	@echo "Compiling the $< ..."
	${PRECOMP} ${PROCFLAGS} TpMain.pc 
	
clean:
	rm  *.o 
	rm  TpMain.c
	rm  TpMain.lis
	rm  TP
