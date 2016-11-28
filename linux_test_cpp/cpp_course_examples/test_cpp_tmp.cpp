#include "test_cpp_main.h"
#include "test_cpp_tmp.h"

map<int, string> FixMap;
#define VAR_HD "~{"
#define VAR_TL "}~"

int TestGlobeFun(char *strDes)
{
	/* WriteLogCtrl(2, "in TestGlobeFun, puIn==[%s]", puIn);*/

	//cout<<"-----------in TestGlobeFun"<<endl;
	//FILE *fp = NULL;
	//if((fp = fopen("./log123", "r")) == NULL)//标准输出重定向到日志文件
	//{
	////cout<<"-------errormsg=="<<strerror(errno)<<endl;
	//WriteLogCtrl(2, "errno==[%d], errmsg==[%s]", errno, strerror(errno));
	//return -2;
	//}
	/*fclose(fp)strDes;*/

	//WriteLogCtrl(2, "in RepFileVar, strDes==[%s]", strDes);
	printf("---------------------in RepFileVar, strDes==[%s]\n", strDes);
	fprintf(stderr, "++++++++++++in TestGlobeFun, strDes==[%s]\n", strDes);

	FixMap.insert(map<int, string>::value_type(100, "||abc123||"));
	FixMap.insert(map<int, string>::value_type(109, "||xyz||"));
	FixMap.insert(map<int, string>::value_type(230, "||china2012||"));
	FixMap.insert(map<int, string>::value_type(118, "||bingo||"));
	FixMap.insert(map<int, string>::value_type(120, "||168001||"));
	FixMap.insert(map<int, string>::value_type(129, "**love999**"));
	FixMap.insert(map<int, string>::value_type(116, ""));

	char strTmp[256];
	char strFixId[10];
	char strFixValue[64];
	memset(strTmp, '\0', sizeof(strTmp));
	memset(strFixId, '\0', sizeof(strFixId));
	memset(strFixValue, '\0', sizeof(strFixValue));
	strncpy(strTmp, strDes, sizeof(strTmp)-1);
	memset(strDes, '\0', sizeof(strDes));
	char *strTmpDes = strTmp;

	char *hdPos = NULL;
	char *hdPos2 = NULL;
	char *tlPos = NULL;
	map<int, string>::iterator bimit;
	while((hdPos = strstr(strTmpDes, VAR_HD)) != NULL)
	{
		if((tlPos = strstr(hdPos+strlen(VAR_HD), VAR_TL)) != NULL)
		{
			if((hdPos2 = strstr(hdPos+strlen(VAR_HD), VAR_HD)) != NULL)
			{
				if(hdPos2 > tlPos)
				{
					memset(strFixId, '\0', sizeof(strFixId));
					*hdPos = '\0';
					strcat(strDes, strTmpDes);
					strncpy(strFixId, hdPos+strlen(VAR_HD), tlPos-hdPos-strlen(VAR_HD));
					memset(strFixValue, '\0', sizeof(strFixValue));
					cout<<"--------xxx--strFixId=="<<strFixId<<endl;
					fprintf(stderr, "***********strFixId==%s\n", strFixId);

					int chkFlag = 0;
					bimit = FixMap.find(atoi(strFixId));
					if(bimit == FixMap.end())
					{
						chkFlag = 1;
					}
					else if(bimit->second == "")
					{
						chkFlag = 1;
					}
					if(chkFlag == 1)
					{
						//WriteLogCtrl(4, "%s | %d | 变量BALA_FIX_ID==[%s]值为空或未配置,请核实!", __FUNCTION__, __LINE__, strFixId);
						printf("%s | %d | 变量BALA_FIX_ID==[%s]值为空或未配置,请核实!\n", __FUNCTION__, __LINE__, strFixId);
						return -1;
					}
					snprintf(strFixValue, sizeof(strFixValue)-1, "%s", bimit->second.c_str());
					strcat(strDes, strFixValue);
					strTmpDes = tlPos + strlen(VAR_TL);
				}
				else
				{
					cout<<"------come in...VAR_HD[0]=="<<VAR_HD[0]<<endl;
					*hdPos2 = '\0';
					strcat(strDes, strTmpDes);
					*hdPos2 = VAR_HD[0];
					strTmpDes = hdPos2;
				}
			}
			else
			{
				memset(strFixId, '\0', sizeof(strFixId));
				*hdPos = '\0';
				strcat(strDes, strTmpDes);
				strncpy(strFixId, hdPos+strlen(VAR_HD), tlPos-hdPos-strlen(VAR_HD));
				memset(strFixValue, '\0', sizeof(strFixValue));
				cout<<"---zzz-----strFixId=="<<strFixId<<endl;

				int chkFlag = 0;
				bimit = FixMap.find(atoi(strFixId));
				if(bimit == FixMap.end())
				{
					chkFlag = 1;
				}
				else if(bimit->second == "")
				{
					chkFlag = 1;
				}
				if(chkFlag == 1)
				{
					//WriteLogCtrl(4, "%s | %d | 变量BALA_FIX_ID==[%s]值为空或未配置,请核实!", __FUNCTION__, __LINE__, strFixId);
					printf("%s | %d | BALA_FIX_ID==[%s] value is null\n", __FUNCTION__, __LINE__, strFixId);
					fprintf(stderr, "***********strFixId==%s value is null\n", strFixId);
					return -1;
				}
				snprintf(strFixValue, sizeof(strFixValue)-1, "%s", bimit->second.c_str());
				strcat(strDes, strFixValue);
				strTmpDes = tlPos + strlen(VAR_TL);
			}
		}
		else
		{
			cout<<"------come in2...VAR_HD[1]=="<<VAR_HD[1]<<endl;
			strcat(strDes, strTmpDes);
			*strTmpDes='\0';
		}
	}
	if(strTmpDes[0] != '\0')
	{
		cout<<"-----come in3..."<<endl;
		strcat(strDes, strTmpDes);
	}
	hdPos = NULL;
	hdPos2 = NULL;
	tlPos = NULL;
	strTmpDes = NULL;

	//WriteLogCtrl(2, "out RepFileVar, strDes==[%s]", strDes);
	printf("------------------------out RepFileVar, strDes==[%s]\n", strDes);
	fprintf(stderr, "++++++++++++out RepFileVar, strDes==[%s]\n", strDes);

	return 0;
}


