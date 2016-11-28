MYSOLIB=-L${TEST_SOLIB}

CC = g++ -g
ccc = gcc -g
cca = ar -rsv
#-fPIC表示编译为位置独立的代码
CFLAG = -fPIC
#编译动态库.so
SOFLAG = -shared

OBJECTS = learn_cpp_main.o
OBJECTS1= learn_cpp_otl.o
OBJECTS2= learn_cpp_ipc.o

main: learncpp clean2
myotl: libMyOtlEg.so clean2
ipc: libMyIpc.so clean2

COMPILING_MSG=@echo "Compiling the $< ..."
LINK_MSG=@echo "Link the $< ..."

learncpp:${OBJECTS}
	${LINK_MSG}
#-s 连接时缩小代码体积
	${CC} -s -o $@ ${OBJECTS}  -ldl -lmyodbc5a
#%.o:%.cpp
learn_cpp_main.o:learn_cpp_main.cpp
	${COMPILING_MSG}
#-Wall 编译时显示所有错误和警告信息
#-O2 使用编译优化级别，有O1，O2，O3,级别1-3，级别越高，优化效果越好，但编译时间也越长，所以用等级2最好
	${CC}  -c -O2 -Wall $< -o $@ $(CFLAG)

libMyOtlEg.so:$(OBJECTS1) 
	${LINK_MSG}
	${CC}  ${SOFLAG} -s -o $@ ${OBJECTS1}  -lmyodbc5a
	mv $@ $(TEST_SOLIB)

libMyIpc.so:$(OBJECTS2) 
	${LINK_MSG}
	${CC}  ${SOFLAG} -s -o $@ ${OBJECTS2}
	mv $@ $(TEST_SOLIB)


%.o:%.cpp
	${COMPILING_MSG}
#-DBUILD.so 相当于在头文件中加入#define BUILD.so 
#三字母词编译需要加上参数-trigraphs
	${CC}  -c -DBUILD_DLL -O2 -Wall -trigraphs $< -o $@ $(CFLAG)

%.o:%.c
	${COMPILING_MSG}
	${ccc}  -c -O2 -Wall $< -o $@ $(CFLAG)


.PHONY:clean
clean:
	rm -f *.o
	rm -f *.obj
	rm -f *.lis
	rm -f *~
	rm -f *.a

.PHONY:clean2
clean2:
	rm -f *.obj
	rm -f *.lis
	rm -f *~

