#ORACLE_HOME = E:/Oracle11g/app/jwkljh/product/11.1.0/db_1
#-I.-I${ORACLE_HOME}/RDBMS/public -L${ORACLE_HOME}/LIB -L${ORACLE_HOME}/RDBMS/lib \
		-l${ORACLE_HOME}/RDBMS/demo -L${ORACLE_HOME}/OCI/lib/bc  -L${ORACLE_HOME}/OCI/lib/MSVC -lclntsh
#CFLAGS = -I. -I${ORACLE_HOME}/OCI/include/ -I${ORACLE_HOME}/RDBMS/public/ -I${ORACLE_HOME}/RDBMS/demo
#CFLAGS = -I. -I./include_libxl/

#LFLAGS = -L${ORACLE_HOME}/LIB/ -L${ORACLE_HOME}/OCI/lib/bc/  -L${ORACLE_HOME}/OCI/lib/MSVC/ \
		-L${ORACLE_HOME}/RDBMS/lib/
#-I. -I/usr/include/mysql++ -I/usr/include/mysql
#MYSOLIB=-L/media/leodemon/Study/Study/WorkSpace/space_for_study/C__Space/ubuntu_test_cp$(TEST_SOLIB)
MYSOLIB=-L${TEST_SOLIB}

CC = g++ -g
ccc = gcc -g
cca = ar -rsv
#-fPIC表示编译为位置独立的代码
CFLAG = -fPIC
#编译动态库.so
SOFLAG = -shared
# gprof
GP_FLAG = -pg

OBJECTS = test_cpp_main.o
OBJECTS1 = test_cpp_example.o
OBJECTS2 = test_cpp_course.o
OBJECTS3 = test_cpp_else.o test_cpp_tmp.o
OBJECTS4 = test_cpp_mysql.o
OBJECTS5 = test_cpp_linux.o
OBJECTS6 = test_cpp_linux_ph.o
OBJECTS8 = test_cpp_xerces.o
OBJECTC = test_c_tmp.o
OBJECTNOW = test_c_now.o
SERVER_MQ_OBJ = test_mq_server.o
CLIENT_MQ_OBJ = test_mq_client.o
MAIN_MQ_OBJ = test_mq_main.o
OBJC1 = ts_c_stack.o ts_c_queue.o ts_c_tree.o

a: testcpp libexample.so libcourse.so libelse.so libtestmysql.so clean2
main: testcpp clean2
test1: libexample.so clean2
test2: libcourse.so clean2
test3: libelse.so clean2
test4: libtestmysql.so clean2
test5: libtestlinux.so clean2
test6: libtestc.a
test7: testnow clean2
test8: libmyxerces.so clean2
mq: mq_server mq_client clean2
mq2: mq_main clean2
adt: libtsc_stack.so clean2

COMPILING_MSG=@echo "Compiling the $< ..."
LINK_MSG=@echo "Link the $< ..."

testcpp:${OBJECTS}
	${LINK_MSG}
#-s 连接时缩小代码体积
#${CC} -s -o $@ ${OBJECTS} -ldl -lmysqlclient
	${CC} $(GP_FLAG) -s -o $@ ${OBJECTS}  -ldl -lmysqlpp
#%.o:%.cpp
test_cpp_main.o:test_cpp_main.cpp
	${COMPILING_MSG}
#-Wall 编译时显示所有错误和警告信息
#-O2 使用编译优化级别，有O1，O2，O3,级别1-3，级别越高，优化效果越好，但编译时间也越长，所以用等级2最好
	${CC}  $(GP_FLAG) -c -O2 -Wall $< -o $@ $(CFLAG)

libexample.so:${OBJECTS1}
	${LINK_MSG}
#在-L.之前加-Wl,--out-implib,libexample.a就能生成静态库libcpptest.a
#下面-s参数没有加上，为了nm时可以找到函数
	${CC} $(SOFLAG) -o $@ ${OBJECTS1} -L. -liconv

libcourse.so:${OBJECTS2}
	${LINK_MSG}
	${CC} $(SOFLAG) -o $@ ${OBJECTS2}
	mv $@ $(TEST_SOLIB)

libelse.so:${OBJECTS3}
	${LINK_MSG}
#${CC} $(SOFLAG) -o $@ ${OBJECTS3} -L. -lxl -lexample
	${CC} $(SOFLAG) -o $@ ${OBJECTS3} ${MYSOLIB} -ltestlinux -L/usr/lib/ -lxml2
	mv $@ $(TEST_SOLIB)

libtestmysql.so:${OBJECTS4}
	${LINK_MSG}
	${CC} $(SOFLAG) -o $@ ${OBJECTS4} -L. -lmysqlclient
	mv $@ $(TEST_SOLIB)

libtestlinux.so:$(OBJECTS5)
	${LINK_MSG}
	${CC} ${SOFLAG} -o $@ ${OBJECTS5} -lpthread
	mv $@ $(TEST_SOLIB)

testlinux:$(OBJECTS6)
	${LINK_MSG}
	${CC} -s -o $@ ${OBJECTS6} -ldl -lpthread

libmyxerces.so:$(OBJECTS8)
	${LINK_MSG}
	${CC} ${SOFLAG} -o $@ ${OBJECTS8}  -lxerces-c
	mv $@ $(TEST_SOLIB)

libtsc_stack.so:${OBJC1}
	${LINK_MSG}
	${ccc} $(SOFLAG) -o $@ ${OBJC1}
	mv $@ $(TEST_SOLIB)

%.o:%.cpp
	${COMPILING_MSG}
#-DBUILD.so 相当于在头文件中加入#define BUILD.so 
#三字母词编译需要加上参数-trigraphs
	${CC}  -c -DBUILD_DLL -O2 -Wall -trigraphs $< -o $@ $(CFLAG)

testnow:$(OBJECTNOW)
	${LINK_MSG}
	${ccc} -o $@ ${OBJECTNOW} ${MYSOLIB} -ltestc

libtestc.a:$(OBJECTC)
	${LINK_MSG}
	${cca} $@ ${OBJECTC}
	mv $@ $(TEST_SOLIB)

libtestc.so:$(OBJECTC)
	$(LINK_MSG)
	${CC} ${SOFLAG} -o $@ ${OBJECTC}
	mv $@ $(TEST_SOLIB)

mq_server:$(SERVER_MQ_OBJ)
	${LINK_MSG}
	${ccc} -o $@ ${SERVER_MQ_OBJ} -L/home/leodemon/leo/zeromq-4.0.3/src/.libs -lzmq

mq_client:$(CLIENT_MQ_OBJ)
	${LINK_MSG}
	${ccc} -o $@ ${CLIENT_MQ_OBJ} -L/home/leodemon/leo/zeromq-4.0.3/src/.libs -lzmq

mq_main:$(MAIN_MQ_OBJ)
	${LINK_MSG}
	${ccc} -o $@ ${MAIN_MQ_OBJ} -L/home/leodemon/leo/zeromq-4.0.3/src/.libs -lzmq
%.o:%.c
	${COMPILING_MSG}
	${ccc} $(GP_FLAG) -c -O2 -Wall $< -o $@ $(CFLAG)


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

