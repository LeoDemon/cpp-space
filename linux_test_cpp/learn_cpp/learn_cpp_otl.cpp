/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_otl.cpp
 *
 *    Description:  study otl...
 *
 *        Version:  1.0
 *        Created:  2012/5/23 22:49:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#include "learn_otl_pub.h"
#include "learn_cpp_main.h"
#include "learn_cpp_otl.h"


//int TestOtl()
//{
//    cout<<"...in TestOtl..."<<endl;
//
//    otl_connect tdb;
//    char test_conn[64]="dbcustopr/dbcustopr@sxcrma";
//
//    if(OtlConnectDb(test_conn, tdb) != 0)
//    {
//        cout<<"Connect db failed!"<<endl;
//        return -1;
//    }
//
//    OtlDisConnectDb(tdb);
//
//    cout<<"...out TestOtl..."<<endl;
//
//    return 0;
//}
//
//
////连接数据库
//int OtlConnectDb(char *test_conn, otl_connect &tdb)
//{
//    cout<<"...in OtlConnectDb..."<<endl;
//
//    try
//    {
//        otl_connect::otl_initialize();
//        tdb.rlogon(test_conn);
//        tdb.auto_commit_off();
//        cout<<"Connect db success..."<<endl;
//    }
//    catch(otl_exception &p)
//    {
//        cout<<"Connect error: "<<p.msg<<", "<<p.stm_text<<", "<<p.var_info<<endl;
//        return -1;
//    }
//
//    cout<<"...out OtlConnectDb..."<<endl;
//
//    return 0;
//}
//
//
////断开数据库连接
//int OtlDisConnectDb(otl_connect &tdb)
//{
//    cout<<"...in OtlDisConnectDb..."<<endl;
//
//    tdb.rollback();
//    tdb.logoff();
//    cout<<"DisConnect db success..."<<endl;
//
//    cout<<"...out OtlDisConnectDb..."<<endl;
//    return 0;
//}
//
//otl insert mysql text column
int InsOtlMysql(const char* puIn, otl_connect* otlDB)
{
    printf("-----in InsOtlMysql------\n");
    otl_nocommit_stream otlOrderLine;
    otl_nocommit_stream otlexcp;
    otlOrderLine.set_flush(false);
    const char* textStr="<?xml version=\"1.0\" encoding=\"UTF-8\"?><BODY><IDNO>22320001188664</IDNO><PHONENO>14755607233</PHONENO><NEWSTATUS>A</NEWSTATUS><CHGTIME>20140804160404</CHGTIME><EFFDATE>20140804160404</EFFDATE><EXPDATE>20500101010101</EXPDATE><CHGREASON>手工停开机</CHGREASON></BODY>";
    int iLen = strlen(textStr);
    printf("---puIn==[%s], len==%d\n", puIn, iLen);
    const char *opNote ="---hhh1123我来了---";
    otl_long_string sInterfaceData(textStr, iLen, iLen); // define long string variable
//    otl_lob_stream lobInterfacerData;
    try
    {
        otlOrderLine.open(1,
                "INSERT INTO or_OrdLineIntr_info"
                "("
                "  ORDER_LINE_ID, ORDER_LINE_CHANGE_ID ,"
                "  ORDER_ID, CREATE_DATE, CHANGE_DATE,"
                "  OP_NOTE, INTERFACE_DATA"
                ")"
                "VALUES"
                "("
                "  :ORDER_LINE_ID<char[20+1]>, :ORDER_LINE_CHANGE_ID<char[30+1]>, "
                "  :ORDER_ID<char[20+1]>, date_format(:CREATE_DATE<char[15]>, '%Y%m%d%H%i%s'),"
                "  date_format(sysdate(), '%Y%m%d%H%i%s'), :OP_NOTE<char[1024+1]>, :INTERFACE_DATA<varchar_long>)"
                , *otlDB);
        otlOrderLine<<"L18xxxxxxx";
        otlOrderLine<<"LC18xxxxxx";
        otlOrderLine<<"O18xxxxxx";
        otlOrderLine<<"20140803123028";
        otlOrderLine<<opNote;
        printf("------000\n");
//        int ii=0;
//        for(;ii<=strlen(textStr);ii++)
//            sInterfaceData[ii]=textStr[ii];
        otlOrderLine<<sInterfaceData;// Initialize otl_lob_stream
        printf("------111\n");

//        lobInterfacerData.set_len(iLen);
//        printf("------222\n");
//        lobInterfacerData<<sInterfaceData;
//        printf("------333\n");
//        lobInterfacerData.close();

        otlOrderLine.flush();
        otlOrderLine.close();

        otlexcp.open(1,
                "INSERT INTO or_ordlineexcp_info"
                "("
                "  ORDER_LINE_EXCP_ID, excp_type, ORDER_LINE_ID,"
                "  EXCP_REASON, err_code, err_msg,"
                "  HANDLE_RESULT, handle_login, TRIGGER_TIME, HANDLE_TIME"
                ")"
                "VALUES"
                "("
                "  :ORDER_LINE_EXCP_ID<char[20+1]>, :excp_type<int>, "
                "  :ORDER_line_ID<char[20+1]>, :EXCP_REASON<char[255]>,"
                "  :ERR_CODE<char[10+1]>, :ERR_MSG<char[1024+1]>, :HANDLE_RESULT<char[255]>,"
                "  :HANDLE_LOGIN<char[20+1]>, sysdate(), sysdate())" , *otlDB);
        otlexcp<<"E18xxxxxxx";
        otlexcp<<10;
        otlexcp<<"L18xxxxxx";
        otlexcp<<"我错啦啦...";
        otlexcp<<"123999";
        otlexcp<<opNote;
        otlexcp<<opNote;
        otlexcp<<"admin";

        otlexcp.flush();
        otlexcp.close();
    }
    catch(otl_exception& p)
    {
        cerr <<"-----err_code=="<<p.code<<endl;
        cerr <<"------err_msg=="<< p.msg << endl; // print out error message
        cerr <<"------stm_text=="<< p.stm_text << endl; // print out SQL that caused the error
        cerr <<"------sqlstate=="<< p.sqlstate << endl; // print out SQLSTATE message
        cerr <<"------var_info=="<< p.var_info << endl; // print out the variable that caused the error
        return -1;
    }
    catch(...)
    {
        cout<<"------unknown exception-----"<<endl;
        return -2;
    }
    printf("-----out InsOtlMysql------\n");

    return 0;
}

