/*
 * =====================================================================================
 *
 *       Filename:  learn_cpp_main.cpp
 *
 *    Description:  main()
 *
 *        Version:  1.0
 *        Created:  2014/7/9 11:20:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#include "framework.h"

int main(int argc,char *argv[])
{
    cout<<"...in learncpp..."<<endl;

    char lib_path[256];
    char func_name[50];
    char dll[30+1];
    memset(lib_path, '\0', sizeof(lib_path));
    memset(func_name, '\0', sizeof(func_name));
    memset(dll, '\0', sizeof(dll));
    strcpy(func_name, argv[1]);
    cout<<"------func_name=="<<func_name<<endl;

    //2: use otl to connect MYSQL database, to get func's library
    otl_connect mydb;
    otl_connect::otl_initialize(); //initialize OCI environment
    try
    {
        mydb.rlogon("smart_pipe/smart_pipe@learn_mysql_dsn");
        otl_cursor::direct_exec(mydb, "use smart_pipe");
        otl_cursor::direct_exec(mydb, "set autocommit=0");

        {
            printf("-----in InsOtlMysql------\n");
            otl_nocommit_stream otlOrderLine;
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

                uAutoPtr ucIOrdLineExcpIn(uInit(8));
                utAddStr(ucIOrdLineExcpIn, "ORDER_LINE_EXCP_ID", "E18xxxxxxx");
                utAddInt(ucIOrdLineExcpIn, "EXCP_TYPE", 10);
                utAddStr(ucIOrdLineExcpIn, "ORDER_LINE_ID", "L18xxxxxx");
                utAddStr(ucIOrdLineExcpIn, "EXCP_REASON", "我错啦啦...");
                utAddStr(ucIOrdLineExcpIn, "TRIGGER_TIME", "2014081817280829");
                utAddStr(ucIOrdLineExcpIn, "ERR_CODE", "12399");
                utAddStr(ucIOrdLineExcpIn, "ERR_MSG", opNote);
                utAddStr(ucIOrdLineExcpIn, "HANDLE_RESULT", " ");
                utAddStr(ucIOrdLineExcpIn, "HANDLE_TIME", "20500101010101");
                utAddStr(ucIOrdLineExcpIn, "HANDLE_LOGIN", " ");
                uAutoPtr(cIOrdLineExcp(ucIOrdLineExcpIn, ptCtrlInfo));
            }
            catch(otl_exception& p)
            {
                cerr <<"-----err_code=="<<p.code<<endl;
                cerr <<"------err_msg=="<< p.msg << endl; // print out error message
                cerr <<"------stm_text=="<< p.stm_text << endl; // print out SQL that caused the error
                cerr <<"------sqlstate=="<< p.sqlstate << endl; // print out SQLSTATE message
                cerr <<"------var_info=="<< p.var_info << endl; // print out the variable that caused the error
            }
            catch(...)
            {
                cout<<"------unknown exception-----"<<endl;
            }
            printf("-----out InsOtlMysql------\n");

            return 0;
        }
    }
    catch(otl_exception &p)
    {
        cerr <<"------msg=="<< p.msg << endl; // print out error message
        cerr <<"------stm_text=="<< p.stm_text << endl; // print out SQL that caused the error
        cerr <<"------sqlstate=="<< p.sqlstate << endl; // print out SQLSTATE message
        cerr <<"------var_info=="<< p.var_info << endl; // print out the variable that caused the error
        exit(1);
    }

    mydb.logoff();

    cout<<"...out learncpp..."<<endl;

    return 0;
}

