#include <stdio.h>
int CalcTest();

int main(int argc, char *argv[])
{
	printf("---------Hello World----------\n");
	CalcTest();
	const char *sss="insert into CT_GRPCUSTEXT_INFO_HIS(REPRESENT_TEL,REPRESENT_DUTE,IS_PARK,PARK_NAME,IS_NETACCESS,IS_MARKET,MARKET_TYPE,REPRESENT_NAME,FINISH_FLAG,OP_TIME,LOGIN_ACCEPT,LOGIN_NO,OP_CODE,PAR_UNIT_ID,PAR_UNIT_NAME,LEADER_APPENDIX,KEYMAN_APPENDIX,CONTACT_APPENDIX,SERVICE_FIRST_CLASS,INFO_MNG_DEPT,LEADER_NUM,MID_LEADER_NUM,LEADER_SEX,COMMUNICATION_COSTS,DEVELOP_CLASS_CODE,REGIONTYPE,LATENCYREQUIRE,TRADE_LEVEL,INNET_DESC,IS_NATIONAL_UNIT,PROVINCE,COMM_CHARGE_NAME,COMM_CHARGE_TEL,CONNCT_NAME,CONNCT_TEL,CONNCT_DUTE,CONNCTOFF_TEL,MASTER_NAME,MASTER_PHONE,MESSAGE_CREDIT_GRADE,CUST_ID,IT_EQUIP,TEL_BRANCH,TEL_BUDGET,PERSON_NUM,SUM_NUM,ADSL_NUM,OTHER_NUM,LOVE_SERVICE_MODE,LOVE_REDOUND_MODE,WRITE_OFF_NUM,WRITE_OFF_MONEY,NEW_OPER_MODE,APPLY_TYPE,LEADER_APPLY_FEE,OTHER_COM_INFO,SEMAPHORE_INFO,OPER_NUM,PRODUCT_NUM,LATITUDE_CODE,GUIDELINE_CODE,GUIDELINE_VALUE,CHIEF_SERVICE_NO,RATE_TOP100,GOOD_PROJECT,MARKET_FLAG,BAK2,BAK3,BAK4,BAK5, UPDATE_CODE,UPDATE_TYPE,UPDATE_LOGIN,UPDATE_DATE,UPDATE_TIME,UPDATE_ACCEPT)                                                         select REPRESENT_TEL,REPRESENT_DUTE,IS_PARK,PARK_NAME,IS_NETACCESS,IS_MARKET,MARKET_TYPE,REPRESENT_NAME,FINISH_FLAG,OP_TIME,LOGIN_ACCEPT,LOGIN_NO,OP_CODE,PAR_UNIT_ID,PAR_UNIT_NAME,LEADER_APPENDIX,KEYMAN_APPENDIX,CONTACT_APPENDIX,SERVICE_FIRST_CLASS,INFO_MNG_DEPT,LEADER_NUM,MID_LEADER_NUM,LEADER_SEX,COMMUNICATION_COSTS,DEVELOP_CLASS_CODE,REGIONTYPE,LATENCYREQUIRE,TRADE_LEVEL,INNET_DESC,IS_NATIONAL_UNIT,PROVINCE,COMM_CHARGE_NAME,COMM_CHARGE_TEL,CONNCT_NAME,CONNCT_TEL,CONNCT_DUTE,CONNCTOFF_TEL,MASTER_NAME,MASTER_PHONE,MESSAGE_CREDIT_GRADE,CUST_ID,IT_EQUIP,TEL_BRANCH,TEL_BUDGET,PERSON_NUM,SUM_NUM,ADSL_NUM,OTHER_NUM,LOVE_SERVICE_MODE,LOVE_REDOUND_MODE,WRITE_OFF_NUM,WRITE_OFF_MONEY,NEW_OPER_MODE,APPLY_TYPE,LEADER_APPLY_FEE,OTHER_COM_INFO,SEMAPHORE_INFO,OPER_NUM,PRODUCT_NUM,LATITUDE_CODE,GUIDELINE_CODE,GUIDELINE_VALUE,CHIEF_SERVICE_NO,RATE_TOP100,GOOD_PROJECT,MARKET_FLAG,BAK2,BAK3,BAK4,BAK5,:FUNCTION_CODE<char[5+1]>,decode(UPDATE_TYPE,'U','X','I','D','X','U','D','I'),:LOGIN_NO<char[20+1]>,to_number(substr(:UPDATE_TIME<char[14+1]>,1,8)), to_date(:UPDATE_TIME<char[14+1]>,'YYYYMMDDHH24MISS'), :NEW_ACCEPT<long>                                                   from CT_GRPCUSTEXT_INFO_HIS where UPDATE_ACCEPT=:OLD_ACCEPT<long> and UPDATE_TYPE in ('D','U','I','X')";
	printf("------ssss.len==%d\n", strlen(sss));

	return 0;
}

