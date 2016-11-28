CC=g++ 

OBJECTS=TestMain.o Test_new.o testUtype.o testTryCatch.o 
all:TestMain

SHOW_MSG=@echo " Compiling the $<" 
TestMain: ${OBJECTS}
	$(SHOW_MSG) 
	${CC} -o $@  ${OBJECTS} -Lutype 
%.o: %.cpp
	$(SHOW_MSG)  
	${CC} -c $< -o $@

clean:
	rm -f *.o 
	rm -f *.lis
	rm -f TestMain.exe
	rm -f *.obj

