ORACLE_HOME = E:/Oracle11g/app/jwkljh/product/11.1.0/db_1
#-I.-I${ORACLE_HOME}/RDBMS/public -L${ORACLE_HOME}/LIB -L${ORACLE_HOME}/RDBMS/lib \
		-l${ORACLE_HOME}/RDBMS/demo -L${ORACLE_HOME}/OCI/lib/bc  -L${ORACLE_HOME}/OCI/lib/MSVC -lclntsh
#CFLAGS = -I. -I${ORACLE_HOME}/OCI/include/ -I${ORACLE_HOME}/RDBMS/public/ -I${ORACLE_HOME}/RDBMS/demo
#CFLAGS = -I. -I./include_libxl/

#LFLAGS = -L${ORACLE_HOME}/LIB/ -L${ORACLE_HOME}/OCI/lib/bc/  -L${ORACLE_HOME}/OCI/lib/MSVC/ \
		-L${ORACLE_HOME}/RDBMS/lib/

CC = g++ -g

OBJECTS = test_cpp_main.o
OBJECTS1 = test_cpp_example.o
OBJECTS2 = test_cpp_course.o
OBJECTS3 = test_cpp_else.o
OBJECTS4 = test_cpp_mysql.o
a: testcpp libexample.dll libcourse.dll libelse.dll libtestmysql.dll clean2
main: testcpp clean2
test1: libexample.dll clean2
test2: libcourse.dll clean2
test3: libelse.dll clean2
test4: libtestmysql.dll clean2

COMPILING_MSG=@echo "Compiling the $< ..."
LINK_MSG=@echo "Link the $< ..."

testcpp:${OBJECTS}
	${LINK_MSG}
#-s 连接时缩小代码体积
	${CC} -s -o $@ ${OBJECTS} -L. -lmysql
#%.o:%.cpp
test_cpp_main.o:test_cpp_main.cpp
	${COMPILING_MSG}
#-Wall 编译时显示所有错误和警告信息
#-O2 使用编译优化级别，有O1，O2，O3,级别1-3，级别越高，优化效果越好，但编译时间也越长，所以用等级2最好
	${CC}  -c -O2 -Wall $< -o $@

libexample.dll:${OBJECTS1}
	${LINK_MSG}
#在-L.之前加-Wl,--out-implib,libexample.a就能生成静态库libcpptest.a
#下面-s参数没有加上，为了nm时可以找到函数
	${CC} -shared -o $@ ${OBJECTS1} -L. -liconv

libcourse.dll:${OBJECTS2}
	${LINK_MSG}
	${CC} -shared -o $@ ${OBJECTS2}
	mv $@ ./solib/

libelse.dll:${OBJECTS3}
	${LINK_MSG}
	${CC} -shared -o $@ ${OBJECTS3} -L. -lxl -lexample
	mv $@ ./solib/

libtestmysql.dll:${OBJECTS4}
	${LINK_MSG}
	${CC} -shared -o $@ ${OBJECTS4} -L. -lmysql
	mv $@ ./solib/

%.o:%.cpp
	${COMPILING_MSG}
#-DBUILD_DLL 相当于在头文件中加入#define BUILD_DLL 
	${CC}  -c -DBUILD_DLL -O2 -Wall $< -o $@


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

