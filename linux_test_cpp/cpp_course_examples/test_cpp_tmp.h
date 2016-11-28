#ifndef TEST_CPP_TMP_H_
#define TEST_CPP_TMP_H_

#include <map>

int TestGlobeFun(char *);
int WriteLogCtrl(int logLevel, const void *logMsg, ...);
extern "C" int TestFuncParameter(char* puIn);
int TestFuncPara2(int, ...);
int TestFuncPara3(int, int, int, int, int, int);
#endif //TEST_CPP_TMP_H_
