/*
 * =====================================================================================
 *
 *       Filename:  learn_otl_pub.h
 *
 *    Description:  public head file for otl
 *
 *        Version:  1.0
 *        Created:  2014/7/9 11:51:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha 
 *   Organization:  si-tech
 *
 * =====================================================================================
 */

#ifndef LEARN_OTL_PUB_H_
#define LEARN_OTL_PUB_H_

//#define OTL_ODBC_MYSQL
#define OTL_ODBC //Compile OTL 4.0/ODBC
//#define OTL_UNICODE //Enable Unicode OTL
#define OTL_ODBC_SELECT_STM_EXECUTE_BEFORE_DESCRIBE //required with MyODBC 5.1 and higher
#define OTL_ODBC_UNIX
//#define OTL_INFORMIX_CLI
#include <sql.h>
#include "otlv4.h" //include the OTL 4.0 header file

#endif //LEARN_OTL_PUB_H_

