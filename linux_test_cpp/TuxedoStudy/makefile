CC = g++ -g
ccc = gcc -g
cca = ar -rsv
tuxcc = buildclient -f
tuxsc = buildserver -f
#-fPIC表示编译为位置独立的代码
CFLAG = -fPIC
#编译动态库.so
SOFLAG = -shared
#ubuntu13.04 does not support tuxedo 12.1,use the command fix this problem
FixFlag = -Xlinker --no-as-needed

CLIENT = TuxedoClient
SERVER = TuxedoServer

a: tux_client tux_server clean2
client: tux_client clean2
server: tux_server clean2

COMPILING_MSG=@echo "Compiling the $< ..."
LINK_MSG=@echo "Link the $< ..."

tux_client:${CLIENT}.c
	${COMPILING_MSG}
	${tuxcc} "${FixFlag} $<" -o $@

tux_server:${SERVER}.c
	${COMPILING_MSG}
	${tuxsc} "${FixFlag} $<" -o $@ -s TOUPPER

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