//测试函数入参是以从右到左的形式依次存放在堆栈当中
int TestFuncParameter(char* puIn)
{
	cout<<"-------in TestFuncParameter-------puIn==["<<puIn<<"]"<<endl;
	TestFuncPara2(5,3,9,10,20,30);
	TestFuncPara3(5,3,9,10,20,30);
	cout<<"-------out TestFuncParameter-------"<<endl;

	return 0;
}

int TestFuncPara2(int a, ...)
{
	cout<<"-------in TestFuncPara2-------"<<endl;
	cout<<"sizeof(int)=="<<sizeof(int)<<",,sizeof(int*)=="<<sizeof(int*)<<endl;
	int *p = &a;
	cout<<"p=="<<p<<",*p=="<<*p<<endl;
	p--;
	for(int i=0;i<a;i++)
	{
		cout<<"p=="<<p<<",*p=="<<*p<<endl;
		p--;
	}
	p = NULL;
	cout<<"-------out TestFuncPara2-------"<<endl;

	return 0;
}

int TestFuncPara3(int a, int b, int c, int d, int e, int f)
{
	cout<<"-------in TestFuncPara3-------"<<endl;
	int *p = &a;
	cout<<"p=="<<p<<",*p=="<<*p<<endl;
	p = &b;
	cout<<"p=="<<p<<",*p=="<<*p<<endl;
	p = &c;
	cout<<"p=="<<p<<",*p=="<<*p<<endl;
	p = &d;
	cout<<"p=="<<p<<",*p=="<<*p<<endl;
	p = &e;
	cout<<"p=="<<p<<",*p=="<<*p<<endl;
	p = &f;
	cout<<"p=="<<p<<",*p=="<<*p<<endl;
	cout<<"-------out TestFuncPara3-------"<<endl;
	return 0;
}

