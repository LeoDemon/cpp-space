/*
 * =====================================================================================
 *
 *       Filename:  infxsql.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年07月22日 17时35分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: LeoDemon
 *   Organization:  
 *
 * =====================================================================================
 */
/*****************************************************************
** INFXSQL.H - This is the the include file for Informix-CLI
**             applications with  SQL.H and SQLEXT.H
**
*********************************************************************/
#ifndef __INFXSQL
#define __INFXSQL
/*****************************************************************
** SQL.H - This is the the main include for ODBC Core functions.
**
** preconditions:
**      #include "windows.h"
**
** (C) Copyright 1990 - 1996 By Microsoft Corp.
**
**      Updated 5/12/93 for 2.00 specification
**      Updated 5/23/94 for 2.01 specification
**      Updated 11/10/94 for 2.10 specification
**      Updated 04/10/95 for 2.50 specification
**      Updated 6/6/95  for 3.00 specification
*********************************************************************/
/*
* ODBCVER  ODBC version number (0x0300).   To exclude
*          definitions introduced in version 3.0 (or above)
*          #define ODBCVER 0x0250 before #including <sql.h>
*/
#ifndef ODBCVER
#define ODBCVER 0x0300
#endif
/* environment specific definitions */
#ifndef EXPORT
#define EXPORT   
#endif
#ifdef WIN32
#define SQL_API  __stdcall
#else
#define SQL_API
#endif
#ifndef RC_INVOKED
/* API declaration data types */
typedef unsigned char   SQLCHAR;
#if (ODBCVER >= 0x0300)
typedef signed char     SQLSCHAR;
typedef unsigned char   SQLDATE;
typedef unsigned char   SQLDECIMAL;
typedef double          SQLDOUBLE;
typedef double          SQLFLOAT;
#endif
/* for 32/64-bit compliance SQLINTEGER is defined as int
 * and SQLUINTEGER is defined as unsigned int 
 */
typedef int            SQLINTEGER;
typedef unsigned int   SQLUINTEGER;
#if (ODBCVER >= 0x0300)
typedef unsigned char   SQLNUMERIC;
#endif
typedef void *          SQLPOINTER;
#if (ODBCVER >= 0x0300)
typedef float           SQLREAL;
#endif
typedef short           SQLSMALLINT;
typedef unsigned short  SQLUSMALLINT;
#if (ODBCVER >= 0x0300)
typedef unsigned char   SQLTIME;
typedef unsigned char   SQLTIMESTAMP;
typedef unsigned char   SQLVARCHAR;
#endif
/* Windows/NT specific DataTypes and defines */
#ifndef WIN32
#define CALLBACK
#define EXPORT
#define FAR
#define PASCAL
#define _cdecl
#define TRUE             1
#define FALSE            0
#define VOID             void
typedef int              HWND;
typedef int              BOOL;
typedef unsigned int     UINT;
typedef VOID            *HANDLE;
typedef char            *LPSTR;
typedef const char      *LPCSTR;
typedef char            *LPWSTR;
typedef char             WCHAR;
typedef SQLUINTEGER      DWORD;
typedef unsigned short   WORD;
typedef unsigned char    BYTE;
typedef BYTE            *LPBYTE;
typedef SQLINTEGER       LONG;
typedef VOID            *LPVOID;   
typedef VOID            *PVOID;
typedef VOID            *HMODULE;
typedef int              GLOBALHANDLE;
typedef int            (*FARPROC)();
typedef VOID            *HINSTANCE;
typedef unsigned int     WPARAM;
typedef SQLUINTEGER      LPARAM;
typedef VOID            *HKEY;
typedef VOID            *PHKEY;
typedef char             CHAR;
typedef BOOL            *LPBOOL;
typedef DWORD           *LPDWORD;
typedef const char      *LPCWSTR;
typedef char             TCHAR;
typedef char             VCHAR;
typedef TCHAR           *LPTSTR;
typedef const TCHAR     *LPCTSTR;
#endif /*!WIN32 */
/* function return type */
typedef SQLSMALLINT     SQLRETURN;
/* generic data structures */
#if (ODBCVER >= 0x0300)
typedef void* SQLHANDLE;
typedef SQLHANDLE               SQLHENV;
typedef SQLHANDLE               SQLHDBC;
typedef SQLHANDLE               SQLHSTMT;
typedef SQLHANDLE               SQLHDESC;
#else
typedef void* SQLHENV;
typedef void* SQLHDBC;
typedef void* SQLHSTMT;
#endif /* ODBCVER >= 0x0300 */
/* SQL portable types for C */
typedef unsigned char           UCHAR;
typedef signed char             SCHAR;
typedef SQLINTEGER              SDWORD;
typedef short int               SWORD;
typedef SQLUINTEGER             UDWORD;
typedef unsigned short int      UWORD;
typedef signed long             SLONG;
typedef signed short            SSHORT;
typedef unsigned long           ULONG;
typedef unsigned short          USHORT;
typedef double                  SDOUBLE;
typedef double             LDOUBLE; 
typedef float                   SFLOAT;
#ifdef PTR
#undef PTR
#endif
typedef void*               PTR;
typedef void*               HENV;
typedef void*               HDBC;
typedef void*               HSTMT;
typedef signed short            RETCODE;
#if defined(WIN32) || defined(OS2)
typedef HWND                    SQLHWND;
#elif defined (UNIX)
typedef Widget                  SQLHWND;
#else
/* placehold for future O/S GUI window handle definition */
typedef SQLPOINTER              SQLHWND;
#endif
#ifndef __SQLDATE
#define __SQLDATE
/* transfer types for DATE, TIME, TIMESTAMP */
typedef struct tagDATE_STRUCT
{
        SQLSMALLINT    year;
        SQLUSMALLINT   month;
        SQLUSMALLINT   day;
} DATE_STRUCT;
#if (ODBCVER >= 0x0300)
typedef DATE_STRUCT SQL_DATE_STRUCT;
#endif  /* ODBCVER >= 0x0300 */
typedef struct tagTIME_STRUCT
{
        SQLUSMALLINT   hour;
        SQLUSMALLINT   minute;
        SQLUSMALLINT   second;
} TIME_STRUCT;
#if (ODBCVER >= 0x0300)
typedef TIME_STRUCT SQL_TIME_STRUCT;
#endif /* ODBCVER >= 0x0300 */
typedef struct tagTIMESTAMP_STRUCT
{
        SQLSMALLINT    year;
        SQLUSMALLINT   month;
        SQLUSMALLINT   day;
        SQLUSMALLINT   hour;
        SQLUSMALLINT   minute;
        SQLUSMALLINT   second;
        SQLUINTEGER    fraction;
} TIMESTAMP_STRUCT;
#if (ODBCVER >= 0x0300)
typedef TIMESTAMP_STRUCT SQL_TIMESTAMP_STRUCT;
#endif  /* ODBCVER >= 0x0300 */
/*
 * enumerations for DATETIME_INTERVAL_SUBCODE values for interval data types
 * these values are from SQL-92
 */
#if (ODBCVER >= 0x0300)
typedef enum 
{
SQL_IS_YEAR = 1,
SQL_IS_MONTH = 2,
SQL_IS_DAY = 3,
SQL_IS_HOUR = 4,
SQL_IS_MINUTE = 5,
SQL_IS_SECOND = 6,
SQL_IS_YEAR_TO_MONTH = 7,
SQL_IS_DAY_TO_HOUR = 8,
SQL_IS_DAY_TO_MINUTE = 9,
SQL_IS_DAY_TO_SECOND = 10,
SQL_IS_HOUR_TO_MINUTE = 11,
SQL_IS_HOUR_TO_SECOND = 12,
SQL_IS_MINUTE_TO_SECOND = 13
} SQLINTERVAL;
#endif  /* ODBCVER >= 0x0300 */
#if (ODBCVER >= 0x0300)
typedef struct tagSQL_YEAR_MONTH
{
SQLUINTEGER year;
SQLUINTEGER month;
} SQL_YEAR_MONTH_STRUCT;
typedef struct tagSQL_DAY_SECOND
{
SQLUINTEGER day;
SQLUINTEGER hour;
SQLUINTEGER minute;
SQLUINTEGER second;
SQLUINTEGER fraction;
} SQL_DAY_SECOND_STRUCT;
typedef struct tagSQL_INTERVAL_STRUCT
{
SQLINTERVAL interval_type;
SQLSMALLINT interval_sign;
union {
SQL_YEAR_MONTH_STRUCT year_month;
SQL_DAY_SECOND_STRUCT day_second;
} intval;
} SQL_INTERVAL_STRUCT;
#endif  /* ODBCVER >= 0x0300 */
#endif /* __SQLDATE */
/* the ODBC C types for SQL_C_SBIGINT and SQL_C_UBIGINT */
#if (ODBCVER >= 0x0300)
#if (_MSC_VER >= 900)
#define ODBCINT64 __int64
#endif  
/* define ODBCINT64 for UNIX */
#ifndef ODBCINT64
#define ODBCINT64      long long
#endif /* ODBCINT64 */
/* If using other compilers, define ODBCINT64 to the 
approriate 64 bit integer type */
#ifdef ODBCINT64
typedef ODBCINT64 SQLBIGINT;
typedef unsigned ODBCINT64 SQLUBIGINT;
#endif
#endif  /* ODBCVER >= 0x0300 */
/* internal representation of numeric data type */
#if (ODBCVER >= 0x0300)
#define SQL_MAX_NUMERIC_LEN 16
typedef struct tagSQL_NUMERIC_STRUCT
{
SQLCHAR precision;
SQLSCHAR scale;
SQLCHAR sign; /* 1 if positive, 0 if negative */
SQLCHAR val[SQL_MAX_NUMERIC_LEN];
} SQL_NUMERIC_STRUCT;
#endif  /* ODBCVER >= 0x0300 */
typedef SQLUINTEGER     BOOKMARK;
typedef wchar_t SQLWCHAR;
#ifdef UNICODE
typedef SQLWCHAR        SQLTCHAR;
#else
typedef SQLCHAR         SQLTCHAR;
#endif  /* UNICODE */
#endif     /* RC_INVOKED */
/********************************************/
/* removes warning in 2.x applications */
#define HSTMT                  SQLHSTMT
#define HDBC                   SQLHDBC
#define HENV                   SQLHENV
#define PTR                    void*
#ifdef __cplusplus
extern "C" {  /* Assume C declarations for C++   */
#endif  /* __cplusplus */
/* special length/indicator values */
#define SQL_NULL_DATA             (-1)
#define SQL_DATA_AT_EXEC          (-2)
/* return values from functions */
#define SQL_SUCCESS                0
#define SQL_SUCCESS_WITH_INFO      1
#if (ODBCVER >= 0x0300)
#define SQL_NO_DATA              100
#endif
#define SQL_ERROR                 (-1)
#define SQL_INVALID_HANDLE        (-2)
#define SQL_STILL_EXECUTING        2
#define SQL_NEED_DATA             99
/* test for SQL_SUCCESS or SQL_SUCCESS_WITH_INFO */
#define SQL_SUCCEEDED(rc) (((rc)&(~1))==0)
/* flags for null-terminated string */
#define SQL_NTS                   (-3)
#define SQL_NTSL                  (-3L)
/* maximum message length */
#define SQL_MAX_MESSAGE_LENGTH   512
/* date/time length constants */
#if (ODBCVER >= 0x0300)
#define SQL_DATE_LEN           10
#define SQL_TIME_LEN            8  /* add P+1 if precision is nonzero */
#define SQL_TIMESTAMP_LEN      19  /* add P+1 if precision is nonzero */
#endif
/* handle type identifiers */
#if (ODBCVER >= 0x0300)
#define SQL_HANDLE_ENV             1
#define SQL_HANDLE_DBC             2
#define SQL_HANDLE_STMT            3
#define SQL_HANDLE_DESC            4
#endif
/* environment attribute */
#if (ODBCVER >= 0x0300)
#define SQL_ATTR_OUTPUT_NTS    10001
#endif
/* connection attributes */
#if (ODBCVER >= 0x0300)
#define SQL_ATTR_AUTO_IPD      10001
#define SQL_ATTR_METADATA_ID   10014
#endif  /* ODBCVER >= 0x0300 */
/* statement attributes */
#if (ODBCVER >= 0x0300)
#define SQL_ATTR_APP_ROW_DESC       10010
#define SQL_ATTR_APP_PARAM_DESC     10011
#define SQL_ATTR_IMP_ROW_DESC       10012
#define SQL_ATTR_IMP_PARAM_DESC     10013
#define SQL_ATTR_CURSOR_SCROLLABLE  (-1)
#define SQL_ATTR_CURSOR_SENSITIVITY (-2)
#endif
/* SQL_ATTR_CURSOR_SCROLLABLE values */
#if (ODBCVER >= 0x0300)
#define SQL_NONSCROLLABLE 0
#define SQL_SCROLLABLE 1
#endif  /* ODBCVER >= 0x0300 */
/* identifiers of fields in the SQL descriptor */
#if (ODBCVER >= 0x0300)
#define SQL_DESC_COUNT                  1001
#define SQL_DESC_TYPE                   1002
#define SQL_DESC_LENGTH                 1003
#define SQL_DESC_OCTET_LENGTH_PTR       1004
#define SQL_DESC_PRECISION              1005
#define SQL_DESC_SCALE                  1006
#define SQL_DESC_DATETIME_INTERVAL_CODE 1007
#define SQL_DESC_NULLABLE               1008
#define SQL_DESC_INDICATOR_PTR          1009
#define SQL_DESC_DATA_PTR               1010
#define SQL_DESC_NAME                   1011
#define SQL_DESC_UNNAMED                1012
#define SQL_DESC_OCTET_LENGTH           1013
#define SQL_DESC_ALLOC_TYPE             1099
#endif
/* identifiers of fields in the diagnostics area */
#if (ODBCVER >= 0x0300)
#define SQL_DIAG_RETURNCODE        1
#define SQL_DIAG_NUMBER            2
#define SQL_DIAG_ROW_COUNT         3
#define SQL_DIAG_SQLSTATE          4
#define SQL_DIAG_NATIVE            5
#define SQL_DIAG_MESSAGE_TEXT      6
#define SQL_DIAG_DYNAMIC_FUNCTION  7
#define SQL_DIAG_CLASS_ORIGIN      8
#define SQL_DIAG_SUBCLASS_ORIGIN   9
#define SQL_DIAG_CONNECTION_NAME  10
#define SQL_DIAG_SERVER_NAME      11
#define SQL_DIAG_DYNAMIC_FUNCTION_CODE 12
#endif
/* dynamic function codes */
#if (ODBCVER >= 0x0300)
#define SQL_DIAG_ALTER_TABLE            4
#define SQL_DIAG_CREATE_INDEX          (-1)
#define SQL_DIAG_CREATE_TABLE          77
#define SQL_DIAG_CREATE_VIEW           84
#define SQL_DIAG_DELETE_WHERE          19
#define SQL_DIAG_DROP_INDEX            (-2)
#define SQL_DIAG_DROP_TABLE            32
#define SQL_DIAG_DROP_VIEW             36
#define SQL_DIAG_DYNAMIC_DELETE_CURSOR 38
#define SQL_DIAG_DYNAMIC_UPDATE_CURSOR 81
#define SQL_DIAG_GRANT                 48
#define SQL_DIAG_INSERT                50
#define SQL_DIAG_REVOKE                59
#define SQL_DIAG_SELECT_CURSOR         85
#define SQL_DIAG_UNKNOWN_STATEMENT      0
#define SQL_DIAG_UPDATE_WHERE          82
#endif  /* ODBCVER >= 0x0300 */
/* SQL data type codes */
#define SQL_UNKNOWN_TYPE 0
#define SQL_CHAR            1
#define SQL_NUMERIC         2
#define SQL_DECIMAL         3
#define SQL_INTEGER         4
#define SQL_SMALLINT        5
#define SQL_FLOAT           6
#define SQL_REAL            7
#define SQL_DOUBLE          8
#if (ODBCVER >= 0x0300)
#define SQL_DATETIME        9
#endif
#define SQL_VARCHAR        12
/* One-parameter shortcuts for date/time data types */
#if (ODBCVER >= 0x0300)
#define SQL_TYPE_DATE      91
#define SQL_TYPE_TIME      92
#define SQL_TYPE_TIMESTAMP 93
#endif
/* Statement attribute values for cursor sensitivity */
#if (ODBCVER >= 0x0300)
#define SQL_UNSPECIFIED     0
#define SQL_INSENSITIVE     1
#define SQL_SENSITIVE       2
#endif
/* GetTypeInfo() request for all data types */
#define SQL_ALL_TYPES       0
/* Default conversion code for SQLBindCol(), SQLBindParam() and SQLGetData() */
#if (ODBCVER >= 0x0300)
#define SQL_DEFAULT        99
#endif
/* SQLGetData() code indicating that the application row descriptor
 * specifies the data type
 */
#if (ODBCVER >= 0x0300)
#define SQL_ARD_TYPE      (-99)
#endif
/* SQL date/time type subcodes */
#if (ODBCVER >= 0x0300)
#define SQL_CODE_DATE       1
#define SQL_CODE_TIME       2
#define SQL_CODE_TIMESTAMP  3
#endif
/* CLI option values */
#if (ODBCVER >= 0x0300)
#define SQL_FALSE           0
#define SQL_TRUE            1
#endif
/* values of NULLABLE field in descriptor */
#define SQL_NO_NULLS        0
#define SQL_NULLABLE        1
/* Value returned by SQLGetTypeInfo() to denote that it is
 * not known whether or not a data type supports null values.
 */
#define SQL_NULLABLE_UNKNOWN  2
/* Values returned by SQLGetTypeInfo() to show WHERE clause
 * supported
 */
#if (ODBCVER >= 0x0300)
#define SQL_PRED_NONE     0
#define SQL_PRED_CHAR     1
#define SQL_PRED_BASIC    2
#endif
/* values of UNNAMED field in descriptor */
#if (ODBCVER >= 0x0300)
#define SQL_NAMED           0
#define SQL_UNNAMED         1
#endif
/* values of ALLOC_TYPE field in descriptor */
#if (ODBCVER >= 0x0300)
#define SQL_DESC_ALLOC_AUTO 1
#define SQL_DESC_ALLOC_USER 2
#endif
/* FreeStmt() options */
#define SQL_CLOSE           0
#define SQL_DROP            1
#define SQL_UNBIND          2
#define SQL_RESET_PARAMS    3
/* Codes used for FetchOrientation in SQLFetchScroll(), 
   and in SQLDataSources() 
*/
#define SQL_FETCH_NEXT      1
#define SQL_FETCH_FIRST     2
/* Other codes used for FetchOrientation in SQLFetchScroll() */
#define SQL_FETCH_LAST      3
#define SQL_FETCH_PRIOR     4
#define SQL_FETCH_ABSOLUTE  5
#define SQL_FETCH_RELATIVE  6
/* SQLEndTran() options */
#define SQL_COMMIT          0
#define SQL_ROLLBACK        1
/* null handles returned by SQLAllocHandle() */
#define SQL_NULL_HENV       0
#define SQL_NULL_HDBC       0
#define SQL_NULL_HSTMT      0
#if (ODBCVER >= 0x0300)
#define SQL_NULL_HDESC      0
#endif
/* null handle used in place of parent handle when allocating HENV */
#if (ODBCVER >= 0x0300)
#define SQL_NULL_HANDLE     0L
#endif
/* Values that may appear in the result set of SQLSpecialColumns() */
#define SQL_SCOPE_CURROW    0
#define SQL_SCOPE_TRANSACTION 1
#define SQL_SCOPE_SESSION   2
#define SQL_PC_UNKNOWN      0
#if (ODBCVER >= 0x0300)
#define SQL_PC_NON_PSEUDO   1
#endif
#define SQL_PC_PSEUDO       2
/* Reserved value for the IdentifierType argument of SQLSpecialColumns() */
#if (ODBCVER >= 0x0300)
#define SQL_ROW_IDENTIFIER  1
#endif
/* Reserved values for UNIQUE argument of SQLStatistics() */
#define SQL_INDEX_UNIQUE    0
#define SQL_INDEX_ALL       1
/* Values that may appear in the result set of SQLStatistics() */
#define SQL_INDEX_CLUSTERED 1
#define SQL_INDEX_HASHED    2
#define SQL_INDEX_OTHER     3
/* SQLGetFunctions() values to identify ODBC APIs */
#define SQL_API_SQLALLOCCONNECT         1
#define SQL_API_SQLALLOCENV             2
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLALLOCHANDLE       1001
#endif
#define SQL_API_SQLALLOCSTMT            3
#define SQL_API_SQLBINDCOL              4
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLBINDPARAM         1002
#endif
#define SQL_API_SQLCANCEL               5
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLCLOSECURSOR       1003
#define SQL_API_SQLCOLATTRIBUTE         6
#endif
#define SQL_API_SQLCOLUMNS             40
#define SQL_API_SQLCONNECT              7
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLCOPYDESC          1004
#endif
#define SQL_API_SQLDATASOURCES         57
#define SQL_API_SQLDESCRIBECOL          8
#define SQL_API_SQLDISCONNECT           9
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLENDTRAN           1005
#endif
#define SQL_API_SQLERROR               10
#define SQL_API_SQLEXECDIRECT          11
#define SQL_API_SQLEXECUTE             12
#define SQL_API_SQLFETCH               13
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLFETCHSCROLL       1021
#endif
#define SQL_API_SQLFREECONNECT         14
#define SQL_API_SQLFREEENV             15
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLFREEHANDLE        1006
#endif
#define SQL_API_SQLFREESTMT            16
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLGETCONNECTATTR    1007
#endif
#define SQL_API_SQLGETCONNECTOPTION    42
#define SQL_API_SQLGETCURSORNAME       17
#define SQL_API_SQLGETDATA             43
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLGETDESCFIELD      1008
#define SQL_API_SQLGETDESCREC        1009
#define SQL_API_SQLGETDIAGFIELD      1010
#define SQL_API_SQLGETDIAGREC        1011
#define SQL_API_SQLGETENVATTR        1012
#endif
#define SQL_API_SQLGETFUNCTIONS        44
#define SQL_API_SQLGETINFO             45
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLGETSTMTATTR       1014
#endif
#define SQL_API_SQLGETSTMTOPTION       46
#define SQL_API_SQLGETTYPEINFO         47
#define SQL_API_SQLNUMRESULTCOLS       18
#define SQL_API_SQLPARAMDATA           48
#define SQL_API_SQLPREPARE             19
#define SQL_API_SQLPUTDATA             49
#define SQL_API_SQLROWCOUNT            20
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLSETCONNECTATTR    1016
#endif
#define SQL_API_SQLSETCONNECTOPTION    50
#define SQL_API_SQLSETCURSORNAME       21
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLSETDESCFIELD      1017
#define SQL_API_SQLSETDESCREC        1018
#define SQL_API_SQLSETENVATTR        1019
#endif
#define SQL_API_SQLSETPARAM            22
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLSETSTMTATTR       1020
#endif
#define SQL_API_SQLSETSTMTOPTION       51
#define SQL_API_SQLSPECIALCOLUMNS      52
#define SQL_API_SQLSTATISTICS          53
#define SQL_API_SQLTABLES              54
#define SQL_API_SQLTRANSACT            23
/* Information requested by SQLGetInfo() */
#if (ODBCVER >= 0x0300)
#define SQL_MAX_DRIVER_CONNECTIONS           0
#define SQL_MAXIMUM_DRIVER_CONNECTIONS SQL_MAX_DRIVER_CONNECTIONS
#define SQL_MAX_CONCURRENT_ACTIVITIES        1
#define SQL_MAXIMUM_CONCURRENT_ACTIVITIES SQL_MAX_CONCURRENT_ACTIVITIES
#endif
#define SQL_DATA_SOURCE_NAME                 2
#define SQL_FETCH_DIRECTION                  8
#define SQL_SERVER_NAME                     13
#define SQL_SEARCH_PATTERN_ESCAPE           14
#define SQL_DBMS_NAME                       17
#define SQL_DBMS_VER                        18
#define SQL_ACCESSIBLE_TABLES               19
#define SQL_ACCESSIBLE_PROCEDURES         20
#define SQL_CURSOR_COMMIT_BEHAVIOR          23
#define SQL_DATA_SOURCE_READ_ONLY           25
#define SQL_DEFAULT_TXN_ISOLATION           26
#define SQL_IDENTIFIER_CASE                 28
#define SQL_IDENTIFIER_QUOTE_CHAR           29
#define SQL_MAX_COLUMN_NAME_LEN             30
#define SQL_MAXIMUM_COLUMN_NAME_LENGTH SQL_MAX_COLUMN_NAME_LEN
#define SQL_MAX_CURSOR_NAME_LEN             31
#define SQL_MAXIMUM_CURSOR_NAME_LENGTH SQL_MAX_CURSOR_NAME_LEN
#define SQL_MAX_SCHEMA_NAME_LEN             32
#define SQL_MAXIMUM_SCHEMA_NAME_LENGTH SQL_MAX_SCHEMA_NAME_LEN
#define SQL_MAX_CATALOG_NAME_LEN            34
#define SQL_MAXIMUM_CATALOG_NAME_LENGTH SQL_MAX_CATALOG_NAME_LEN
#define SQL_MAX_TABLE_NAME_LEN              35
#define SQL_SCROLL_CONCURRENCY              43
#define SQL_TXN_CAPABLE                     46
#define SQL_TRANSACTION_CAPABLE SQL_TXN_CAPABLE
#define SQL_USER_NAME                       47
#define SQL_TXN_ISOLATION_OPTION            72
#define SQL_TRANSACTION_ISOLATION_OPTION SQL_TXN_ISOLATION_OPTION
#define SQL_INTEGRITY                       73
#define SQL_GETDATA_EXTENSIONS              81
#define SQL_NULL_COLLATION                  85
#define SQL_ALTER_TABLE                     86
#define SQL_ORDER_BY_COLUMNS_IN_SELECT      90
#define SQL_SPECIAL_CHARACTERS              94
#define SQL_MAX_COLUMNS_IN_GROUP_BY         97
#define SQL_MAXIMUM_COLUMNS_IN_GROUP_BY SQL_MAX_COLUMNS_IN_GROUP_BY
#define SQL_MAX_COLUMNS_IN_INDEX            98
#define SQL_MAXIMUM_COLUMNS_IN_INDEX SQL_MAX_COLUMNS_IN_INDEX
#define SQL_MAX_COLUMNS_IN_ORDER_BY         99
#define SQL_MAXIMUM_COLUMNS_IN_ORDER_BY SQL_MAX_COLUMNS_IN_ORDER_BY
#define SQL_MAX_COLUMNS_IN_SELECT          100
#define SQL_MAXIMUM_COLUMNS_IN_SELECT    SQL_MAX_COLUMNS_IN_SELECT
#define SQL_MAX_COLUMNS_IN_TABLE           101
#define SQL_MAX_INDEX_SIZE                 102
#define SQL_MAXIMUM_INDEX_SIZE    SQL_MAX_INDEX_SIZE
#define SQL_MAX_ROW_SIZE                   104
#define SQL_MAXIMUM_ROW_SIZE    SQL_MAX_ROW_SIZE
#define SQL_MAX_STATEMENT_LEN              105
#define SQL_MAXIMUM_STATEMENT_LENGTH    SQL_MAX_STATEMENT_LEN
#define SQL_MAX_TABLES_IN_SELECT           106
#define SQL_MAXIMUM_TABLES_IN_SELECT    SQL_MAX_TABLES_IN_SELECT
#define SQL_MAX_USER_NAME_LEN              107
#define SQL_MAXIMUM_USER_NAME_LENGTH    SQL_MAX_USER_NAME_LEN
#if (ODBCVER >= 0x0300)
#define SQL_OJ_CAPABILITIES                115
#define SQL_OUTER_JOIN_CAPABILITIES    SQL_OJ_CAPABILITIES
#endif /* ODBCVER >= 0x0300 */
#if (ODBCVER >= 0x0300)
#define SQL_XOPEN_CLI_YEAR               10000
#define SQL_CURSOR_SENSITIVITY           10001
#define SQL_DESCRIBE_PARAMETER           10002
#define SQL_CATALOG_NAME                 10003
#define SQL_COLLATION_SEQ                10004
#define SQL_MAX_IDENTIFIER_LEN           10005
#define SQL_MAXIMUM_IDENTIFIER_LENGTH  SQL_MAX_IDENTIFIER_LEN
#endif /* ODBCVER >= 0x0300 */
/* SQL_ALTER_TABLE bitmasks */
#if (ODBCVER >= 0x0200)
#define SQL_AT_ADD_COLUMN                    0x00000001L
#define SQL_AT_DROP_COLUMN                   0x00000002L
#endif /* ODBCVER >= 0x0200 */
#if (ODBCVER >= 0x0300)
#define SQL_AT_ADD_CONSTRAINT                0x00000008L
/* The following bitmasks are ODBC extensions and defined in sqlext.h
*#define SQL_AT_COLUMN_SINGLE 0x00000020L
*#define SQL_AT_ADD_COLUMN_DEFAULT 0x00000040L
*#define SQL_AT_ADD_COLUMN_COLLATION 0x00000080L
*#define SQL_AT_SET_COLUMN_DEFAULT 0x00000100L
*#define SQL_AT_DROP_COLUMN_DEFAULT 0x00000200L
*#define SQL_AT_DROP_COLUMN_CASCADE 0x00000400L
*#define SQL_AT_DROP_COLUMN_RESTRICT 0x00000800L
*#define SQL_AT_ADD_TABLE_CONSTRAINT 0x00001000L
*#define SQL_AT_DROP_TABLE_CONSTRAINT_CASCADE 0x00002000L
*#define SQL_AT_DROP_TABLE_CONSTRAINT_RESTRICT 0x00004000L
*#define SQL_AT_CONSTRAINT_NAME_DEFINITION 0x00008000L
*#define SQL_AT_CONSTRAINT_INITIALLY_DEFERRED 0x00010000L
*#define SQL_AT_CONSTRAINT_INITIALLY_IMMEDIATE 0x00020000L
*#define SQL_AT_CONSTRAINT_DEFERRABLE 0x00040000L
*#define SQL_AT_CONSTRAINT_NON_DEFERRABLE 0x00080000L
*/
#endif  /* ODBCVER >= 0x0300 */
/* SQL_ASYNC_MODE values */
#if (ODBCVER >= 0x0300)
#define SQL_AM_NONE                         0
#define SQL_AM_CONNECTION                   1
#define SQL_AM_STATEMENT                    2
#endif
/* SQL_CURSOR_COMMIT_BEHAVIOR values */
#define SQL_CB_DELETE                       0
#define SQL_CB_CLOSE                        1
#define SQL_CB_PRESERVE                     2
/* SQL_FETCH_DIRECTION bitmasks */
#define SQL_FD_FETCH_NEXT                   0x00000001L
#define SQL_FD_FETCH_FIRST                  0x00000002L
#define SQL_FD_FETCH_LAST                   0x00000004L
#define SQL_FD_FETCH_PRIOR                  0x00000008L
#define SQL_FD_FETCH_ABSOLUTE               0x00000010L
#define SQL_FD_FETCH_RELATIVE               0x00000020L
/* SQL_GETDATA_EXTENSIONS bitmasks */
#define SQL_GD_ANY_COLUMN                   0x00000001L
#define SQL_GD_ANY_ORDER                    0x00000002L
/* SQL_IDENTIFIER_CASE values */
#define SQL_IC_UPPER                        1
#define SQL_IC_LOWER                        2
#define SQL_IC_SENSITIVE                    3
#define SQL_IC_MIXED                        4
/* SQL_OJ_CAPABILITIES bitmasks */
/* NB: this means 'outer join', not what  you may be thinking */
#if (ODBCVER >= 0x0201)
#define SQL_OJ_LEFT                         0x00000001L
#define SQL_OJ_RIGHT                        0x00000002L
#define SQL_OJ_FULL                         0x00000004L
#define SQL_OJ_NESTED                       0x00000008L
#define SQL_OJ_NOT_ORDERED                  0x00000010L
#define SQL_OJ_INNER                        0x00000020L
#define SQL_OJ_ALL_COMPARISON_OPS           0x00000040L
#endif
/* SQL_SCROLL_CONCURRENCY bitmasks */
#define SQL_SCCO_READ_ONLY                  0x00000001L
#define SQL_SCCO_LOCK                       0x00000002L
#define SQL_SCCO_OPT_ROWVER                 0x00000004L
#define SQL_SCCO_OPT_VALUES                 0x00000008L
/* SQL_TXN_CAPABLE values */
#define SQL_TC_NONE                         0
#define SQL_TC_DML                          1
#define SQL_TC_ALL                          2
#define SQL_TC_DDL_COMMIT                   3
#define SQL_TC_DDL_IGNORE                   4
/* SQL_TXN_ISOLATION_OPTION bitmasks */
#define SQL_TXN_READ_UNCOMMITTED            0x00000001L
#define SQL_TRANSACTION_READ_UNCOMMITTED SQL_TXN_READ_UNCOMMITTED
#define SQL_TXN_READ_COMMITTED              0x00000002L
#define SQL_TRANSACTION_READ_COMMITTED SQL_TXN_READ_COMMITTED
#define SQL_TXN_REPEATABLE_READ             0x00000004L
#define SQL_TRANSACTION_REPEATABLE_READ SQL_TXN_REPEATABLE_READ
#define SQL_TXN_SERIALIZABLE                0x00000008L
#define SQL_TRANSACTION_SERIALIZABLE SQL_TXN_SERIALIZABLE
/* SQL_NULL_COLLATION values */
#define SQL_NC_HIGH                         0
#define SQL_NC_LOW                          1
#ifndef RC_INVOKED
SQLRETURN  SQL_API SQLAllocConnect(SQLHENV EnvironmentHandle,
           SQLHDBC *ConnectionHandle);
SQLRETURN  SQL_API SQLAllocEnv(SQLHENV *EnvironmentHandle);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLAllocHandle(SQLSMALLINT HandleType,
           SQLHANDLE InputHandle, SQLHANDLE *OutputHandle);
#endif
SQLRETURN  SQL_API SQLAllocStmt(SQLHDBC ConnectionHandle,
           SQLHSTMT *StatementHandle);
SQLRETURN  SQL_API SQLBindCol(SQLHSTMT StatementHandle, 
   SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, 
   SQLPOINTER TargetValue, SQLINTEGER BufferLength, 
       SQLINTEGER *StrLen_or_Ind);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLBindParam(SQLHSTMT StatementHandle,
           SQLUSMALLINT ParameterNumber, SQLSMALLINT ValueType,
           SQLSMALLINT ParameterType, SQLUINTEGER LengthPrecision,
           SQLSMALLINT ParameterScale, SQLPOINTER ParameterValue,
           SQLINTEGER *StrLen_or_Ind);
#endif
SQLRETURN  SQL_API SQLCancel(SQLHSTMT StatementHandle);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLCloseCursor(SQLHSTMT StatementHandle);
SQLRETURN  SQL_API SQLColAttribute (SQLHSTMT StatementHandle,
           SQLUSMALLINT ColumnNumber, SQLUSMALLINT FieldIdentifier,
           SQLPOINTER CharacterAttribute, SQLSMALLINT BufferLength,
           SQLSMALLINT *StringLength, SQLPOINTER NumericAttribute);
#endif
SQLRETURN  SQL_API SQLColumns(SQLHSTMT StatementHandle,
           SQLCHAR *CatalogName, SQLSMALLINT NameLength1,
           SQLCHAR *SchemaName, SQLSMALLINT NameLength2,
           SQLCHAR *TableName, SQLSMALLINT NameLength3,
           SQLCHAR *ColumnName, SQLSMALLINT NameLength4);
SQLRETURN  SQL_API SQLConnect(SQLHDBC ConnectionHandle,
           SQLCHAR *ServerName, SQLSMALLINT NameLength1,
           SQLCHAR *UserName, SQLSMALLINT NameLength2,
           SQLCHAR *Authentication, SQLSMALLINT NameLength3);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLCopyDesc(SQLHDESC SourceDescHandle,
           SQLHDESC TargetDescHandle);
#endif
SQLRETURN  SQL_API SQLDataSources(SQLHENV EnvironmentHandle,
           SQLUSMALLINT Direction, SQLCHAR *ServerName,
           SQLSMALLINT BufferLength1, SQLSMALLINT *NameLength1,
           SQLCHAR *Description, SQLSMALLINT BufferLength2,
           SQLSMALLINT *NameLength2);
SQLRETURN  SQL_API SQLDescribeCol(SQLHSTMT StatementHandle,
           SQLUSMALLINT ColumnNumber, SQLCHAR *ColumnName,
           SQLSMALLINT BufferLength, SQLSMALLINT *NameLength,
           SQLSMALLINT *DataType, SQLUINTEGER *ColumnSize,
           SQLSMALLINT *DecimalDigits, SQLSMALLINT *Nullable);
SQLRETURN  SQL_API SQLDisconnect(SQLHDBC ConnectionHandle);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLEndTran(SQLSMALLINT HandleType, SQLHANDLE Handle,
           SQLSMALLINT CompletionType);
#endif
SQLRETURN  SQL_API SQLError(SQLHENV EnvironmentHandle,
           SQLHDBC ConnectionHandle, SQLHSTMT StatementHandle,
           SQLCHAR *Sqlstate, SQLINTEGER *NativeError,
           SQLCHAR *MessageText, SQLSMALLINT BufferLength,
           SQLSMALLINT *TextLength);
SQLRETURN  SQL_API SQLExecDirect(SQLHSTMT StatementHandle,
           SQLCHAR *StatementText, SQLINTEGER TextLength);
SQLRETURN  SQL_API SQLExecute(SQLHSTMT StatementHandle);
SQLRETURN  SQL_API SQLFetch(SQLHSTMT StatementHandle);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLFetchScroll(SQLHSTMT StatementHandle,
           SQLSMALLINT FetchOrientation, SQLINTEGER FetchOffset);
#endif
SQLRETURN  SQL_API SQLFreeConnect(SQLHDBC ConnectionHandle);
SQLRETURN  SQL_API SQLFreeEnv(SQLHENV EnvironmentHandle);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLFreeHandle(SQLSMALLINT HandleType, SQLHANDLE Handle);
#endif
SQLRETURN  SQL_API SQLFreeStmt(SQLHSTMT StatementHandle,
           SQLUSMALLINT Option);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLGetConnectAttr(SQLHDBC ConnectionHandle,
           SQLINTEGER Attribute, SQLPOINTER Value,
           SQLINTEGER BufferLength, SQLINTEGER *StringLength);
#endif
SQLRETURN  SQL_API SQLGetConnectOption(SQLHDBC ConnectionHandle,
           SQLUSMALLINT Option, SQLPOINTER Value);
SQLRETURN  SQL_API SQLGetCursorName(SQLHSTMT StatementHandle,
           SQLCHAR *CursorName, SQLSMALLINT BufferLength,
           SQLSMALLINT *NameLength);
SQLRETURN  SQL_API SQLGetData(SQLHSTMT StatementHandle,
           SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType,
           SQLPOINTER TargetValue, SQLINTEGER BufferLength,
           SQLINTEGER *StrLen_or_Ind);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLGetDescField(SQLHDESC DescriptorHandle,
           SQLSMALLINT RecNumber, SQLSMALLINT FieldIdentifier,
           SQLPOINTER Value, SQLINTEGER BufferLength,
           SQLINTEGER *StringLength);
SQLRETURN  SQL_API SQLGetDescRec(SQLHDESC DescriptorHandle,
           SQLSMALLINT RecNumber, SQLCHAR *Name,
           SQLSMALLINT BufferLength, SQLSMALLINT *StringLength,
           SQLSMALLINT *Type, SQLSMALLINT *SubType, 
           SQLINTEGER *Length, SQLSMALLINT *Precision, 
           SQLSMALLINT *Scale, SQLSMALLINT *Nullable);
SQLRETURN  SQL_API SQLGetDiagField(SQLSMALLINT HandleType, SQLHANDLE Handle,
           SQLSMALLINT RecNumber, SQLSMALLINT DiagIdentifier,
           SQLPOINTER DiagInfo, SQLSMALLINT BufferLength,
           SQLSMALLINT *StringLength);
SQLRETURN  SQL_API SQLGetDiagRec(SQLSMALLINT HandleType, SQLHANDLE Handle,
           SQLSMALLINT RecNumber, SQLCHAR *Sqlstate,
           SQLINTEGER *NativeError, SQLCHAR *MessageText,
           SQLSMALLINT BufferLength, SQLSMALLINT *TextLength);
SQLRETURN  SQL_API SQLGetEnvAttr(SQLHENV EnvironmentHandle,
           SQLINTEGER Attribute, SQLPOINTER Value,
           SQLINTEGER BufferLength, SQLINTEGER *StringLength);
#endif  /* ODBCVER >= 0x0300 */
SQLRETURN  SQL_API SQLGetFunctions(SQLHDBC ConnectionHandle,
           SQLUSMALLINT FunctionId, SQLUSMALLINT *Supported);
SQLRETURN  SQL_API SQLGetInfo(SQLHDBC ConnectionHandle,
           SQLUSMALLINT InfoType, SQLPOINTER InfoValue,
           SQLSMALLINT BufferLength, SQLSMALLINT *StringLength);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLGetStmtAttr(SQLHSTMT StatementHandle,
           SQLINTEGER Attribute, SQLPOINTER Value,
           SQLINTEGER BufferLength, SQLINTEGER *StringLength);
#endif  /* ODBCVER >= 0x0300 */
SQLRETURN  SQL_API SQLGetStmtOption(SQLHSTMT StatementHandle,
           SQLUSMALLINT Option, SQLPOINTER Value);
SQLRETURN  SQL_API SQLGetTypeInfo(SQLHSTMT StatementHandle,
           SQLSMALLINT DataType);
SQLRETURN  SQL_API SQLNumResultCols(SQLHSTMT StatementHandle,
           SQLSMALLINT *ColumnCount);
SQLRETURN  SQL_API SQLParamData(SQLHSTMT StatementHandle,
           SQLPOINTER *Value);
SQLRETURN  SQL_API SQLPrepare(SQLHSTMT StatementHandle,
           SQLCHAR *StatementText, SQLINTEGER TextLength);
SQLRETURN  SQL_API SQLPutData(SQLHSTMT StatementHandle,
           SQLPOINTER Data, SQLINTEGER StrLen_or_Ind);
SQLRETURN  SQL_API SQLRowCount(SQLHSTMT StatementHandle, 
   SQLINTEGER *RowCount);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLSetConnectAttr(SQLHDBC ConnectionHandle,
           SQLINTEGER Attribute, SQLPOINTER Value,
           SQLINTEGER StringLength);
#endif /* ODBCVER >= 0x0300 */
SQLRETURN  SQL_API SQLSetConnectOption(SQLHDBC ConnectionHandle,
           SQLUSMALLINT Option, ULONG Value);
SQLRETURN  SQL_API SQLSetCursorName(SQLHSTMT StatementHandle,
           SQLCHAR *CursorName, SQLSMALLINT NameLength);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLSetDescField(SQLHDESC DescriptorHandle,
           SQLSMALLINT RecNumber, SQLSMALLINT FieldIdentifier,
           SQLPOINTER Value, SQLINTEGER BufferLength);
SQLRETURN  SQL_API SQLSetDescRec(SQLHDESC DescriptorHandle,
           SQLSMALLINT RecNumber, SQLSMALLINT Type,
           SQLSMALLINT SubType, SQLINTEGER Length,
           SQLSMALLINT Precision, SQLSMALLINT Scale,
           SQLPOINTER Data, SQLINTEGER *StringLength,
           SQLINTEGER *Indicator);
SQLRETURN  SQL_API SQLSetEnvAttr(SQLHENV EnvironmentHandle,
           SQLINTEGER Attribute, SQLPOINTER Value,
           SQLINTEGER StringLength);
#endif /* ODBCVER >= 0x0300 */
SQLRETURN  SQL_API SQLSetParam(SQLHSTMT StatementHandle,
           SQLUSMALLINT ParameterNumber, SQLSMALLINT ValueType,
           SQLSMALLINT ParameterType, SQLUINTEGER LengthPrecision,
           SQLSMALLINT ParameterScale, SQLPOINTER ParameterValue,
           SQLINTEGER *StrLen_or_Ind);
#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLSetStmtAttr(SQLHSTMT StatementHandle,
           SQLINTEGER Attribute, SQLPOINTER Value,
           SQLINTEGER StringLength);
#endif
SQLRETURN  SQL_API SQLSetStmtOption(SQLHSTMT StatementHandle,
           SQLUSMALLINT Option, SQLUINTEGER Value);
SQLRETURN  SQL_API SQLSpecialColumns(SQLHSTMT StatementHandle,
           SQLUSMALLINT IdentifierType, SQLCHAR *CatalogName,
           SQLSMALLINT NameLength1, SQLCHAR *SchemaName,
           SQLSMALLINT NameLength2, SQLCHAR *TableName,
           SQLSMALLINT NameLength3, SQLUSMALLINT Scope,
           SQLUSMALLINT Nullable);
SQLRETURN  SQL_API SQLStatistics(SQLHSTMT StatementHandle,
           SQLCHAR *CatalogName, SQLSMALLINT NameLength1,
           SQLCHAR *SchemaName, SQLSMALLINT NameLength2,
           SQLCHAR *TableName, SQLSMALLINT NameLength3,
           SQLUSMALLINT Unique, SQLUSMALLINT Reserved);
SQLRETURN  SQL_API SQLTables(SQLHSTMT StatementHandle,
           SQLCHAR *CatalogName, SQLSMALLINT NameLength1,
           SQLCHAR *SchemaName, SQLSMALLINT NameLength2,
           SQLCHAR *TableName, SQLSMALLINT NameLength3,
           SQLCHAR *TableType, SQLSMALLINT NameLength4);
SQLRETURN  SQL_API SQLTransact(SQLHENV EnvironmentHandle,
           SQLHDBC ConnectionHandle, SQLUSMALLINT CompletionType);
#endif  /* RC_INVOKED */
#ifdef __cplusplus
}                                    /* End of extern "C" { */
#endif  /* __cplusplus */
/*****************************************************************
** SQLEXT.H - This is the include for applications using
**             the Microsoft SQL Extensions
**
** (C) Copyright 1990 - 1996 By Microsoft Corp.
**
**      Updated 05/12/93 for 2.00 specification
**      Updated 05/23/94 for 2.01 specification
**      Updated 10/27/94 for 2.10 specification
**      Updated 04/10/95 for 2.50 specification
** Updated 07/25/95 for 3.00 specification
** Updated 01/12/96 for 3.00 preliminary release 
**  Updated 09/16/96 for 3.00 SDK release
** Updated 11/21/96 for bug #4436 
*********************************************************************/
#ifdef __cplusplus
extern "C" {                         /* Assume C declarations for C++ */
#endif  /* __cplusplus */
/* generally useful constants */
#define SQL_SPEC_MAJOR     3      /* Major version of specification  */
#define SQL_SPEC_MINOR    00      /* Minor version of specification  */
#define SQL_SPEC_STRING   "03.00" /* String constant for version */
#define SQL_SQLSTATE_SIZE 5 /* size of SQLSTATE */
#define SQL_MAX_DSN_LENGTH 32 /* maximum data source name size */
#define SQL_MAX_OPTION_STRING_LENGTH    256
/* return code SQL_NO_DATA_FOUND is the same as SQL_NO_DATA */
#if (ODBCVER < 0x0300)
#define SQL_NO_DATA_FOUND 100
#else
#define SQL_NO_DATA_FOUND SQL_NO_DATA
#endif
/* an end handle type */
#if (ODBCVER >= 0x0300)
#define SQL_HANDLE_SENV 5
#endif  /* ODBCVER >= 0x0300 */
/* env attribute */
#if (ODBCVER >= 0x0300)
#define SQL_ATTR_ODBC_VERSION 200
#define SQL_ATTR_CONNECTION_POOLING 201
#define SQL_ATTR_CP_MATCH 202
#endif  /* ODBCVER >= 0x0300 */
#if (ODBCVER >= 0x0300)
/* values for SQL_ATTR_CONNECTION_POOLING */
#define SQL_CP_OFF 0UL
#define SQL_CP_ONE_PER_DRIVER 1UL
#define SQL_CP_ONE_PER_HENV 2UL
#define SQL_CP_DEFAULT SQL_CP_OFF
/* values for SQL_ATTR_CP_MATCH */
#define SQL_CP_STRICT_MATCH 0UL
#define SQL_CP_RELAXED_MATCH 1UL
#define SQL_CP_MATCH_DEFAULT SQL_CP_STRICT_MATCH
/* values for SQL_ATTR_ODBC_VERSION */
#define SQL_OV_ODBC2 2UL
#define SQL_OV_ODBC3 3UL
#endif  /* ODBCVER >= 0x0300 */
/* connection attributes */
#define SQL_ACCESS_MODE                 101
#define SQL_AUTOCOMMIT                  102
#define SQL_LOGIN_TIMEOUT               103
#define SQL_OPT_TRACE                   104
#define SQL_OPT_TRACEFILE               105
#define SQL_TRANSLATE_DLL               106
#define SQL_TRANSLATE_OPTION            107
#define SQL_TXN_ISOLATION               108
#define SQL_CURRENT_QUALIFIER           109
#define SQL_ODBC_CURSORS                110
#define SQL_QUIET_MODE                  111
#define SQL_PACKET_SIZE                 112
/* connection attributes with new names */
#if (ODBCVER >= 0x0300)
#define SQL_ATTR_ACCESS_MODE SQL_ACCESS_MODE
#define SQL_ATTR_AUTOCOMMIT SQL_AUTOCOMMIT
#define SQL_ATTR_CONNECTION_TIMEOUT 113
#define SQL_ATTR_CURRENT_CATALOG SQL_CURRENT_QUALIFIER
#define SQL_ATTR_DISCONNECT_BEHAVIOR 114
#define SQL_ATTR_ENLIST_IN_DTC 1207
#define SQL_ATTR_ENLIST_IN_XA 1208
#define SQL_ATTR_LOGIN_TIMEOUT SQL_LOGIN_TIMEOUT
#define SQL_ATTR_ODBC_CURSORS SQL_ODBC_CURSORS
#define SQL_ATTR_PACKET_SIZE SQL_PACKET_SIZE
#define SQL_ATTR_QUIET_MODE SQL_QUIET_MODE
#define SQL_ATTR_TRACE SQL_OPT_TRACE
#define SQL_ATTR_TRACEFILE SQL_OPT_TRACEFILE
#define SQL_ATTR_TRANSLATE_LIB SQL_TRANSLATE_DLL
#define SQL_ATTR_TRANSLATE_OPTION SQL_TRANSLATE_OPTION
#define SQL_ATTR_TXN_ISOLATION SQL_TXN_ISOLATION
#endif  /* ODBCVER >= 0x0300 */
/* SQL_CONNECT_OPT_DRVR_START is not meaningful for 3.0 driver */
#if (ODBCVER < 0x0300)
#define SQL_CONNECT_OPT_DRVR_START      1000
#endif  /* ODBCVER < 0x0300 */
#if (ODBCVER < 0x0300)
#define SQL_CONN_OPT_MAX                SQL_PACKET_SIZE
#define SQL_CONN_OPT_MIN                SQL_ACCESS_MODE
#endif /* ODBCVER < 0x0300 */
/* SQL_ACCESS_MODE options */
#define SQL_MODE_READ_WRITE             0UL
#define SQL_MODE_READ_ONLY              1UL
#define SQL_MODE_DEFAULT                SQL_MODE_READ_WRITE
/* SQL_AUTOCOMMIT options */
#define SQL_AUTOCOMMIT_OFF              0UL
#define SQL_AUTOCOMMIT_ON               1UL
#define SQL_AUTOCOMMIT_DEFAULT          SQL_AUTOCOMMIT_ON
/* SQL_LOGIN_TIMEOUT options */
#define SQL_LOGIN_TIMEOUT_DEFAULT       15UL
/* SQL_OPT_TRACE options */
#define SQL_OPT_TRACE_OFF               0UL
#define SQL_OPT_TRACE_ON                1UL
#define SQL_OPT_TRACE_DEFAULT           SQL_OPT_TRACE_OFF
#define SQL_OPT_TRACE_FILE_DEFAULT      "\SQL.LOG"
/* SQL_ODBC_CURSORS options */
#define SQL_CUR_USE_IF_NEEDED           0UL
#define SQL_CUR_USE_ODBC                1UL
#define SQL_CUR_USE_DRIVER              2UL
#define SQL_CUR_DEFAULT                 SQL_CUR_USE_DRIVER
#if (ODBCVER >= 0x0300)
/* values for SQL_ATTR_DISCONNECT_BEHAVIOR */
#define SQL_DB_RETURN_TO_POOL 0UL
#define SQL_DB_DISCONNECT 1UL
#define SQL_DB_DEFAULT SQL_DB_RETURN_TO_POOL
/* values for SQL_ATTR_ENLIST_IN_DTC */
#define SQL_DTC_DONE 0L
#endif  /* ODBCVER >= 0x0300 */
/* statement attributes */
#define SQL_QUERY_TIMEOUT 0
#define SQL_MAX_ROWS 1
#define SQL_NOSCAN 2
#define SQL_MAX_LENGTH 3
#define SQL_ASYNC_ENABLE 4 /* same as SQL_ATTR_ASYNC_ENABLE */
#define SQL_BIND_TYPE 5
#define SQL_CURSOR_TYPE 6
#define SQL_CONCURRENCY 7
#define SQL_KEYSET_SIZE 8
#define SQL_ROWSET_SIZE 9
#define SQL_SIMULATE_CURSOR 10
#define SQL_RETRIEVE_DATA 11
#define SQL_USE_BOOKMARKS 12
#define SQL_GET_BOOKMARK 13      /*      GetStmtOption Only */
#define SQL_ROW_NUMBER 14      /*      GetStmtOption Only */
/* statement attributes for ODBC 3.0 */
#if (ODBCVER >= 0x0300)
#define SQL_ATTR_ASYNC_ENABLE 4
#define SQL_ATTR_CONCURRENCY SQL_CONCURRENCY
#define SQL_ATTR_CURSOR_TYPE SQL_CURSOR_TYPE
#define SQL_ATTR_ENABLE_AUTO_IPD 15
#define SQL_ATTR_FETCH_BOOKMARK_PTR 16
#define SQL_ATTR_KEYSET_SIZE SQL_KEYSET_SIZE
#define SQL_ATTR_MAX_LENGTH SQL_MAX_LENGTH
#define SQL_ATTR_MAX_ROWS SQL_MAX_ROWS
#define SQL_ATTR_NOSCAN SQL_NOSCAN
#define SQL_ATTR_PARAM_BIND_OFFSET_PTR 17
#define SQL_ATTR_PARAM_BIND_TYPE 18
#define SQL_ATTR_PARAM_OPERATION_PTR 19
#define SQL_ATTR_PARAM_STATUS_PTR 20
#define SQL_ATTR_PARAMS_PROCESSED_PTR 21
#define SQL_ATTR_PARAMSET_SIZE 22
#define SQL_ATTR_QUERY_TIMEOUT SQL_QUERY_TIMEOUT
#define SQL_ATTR_RETRIEVE_DATA SQL_RETRIEVE_DATA
#define SQL_ATTR_ROW_BIND_OFFSET_PTR 23
#define SQL_ATTR_ROW_BIND_TYPE SQL_BIND_TYPE
#define SQL_ATTR_ROW_NUMBER SQL_ROW_NUMBER    /*GetStmtAttr*/
#define SQL_ATTR_ROW_OPERATION_PTR 24
#define SQL_ATTR_ROW_STATUS_PTR 25
#define SQL_ATTR_ROWS_FETCHED_PTR 26
#define SQL_ATTR_ROW_ARRAY_SIZE 27
#define SQL_ATTR_SIMULATE_CURSOR SQL_SIMULATE_CURSOR
#define SQL_ATTR_USE_BOOKMARKS SQL_USE_BOOKMARKS
#endif  /* ODBCVER >= 0x0300 */
#if (ODBCVER < 0x0300)
#define SQL_STMT_OPT_MAX                SQL_ROW_NUMBER
#define SQL_STMT_OPT_MIN SQL_QUERY_TIMEOUT
#endif     /* ODBCVER < 0x0300 */
/* New defines for SEARCHABLE column in SQLGetTypeInfo */
#if (ODBCVER >= 0x0300)
#define SQL_COL_PRED_CHAR SQL_LIKE_ONLY
#define SQL_COL_PRED_BASIC SQL_ALL_EXCEPT_LIKE
#endif /* ODBCVER >= 0x0300 */
/* whether an attribute is a pointer or not */
#if (ODBCVER >= 0x0300)
#define SQL_IS_POINTER (-4)
#define SQL_IS_UINTEGER (-5)
#define SQL_IS_INTEGER (-6)
#define SQL_IS_USMALLINT (-7)
#define SQL_IS_SMALLINT (-8)
#endif  /* ODBCVER >= 0x0300 */
/* the value of SQL_ATTR_PARAM_BIND_TYPE */
#if (ODBCVER >= 0x0300)
#define SQL_PARAM_BIND_BY_COLUMN 0UL
#define SQL_PARAM_BIND_TYPE_DEFAULT SQL_PARAM_BIND_BY_COLUMN
#endif  /* ODBCVER >= 0x0300 */
/* SQL_QUERY_TIMEOUT options */
#define SQL_QUERY_TIMEOUT_DEFAULT       0UL
/* SQL_MAX_ROWS options */
#define SQL_MAX_ROWS_DEFAULT            0UL
/* SQL_NOSCAN options */
#define SQL_NOSCAN_OFF                  0UL     /*      1.0 FALSE */
#define SQL_NOSCAN_ON                   1UL     /*      1.0 TRUE */
#define SQL_NOSCAN_DEFAULT              SQL_NOSCAN_OFF
/* SQL_MAX_LENGTH options */
#define SQL_MAX_LENGTH_DEFAULT          0UL
/* values for SQL_ATTR_ASYNC_ENABLE */
#define SQL_ASYNC_ENABLE_OFF 0UL
#define SQL_ASYNC_ENABLE_ON 1UL
#define SQL_ASYNC_ENABLE_DEFAULT        SQL_ASYNC_ENABLE_OFF
/* SQL_BIND_TYPE options */
#define SQL_BIND_BY_COLUMN              0UL
#define SQL_BIND_TYPE_DEFAULT           SQL_BIND_BY_COLUMN  /* Default value */
/* SQL_CONCURRENCY options */
#define SQL_CONCUR_READ_ONLY            1
#define SQL_CONCUR_LOCK                 2
#define SQL_CONCUR_ROWVER               3
#define SQL_CONCUR_VALUES               4
#define SQL_CONCUR_DEFAULT              SQL_CONCUR_READ_ONLY /* Default value */
/* SQL_CURSOR_TYPE options */
#define SQL_CURSOR_FORWARD_ONLY         0UL
#define SQL_CURSOR_KEYSET_DRIVEN        1UL
#define SQL_CURSOR_DYNAMIC              2UL
#define SQL_CURSOR_STATIC               3UL
#define SQL_CURSOR_TYPE_DEFAULT         SQL_CURSOR_FORWARD_ONLY /* Default value */
/* SQL_ROWSET_SIZE options */
#define SQL_ROWSET_SIZE_DEFAULT         1UL
/* SQL_KEYSET_SIZE options */
#define SQL_KEYSET_SIZE_DEFAULT         0UL
/* SQL_SIMULATE_CURSOR options */
#define SQL_SC_NON_UNIQUE               0UL
#define SQL_SC_TRY_UNIQUE               1UL
#define SQL_SC_UNIQUE                   2UL
/* SQL_RETRIEVE_DATA options */
#define SQL_RD_OFF                      0UL
#define SQL_RD_ON                       1UL
#define SQL_RD_DEFAULT                  SQL_RD_ON
/* SQL_USE_BOOKMARKS options */
#define SQL_UB_OFF                      0UL
#define SQL_UB_ON 01UL
#define SQL_UB_DEFAULT                  SQL_UB_OFF
/* New values for SQL_USE_BOOKMARKS attribute */
#if (ODBCVER >= 0x0300)
#define SQL_UB_FIXED SQL_UB_ON
#define SQL_UB_VARIABLE 2UL
#endif  /* ODBCVER >= 0x0300 */
/* extended descriptor field */
#if (ODBCVER >= 0x0300)
#define SQL_DESC_ARRAY_SIZE 20
#define SQL_DESC_ARRAY_STATUS_PTR 21
#define SQL_DESC_AUTO_UNIQUE_VALUE SQL_COLUMN_AUTO_INCREMENT
#define SQL_DESC_BASE_COLUMN_NAME 22
#define SQL_DESC_BASE_TABLE_NAME 23
#define SQL_DESC_BIND_OFFSET_PTR 24
#define SQL_DESC_BIND_TYPE 25
#define SQL_DESC_CASE_SENSITIVE SQL_COLUMN_CASE_SENSITIVE
#define SQL_DESC_CATALOG_NAME SQL_COLUMN_QUALIFIER_NAME
#define SQL_DESC_CONCISE_TYPE SQL_COLUMN_TYPE
#define SQL_DESC_DATETIME_INTERVAL_PRECISION 26
#define SQL_DESC_DISPLAY_SIZE SQL_COLUMN_DISPLAY_SIZE
#define SQL_DESC_FIXED_PREC_SCALE SQL_COLUMN_MONEY
#define SQL_DESC_LABEL SQL_COLUMN_LABEL
#define SQL_DESC_LITERAL_PREFIX 27
#define SQL_DESC_LITERAL_SUFFIX 28
#define SQL_DESC_LOCAL_TYPE_NAME 29
#define SQL_DESC_MAXIMUM_SCALE 30
#define SQL_DESC_MINIMUM_SCALE 31
#define SQL_DESC_NUM_PREC_RADIX 32
#define SQL_DESC_PARAMETER_TYPE 33
#define SQL_DESC_ROWS_PROCESSED_PTR 34
#define SQL_DESC_SCHEMA_NAME SQL_COLUMN_OWNER_NAME
#define SQL_DESC_SEARCHABLE SQL_COLUMN_SEARCHABLE
#define SQL_DESC_TYPE_NAME SQL_COLUMN_TYPE_NAME
#define SQL_DESC_TABLE_NAME SQL_COLUMN_TABLE_NAME
#define SQL_DESC_UNSIGNED SQL_COLUMN_UNSIGNED
#define SQL_DESC_UPDATABLE SQL_COLUMN_UPDATABLE
#endif
/* defines for diagnostics fields */
#if (ODBCVER >= 0x0300)
#define SQL_DIAG_CURSOR_ROW_COUNT (-1249)
#define SQL_DIAG_ROW_NUMBER (-1248)
#define SQL_DIAG_COLUMN_NUMBER (-1247)
#endif /* ODBCVER >= 0x0300 */
/* dynamic function codes */
#if (ODBCVER >= 0x0300)
#define SQL_DIAG_CALL 7
#endif  /* ODBCVER >= 0x0300 */
/* SQL extended datatypes */
#define SQL_DATE                                9
#if (ODBCVER >= 0x0300)
#define SQL_INTERVAL 10
#endif  /* ODBCVER >= 0x0300 */
#define SQL_TIME                                10
#define SQL_TIMESTAMP                           11
#define SQL_LONGVARCHAR                         (-1)
#define SQL_BINARY                              (-2)
#define SQL_VARBINARY                           (-3)
#define SQL_LONGVARBINARY                       (-4)
#define SQL_BIGINT                              (-5)
#define SQL_TINYINT                             (-6)
#define SQL_BIT                                 (-7)
#if (ODBCVER >= 0x0300)
/* interval code */
#define SQL_CODE_YEAR 1
#define SQL_CODE_MONTH 2
#define SQL_CODE_DAY 3
#define SQL_CODE_HOUR 4
#define SQL_CODE_MINUTE 5
#define SQL_CODE_SECOND 6
#define SQL_CODE_YEAR_TO_MONTH 7
#define SQL_CODE_DAY_TO_HOUR 8
#define SQL_CODE_DAY_TO_MINUTE 9
#define SQL_CODE_DAY_TO_SECOND 10
#define SQL_CODE_HOUR_TO_MINUTE 11
#define SQL_CODE_HOUR_TO_SECOND 12
#define SQL_CODE_MINUTE_TO_SECOND 13
#define SQL_INTERVAL_YEAR (100 + SQL_CODE_YEAR)
#define SQL_INTERVAL_MONTH (100 + SQL_CODE_MONTH)
#define SQL_INTERVAL_DAY (100 + SQL_CODE_DAY) 
#define SQL_INTERVAL_HOUR (100 + SQL_CODE_HOUR) 
#define SQL_INTERVAL_MINUTE (100 + SQL_CODE_MINUTE) 
#define SQL_INTERVAL_SECOND                 (100 + SQL_CODE_SECOND) 
#define SQL_INTERVAL_YEAR_TO_MONTH (100 + SQL_CODE_YEAR_TO_MONTH)
#define SQL_INTERVAL_DAY_TO_HOUR (100 + SQL_CODE_DAY_TO_HOUR) 
#define SQL_INTERVAL_DAY_TO_MINUTE (100 + SQL_CODE_DAY_TO_MINUTE) 
#define SQL_INTERVAL_DAY_TO_SECOND (100 + SQL_CODE_DAY_TO_SECOND) 
#define SQL_INTERVAL_HOUR_TO_MINUTE (100 + SQL_CODE_HOUR_TO_MINUTE)
#define SQL_INTERVAL_HOUR_TO_SECOND (100 + SQL_CODE_HOUR_TO_SECOND) 
#define SQL_INTERVAL_MINUTE_TO_SECOND (100 + SQL_CODE_MINUTE_TO_SECOND) 
#else
#define SQL_INTERVAL_YEAR                       (-80)
#define SQL_INTERVAL_MONTH                      (-81)
#define SQL_INTERVAL_YEAR_TO_MONTH              (-82)
#define SQL_INTERVAL_DAY                        (-83)
#define SQL_INTERVAL_HOUR                       (-84)
#define SQL_INTERVAL_MINUTE                     (-85)
#define SQL_INTERVAL_SECOND                     (-86)
#define SQL_INTERVAL_DAY_TO_HOUR                (-87)
#define SQL_INTERVAL_DAY_TO_MINUTE              (-88)
#define SQL_INTERVAL_DAY_TO_SECOND              (-89)
#define SQL_INTERVAL_HOUR_TO_MINUTE             (-90)
#define SQL_INTERVAL_HOUR_TO_SECOND             (-91)
#define SQL_INTERVAL_MINUTE_TO_SECOND           (-92)
#endif  /* ODBCVER >= 0x0300 */
#define SQL_UNICODE                             (-95)
#define SQL_UNICODE_VARCHAR                     (-96)
#define SQL_UNICODE_LONGVARCHAR                 (-97)
#define SQL_UNICODE_CHAR                        SQL_UNICODE
#if (ODBCVER < 0x0300)
#define SQL_TYPE_DRIVER_START                   SQL_INTERVAL_YEAR
#define SQL_TYPE_DRIVER_END                     SQL_UNICODE_LONGVARCHAR
#endif  /* ODBCVER < 0x0300 */
/* C datatype to SQL datatype mapping      SQL types
                                           ------------------- */
#define SQL_C_CHAR    SQL_CHAR             /* CHAR, VARCHAR, DECIMAL, NUMERIC */
#define SQL_C_LONG    SQL_INTEGER          /* INTEGER                      */
#define SQL_C_SHORT   SQL_SMALLINT         /* SMALLINT                     */
#define SQL_C_FLOAT   SQL_REAL             /* REAL                         */
#define SQL_C_DOUBLE  SQL_DOUBLE           /* FLOAT, DOUBLE                */
#if (ODBCVER >= 0x0300)
#define SQL_C_NUMERIC SQL_NUMERIC
#endif  /* ODBCVER >= 0x0300 */
#define SQL_C_DEFAULT 99
#define SQL_SIGNED_OFFSET       (-20)
#define SQL_UNSIGNED_OFFSET     (-22)
/* C datatype to SQL datatype mapping */
#define SQL_C_DATE       SQL_DATE
#define SQL_C_TIME       SQL_TIME
#define SQL_C_TIMESTAMP  SQL_TIMESTAMP
#if (ODBCVER >= 0x0300)
#define SQL_C_TYPE_DATE SQL_TYPE_DATE
#define SQL_C_TYPE_TIME SQL_TYPE_TIME
#define SQL_C_TYPE_TIMESTAMP SQL_TYPE_TIMESTAMP
#define SQL_C_INTERVAL_YEAR SQL_INTERVAL_YEAR
#define SQL_C_INTERVAL_MONTH SQL_INTERVAL_MONTH
#define SQL_C_INTERVAL_DAY SQL_INTERVAL_DAY
#define SQL_C_INTERVAL_HOUR SQL_INTERVAL_HOUR
#define SQL_C_INTERVAL_MINUTE SQL_INTERVAL_MINUTE
#define SQL_C_INTERVAL_SECOND SQL_INTERVAL_SECOND
#define SQL_C_INTERVAL_YEAR_TO_MONTH SQL_INTERVAL_YEAR_TO_MONTH
#define SQL_C_INTERVAL_DAY_TO_HOUR SQL_INTERVAL_DAY_TO_HOUR
#define SQL_C_INTERVAL_DAY_TO_MINUTE SQL_INTERVAL_DAY_TO_MINUTE
#define SQL_C_INTERVAL_DAY_TO_SECOND SQL_INTERVAL_DAY_TO_SECOND
#define SQL_C_INTERVAL_HOUR_TO_MINUTE SQL_INTERVAL_HOUR_TO_MINUTE
#define SQL_C_INTERVAL_HOUR_TO_SECOND SQL_INTERVAL_HOUR_TO_SECOND
#define SQL_C_INTERVAL_MINUTE_TO_SECOND SQL_INTERVAL_MINUTE_TO_SECOND
#endif  /* ODBCVER >= 0x0300 */
#define SQL_C_BINARY     SQL_BINARY
#define SQL_C_BIT        SQL_BIT
#if (ODBCVER >= 0x0300)
#define SQL_C_SBIGINT (SQL_BIGINT+SQL_SIGNED_OFFSET)    /* SIGNED BIGINT */
#define SQL_C_UBIGINT (SQL_BIGINT+SQL_UNSIGNED_OFFSET)   /* UNSIGNED BIGINT */
#endif  /* ODBCVER >= 0x0300 */
#define SQL_C_TINYINT    SQL_TINYINT
#define SQL_C_SLONG      (SQL_C_LONG+SQL_SIGNED_OFFSET)    /* SIGNED INTEGER  */
#define SQL_C_SSHORT     (SQL_C_SHORT+SQL_SIGNED_OFFSET)   /* SIGNED SMALLINT */
#define SQL_C_STINYINT   (SQL_TINYINT+SQL_SIGNED_OFFSET)   /* SIGNED TINYINT  */
#define SQL_C_ULONG      (SQL_C_LONG+SQL_UNSIGNED_OFFSET)  /* UNSIGNED INTEGER*/
#define SQL_C_USHORT     (SQL_C_SHORT+SQL_UNSIGNED_OFFSET) /* UNSIGNED SMALLINT*/
#define SQL_C_UTINYINT   (SQL_TINYINT+SQL_UNSIGNED_OFFSET) /* UNSIGNED TINYINT*/
#define SQL_C_BOOKMARK   SQL_C_ULONG                       /* BOOKMARK        */
#define SQL_TYPE_NULL                   0
#if (ODBCVER < 0x0300)
#define SQL_TYPE_MIN                    SQL_BIT
#define SQL_TYPE_MAX                    SQL_VARCHAR
#endif
#if (ODBCVER >= 0x0300)
#define SQL_C_VARBOOKMARK SQL_C_BINARY
#endif  /* ODBCVER >= 0x0300 */
/* define for SQL_DIAG_ROW_NUMBER and SQL_DIAG_COLUMN_NUMBER */
#if (ODBCVER >= 0x0300)
#define SQL_NO_ROW_NUMBER (-1)
#define SQL_NO_COLUMN_NUMBER (-1)
#define SQL_ROW_NUMBER_UNKNOWN (-2)
#define SQL_COLUMN_NUMBER_UNKNOWN (-2)
#endif
/* SQLBindParameter extensions */
#define SQL_DEFAULT_PARAM            (-5)
#define SQL_IGNORE                   (-6)
#if (ODBCVER >= 0x0300)
#define SQL_COLUMN_IGNORE SQL_IGNORE
#endif  /* ODBCVER >= 0x0300 */
#define SQL_LEN_DATA_AT_EXEC_OFFSET  (-100)
#define SQL_LEN_DATA_AT_EXEC(length) (-(length)+SQL_LEN_DATA_AT_EXEC_OFFSET)
/* binary length for driver specific attributes */
#define SQL_LEN_BINARY_ATTR_OFFSET  (-100)
#define SQL_LEN_BINARY_ATTR(length)  (-(length)+SQL_LEN_BINARY_ATTR_OFFSET)
/* Defines used by Driver Manager when mapping SQLSetParam to SQLBindParameter
*/
#define SQL_PARAM_TYPE_DEFAULT           SQL_PARAM_INPUT_OUTPUT
#define SQL_SETPARAM_VALUE_MAX           (-1L)
/* SQLColAttributes defines */
#define SQL_COLUMN_COUNT                0
#define SQL_COLUMN_NAME                 1
#define SQL_COLUMN_TYPE                 2
#define SQL_COLUMN_LENGTH               3
#define SQL_COLUMN_PRECISION            4
#define SQL_COLUMN_SCALE                5
#define SQL_COLUMN_DISPLAY_SIZE         6
#define SQL_COLUMN_NULLABLE             7
#define SQL_COLUMN_UNSIGNED             8
#define SQL_COLUMN_MONEY                9
#define SQL_COLUMN_UPDATABLE            10
#define SQL_COLUMN_AUTO_INCREMENT       11
#define SQL_COLUMN_CASE_SENSITIVE       12
#define SQL_COLUMN_SEARCHABLE           13
#define SQL_COLUMN_TYPE_NAME            14
#define SQL_COLUMN_TABLE_NAME           15
#define SQL_COLUMN_OWNER_NAME           16
#define SQL_COLUMN_QUALIFIER_NAME       17
#define SQL_COLUMN_LABEL                18
#define SQL_COLATT_OPT_MAX              SQL_COLUMN_LABEL
#if (ODBCVER < 0x0300)
#define SQL_COLUMN_DRIVER_START         1000
#endif  /* ODBCVER < 0x0300 */
#define SQL_COLATT_OPT_MIN              SQL_COLUMN_COUNT
/* SQLColAttributes subdefines for SQL_COLUMN_UPDATABLE */
#define SQL_ATTR_READONLY               0
#define SQL_ATTR_WRITE                  1
#define SQL_ATTR_READWRITE_UNKNOWN      2
/* SQLColAttributes subdefines for SQL_COLUMN_SEARCHABLE */
/* These are also used by SQLGetInfo                     */
#define SQL_UNSEARCHABLE                0
#define SQL_LIKE_ONLY                   1
#define SQL_ALL_EXCEPT_LIKE             2
#define SQL_SEARCHABLE                  3
#define SQL_PRED_SEARCHABLE SQL_SEARCHABLE
/* Special return values for SQLGetData */
#define SQL_NO_TOTAL                    (-4)
/********************************************/
/* SQLGetFunctions: additional values for   */
/* fFunction to represent functions that    */
/* are not in the X/Open spec. */
/********************************************/
#if (ODBCVER >= 0x0300)
#define SQL_API_SQLALLOCHANDLESTD 73
#define SQL_API_SQLBULKOPERATIONS 24
#endif /* ODBCVER >= 0x0300 */
#define SQL_API_SQLBINDPARAMETER    72
#define SQL_API_SQLBROWSECONNECT    55    
#define SQL_API_SQLCOLATTRIBUTES    6 
#define SQL_API_SQLCOLUMNPRIVILEGES 56
#define SQL_API_SQLDESCRIBEPARAM    58
#define SQL_API_SQLDRIVERCONNECT 41 
#define SQL_API_SQLDRIVERS          71
#define SQL_API_SQLEXTENDEDFETCH    59
#define SQL_API_SQLFOREIGNKEYS      60
#define SQL_API_SQLMORERESULTS      61
#define SQL_API_SQLNATIVESQL        62
#define SQL_API_SQLNUMPARAMS        63
#define SQL_API_SQLPARAMOPTIONS     64
#define SQL_API_SQLPRIMARYKEYS      65
#define SQL_API_SQLPROCEDURECOLUMNS 66
#define SQL_API_SQLPROCEDURES       67
#define SQL_API_SQLSETPOS           68
#define SQL_API_SQLSETSCROLLOPTIONS 69
#define SQL_API_SQLTABLEPRIVILEGES  70
/*-------------------------------------------*/
/* SQL_EXT_API_LAST is not useful with ODBC  */
/* version 3.0 because some of the values    */
/* from X/Open are in the 10000 range.       */
/*-------------------------------------------*/
#if (ODBCVER < 0x0300)
#define SQL_EXT_API_LAST            SQL_API_SQLBINDPARAMETER
#define SQL_NUM_FUNCTIONS           23
#define SQL_EXT_API_START           40
#define SQL_NUM_EXTENSIONS (SQL_EXT_API_LAST-SQL_EXT_API_START+1)
#endif
/*--------------------------------------------*/
/* SQL_API_ALL_FUNCTIONS returns an array     */
/* of 'booleans' representing whether a       */
/* function is implemented by the driver.     */
/*                                            */
/* CAUTION: Only functions defined in ODBC    */
/* version 2.0 and earlier are returned, the  */
/* new high-range function numbers defined by */
/* X/Open break this scheme.   See the new    */
/* method -- SQL_API_ODBC3_ALL_FUNCTIONS      */
/*--------------------------------------------*/
#define SQL_API_ALL_FUNCTIONS       0 /* See CAUTION above */
/*----------------------------------------------*/
/* 2.X drivers export a dummy function with   */
/* ordinal number SQL_API_LOADBYORDINAL to speed*/
/* loading under the windows operating system.  */
/*  */
/* CAUTION: Loading by ordinal is not supported */
/* for 3.0 and above drivers. */
/*----------------------------------------------*/
#define SQL_API_LOADBYORDINAL       199 /* See CAUTION above */
/*----------------------------------------------*/
/* SQL_API_ODBC3_ALL_FUNCTIONS                  */
/* This returns a bitmap, which allows us to    */
/* handle the higher-valued function numbers.   */
/* Use  SQL_FUNC_EXISTS(bitmap,function_number) */
/* to determine if the function exists.         */
/*----------------------------------------------*/
#if (ODBCVER >= 0x0300)
#define SQL_API_ODBC3_ALL_FUNCTIONS 999
#define SQL_API_ODBC3_ALL_FUNCTIONS_SIZE 250 /* array of 250 words */
#define SQL_FUNC_EXISTS(pfExists, uwAPI) ((*(((UWORD*) (pfExists)) + ((uwAPI) >> 4)) & (1 << ((uwAPI) & 0x000F)) ) ? SQL_TRUE : SQL_FALSE )
#endif  /* ODBCVER >= 0x0300 */
/************************************************/
/* Extended definitions for SQLGetInfo */
/************************************************/
/*---------------------------------*/
/* Values in ODBC 2.0 that are not */
/* in the X/Open spec              */
/*---------------------------------*/
#define SQL_INFO_FIRST                       0
#define SQL_ACTIVE_CONNECTIONS               0 /* MAX_DRIVER_CONNECTIONS */
#define SQL_ACTIVE_STATEMENTS                1 /* MAX_CONCURRENT_ACTIVITIES */
#define SQL_DRIVER_HDBC                      3
#define SQL_DRIVER_HENV                      4
#define SQL_DRIVER_HSTMT                     5
#define SQL_DRIVER_NAME                      6
#define SQL_DRIVER_VER                       7
#define SQL_ODBC_API_CONFORMANCE             9
#define SQL_ODBC_VER                        10
#define SQL_ROW_UPDATES                     11
#define SQL_ODBC_SAG_CLI_CONFORMANCE        12
#define SQL_ODBC_SQL_CONFORMANCE            15
#define SQL_PROCEDURES                      21
#define SQL_CONCAT_NULL_BEHAVIOR            22
#define SQL_CURSOR_ROLLBACK_BEHAVIOR        24
#define SQL_EXPRESSIONS_IN_ORDERBY          27
#define SQL_MAX_OWNER_NAME_LEN              32 /* MAX_SCHEMA_NAME_LEN */
#define SQL_MAX_PROCEDURE_NAME_LEN          33
#define SQL_MAX_QUALIFIER_NAME_LEN          34 /* MAX_CATALOG_NAME_LEN */
#define SQL_MULT_RESULT_SETS                36
#define SQL_MULTIPLE_ACTIVE_TXN             37
#define SQL_OUTER_JOINS                     38
#define SQL_OWNER_TERM                      39
#define SQL_PROCEDURE_TERM                  40
#define SQL_QUALIFIER_NAME_SEPARATOR        41
#define SQL_QUALIFIER_TERM                  42
#define SQL_SCROLL_OPTIONS                  44
#define SQL_TABLE_TERM                      45
#define SQL_CONVERT_FUNCTIONS               48
#define SQL_NUMERIC_FUNCTIONS               49
#define SQL_STRING_FUNCTIONS                50
#define SQL_SYSTEM_FUNCTIONS                51
#define SQL_TIMEDATE_FUNCTIONS              52
#define SQL_CONVERT_BIGINT                  53
#define SQL_CONVERT_BINARY                  54
#define SQL_CONVERT_BIT                     55
#define SQL_CONVERT_CHAR                    56
#define SQL_CONVERT_DATE                    57
#define SQL_CONVERT_DECIMAL                 58
#define SQL_CONVERT_DOUBLE                  59
#define SQL_CONVERT_FLOAT                   60
#define SQL_CONVERT_INTEGER                 61
#define SQL_CONVERT_LONGVARCHAR             62
#define SQL_CONVERT_NUMERIC                 63
#define SQL_CONVERT_REAL                    64
#define SQL_CONVERT_SMALLINT                65
#define SQL_CONVERT_TIME                    66
#define SQL_CONVERT_TIMESTAMP               67
#define SQL_CONVERT_TINYINT                 68
#define SQL_CONVERT_VARBINARY               69
#define SQL_CONVERT_VARCHAR                 70
#define SQL_CONVERT_LONGVARBINARY           71
#define SQL_ODBC_SQL_OPT_IEF                73 /* SQL_INTEGRITY */
#define SQL_CORRELATION_NAME                74
#define SQL_NON_NULLABLE_COLUMNS            75
#define SQL_DRIVER_HLIB                     76
#define SQL_DRIVER_ODBC_VER                 77
#define SQL_LOCK_TYPES                      78
#define SQL_POS_OPERATIONS                  79
#define SQL_POSITIONED_STATEMENTS           80
#define SQL_BOOKMARK_PERSISTENCE            82
#define SQL_STATIC_SENSITIVITY              83
#define SQL_FILE_USAGE                      84
#define SQL_COLUMN_ALIAS                    87
#define SQL_GROUP_BY                        88
#define SQL_KEYWORDS                        89
#define SQL_OWNER_USAGE                     91
#define SQL_QUALIFIER_USAGE                 92
#define SQL_QUOTED_IDENTIFIER_CASE          93
#define SQL_SUBQUERIES                      95
#define SQL_UNION                           96
#define SQL_MAX_ROW_SIZE_INCLUDES_LONG      103
#define SQL_MAX_CHAR_LITERAL_LEN            108
#define SQL_TIMEDATE_ADD_INTERVALS          109
#define SQL_TIMEDATE_DIFF_INTERVALS         110
#define SQL_NEED_LONG_DATA_LEN              111
#define SQL_MAX_BINARY_LITERAL_LEN          112
#define SQL_LIKE_ESCAPE_CLAUSE              113
#define SQL_QUALIFIER_LOCATION              114
#if (ODBCVER >= 0x0201 && ODBCVER < 0x0300)
#define SQL_OJ_CAPABILITIES         65003  /* Temp value until ODBC 3.0 */
#endif  /* ODBCVER >= 0x0201 && ODBCVER < 0x0300 */
/*----------------------------------------------*/
/* SQL_INFO_LAST and SQL_INFO_DRIVER_START are  */
/* not useful anymore, because  X/Open has      */
/* values in the 10000 range.   You   */
/* must contact X/Open directly to get a range */
/* of numbers for driver-specific values.     */
/*----------------------------------------------*/
#if (ODBCVER < 0x0300)
#define SQL_INFO_LAST SQL_QUALIFIER_LOCATION
#define SQL_INFO_DRIVER_START 1000
#endif /* ODBCVER < 0x0300 */
/*-----------------------------------------------*/
/* ODBC 3.0 SQLGetInfo values that are not part  */
/* of the X/Open standard at this time.   X/Open */
/* standard values are in sql.h.  */
/*-----------------------------------------------*/
#if (ODBCVER >= 0x0300)
#define SQL_ACTIVE_ENVIRONMENTS 116
#define SQL_ALTER_DOMAIN 117
#define SQL_SQL_CONFORMANCE 118
#define SQL_DATETIME_LITERALS 119
#define SQL_ASYNC_MODE 10021 /* new X/Open spec */
#define SQL_BATCH_ROW_COUNT 120
#define SQL_BATCH_SUPPORT 121
#define SQL_CATALOG_LOCATION SQL_QUALIFIER_LOCATION
#define SQL_CATALOG_NAME_SEPARATOR SQL_QUALIFIER_NAME_SEPARATOR
#define SQL_CATALOG_TERM SQL_QUALIFIER_TERM
#define SQL_CATALOG_USAGE SQL_QUALIFIER_USAGE
#define SQL_CONVERT_WCHAR 122
#define SQL_CONVERT_INTERVAL_DAY_TIME 123
#define SQL_CONVERT_INTERVAL_YEAR_MONTH 124
#define SQL_CONVERT_WLONGVARCHAR 125
#define SQL_CONVERT_WVARCHAR 126
#define SQL_CREATE_ASSERTION 127
#define SQL_CREATE_CHARACTER_SET 128
#define SQL_CREATE_COLLATION 129
#define SQL_CREATE_DOMAIN 130
#define SQL_CREATE_SCHEMA 131
#define SQL_CREATE_TABLE 132
#define SQL_CREATE_TRANSLATION 133
#define SQL_CREATE_VIEW 134
#define SQL_DRIVER_HDESC 135
#define SQL_DROP_ASSERTION 136
#define SQL_DROP_CHARACTER_SET 137
#define SQL_DROP_COLLATION 138
#define SQL_DROP_DOMAIN 139
#define SQL_DROP_SCHEMA 140
#define SQL_DROP_TABLE 141
#define SQL_DROP_TRANSLATION 142
#define SQL_DROP_VIEW 143
#define SQL_DYNAMIC_CURSOR_ATTRIBUTES1 144
#define SQL_DYNAMIC_CURSOR_ATTRIBUTES2 145
#define SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1 146
#define SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2 147
#define SQL_INDEX_KEYWORDS 148
#define SQL_INFO_SCHEMA_VIEWS 149
#define SQL_KEYSET_CURSOR_ATTRIBUTES1 150
#define SQL_KEYSET_CURSOR_ATTRIBUTES2 151
#define SQL_MAX_ASYNC_CONCURRENT_STATEMENTS 10022 /* new X/Open spec */
#define SQL_ODBC_INTERFACE_CONFORMANCE 152
#define SQL_PARAM_ARRAY_ROW_COUNTS      153
#define SQL_PARAM_ARRAY_SELECTS      154
#define SQL_SCHEMA_TERM SQL_OWNER_TERM
#define SQL_SCHEMA_USAGE SQL_OWNER_USAGE
#define SQL_SQL92_DATETIME_FUNCTIONS 155
#define SQL_SQL92_FOREIGN_KEY_DELETE_RULE 156
#define SQL_SQL92_FOREIGN_KEY_UPDATE_RULE 157
#define SQL_SQL92_GRANT 158
#define SQL_SQL92_NUMERIC_VALUE_FUNCTIONS 159
#define SQL_SQL92_PREDICATES 160
#define SQL_SQL92_RELATIONAL_JOIN_OPERATORS 161
#define SQL_SQL92_REVOKE 162
#define SQL_SQL92_ROW_VALUE_CONSTRUCTOR 163
#define SQL_SQL92_STRING_FUNCTIONS 164
#define SQL_SQL92_VALUE_EXPRESSIONS 165
#define SQL_STANDARD_CLI_CONFORMANCE 166
#define SQL_STATIC_CURSOR_ATTRIBUTES1 167
#define SQL_STATIC_CURSOR_ATTRIBUTES2 168
#define SQL_AGGREGATE_FUNCTIONS 169
#define SQL_DDL_INDEX 170
#define SQL_DM_VER 171
#define SQL_INSERT_STATEMENT 172
#define SQL_UNION_STATEMENT SQL_UNION
#endif  /* ODBCVER >= 0x0300 */
/* SQL_ALTER_TABLE bitmasks */
#if (ODBCVER >= 0x0300)
/* the following 5 bitmasks are defined in sql.h
*#define SQL_AT_ADD_COLUMN                    0x00000001L
*#define SQL_AT_DROP_COLUMN                   0x00000002L
*#define SQL_AT_ADD_CONSTRAINT                0x00000008L
*/
#define SQL_AT_ADD_COLUMN_SINGLE 0x00000020L
#define SQL_AT_ADD_COLUMN_DEFAULT 0x00000040L
#define SQL_AT_ADD_COLUMN_COLLATION 0x00000080L
#define SQL_AT_SET_COLUMN_DEFAULT 0x00000100L
#define SQL_AT_DROP_COLUMN_DEFAULT 0x00000200L
#define SQL_AT_DROP_COLUMN_CASCADE 0x00000400L
#define SQL_AT_DROP_COLUMN_RESTRICT 0x00000800L
#define SQL_AT_ADD_TABLE_CONSTRAINT 0x00001000L
#define SQL_AT_DROP_TABLE_CONSTRAINT_CASCADE 0x00002000L
#define SQL_AT_DROP_TABLE_CONSTRAINT_RESTRICT 0x00004000L
#define SQL_AT_CONSTRAINT_NAME_DEFINITION 0x00008000L
#define SQL_AT_CONSTRAINT_INITIALLY_DEFERRED 0x00010000L
#define SQL_AT_CONSTRAINT_INITIALLY_IMMEDIATE 0x00020000L
#define SQL_AT_CONSTRAINT_DEFERRABLE 0x00040000L
#define SQL_AT_CONSTRAINT_NON_DEFERRABLE 0x00080000L
#endif /* ODBCVER >= 0x0300 */
/* SQL_CONVERT_*  return value bitmasks */
#define SQL_CVT_CHAR                        0x00000001L
#define SQL_CVT_NUMERIC                     0x00000002L
#define SQL_CVT_DECIMAL                     0x00000004L
#define SQL_CVT_INTEGER                     0x00000008L
#define SQL_CVT_SMALLINT                    0x00000010L
#define SQL_CVT_FLOAT                       0x00000020L
#define SQL_CVT_REAL                        0x00000040L
#define SQL_CVT_DOUBLE                      0x00000080L
#define SQL_CVT_VARCHAR                     0x00000100L
#define SQL_CVT_LONGVARCHAR                 0x00000200L
#define SQL_CVT_BINARY                      0x00000400L
#define SQL_CVT_VARBINARY                   0x00000800L
#define SQL_CVT_BIT                         0x00001000L
#define SQL_CVT_TINYINT                     0x00002000L
#define SQL_CVT_BIGINT                      0x00004000L
#define SQL_CVT_DATE                        0x00008000L
#define SQL_CVT_TIME                        0x00010000L
#define SQL_CVT_TIMESTAMP                   0x00020000L
#define SQL_CVT_LONGVARBINARY               0x00040000L
#if (ODBCVER >= 0x0300)
#define SQL_CVT_INTERVAL_YEAR_MONTH      0x00080000L
#define SQL_CVT_INTERVAL_DAY_TIME      0x00100000L
#define SQL_CVT_WCHAR 0x00200000L
#define SQL_CVT_WLONGVARCHAR 0x00400000L
#define SQL_CVT_WVARCHAR 0x00800000L
#endif  /* ODBCVER >= 0x0300 */
/* SQL_CONVERT_FUNCTIONS functions */
#define SQL_FN_CVT_CONVERT                  0x00000001L
#if (ODBCVER >= 0x0300)
#define SQL_FN_CVT_CAST 0x00000002L
#endif  /* ODBCVER >= 0x0300 */
/* SQL_STRING_FUNCTIONS functions */
#define SQL_FN_STR_CONCAT                   0x00000001L
#define SQL_FN_STR_INSERT                   0x00000002L
#define SQL_FN_STR_LEFT                     0x00000004L
#define SQL_FN_STR_LTRIM                    0x00000008L
#define SQL_FN_STR_LENGTH                   0x00000010L
#define SQL_FN_STR_LOCATE                   0x00000020L
#define SQL_FN_STR_LCASE                    0x00000040L
#define SQL_FN_STR_REPEAT                   0x00000080L
#define SQL_FN_STR_REPLACE                  0x00000100L
#define SQL_FN_STR_RIGHT                    0x00000200L
#define SQL_FN_STR_RTRIM                    0x00000400L
#define SQL_FN_STR_SUBSTRING                0x00000800L
#define SQL_FN_STR_UCASE                    0x00001000L
#define SQL_FN_STR_ASCII                    0x00002000L
#define SQL_FN_STR_CHAR                     0x00004000L
#define SQL_FN_STR_DIFFERENCE               0x00008000L
#define SQL_FN_STR_LOCATE_2                 0x00010000L
#define SQL_FN_STR_SOUNDEX                  0x00020000L
#define SQL_FN_STR_SPACE                    0x00040000L
#if (ODBCVER >= 0x0300)
#define SQL_FN_STR_BIT_LENGTH 0x00080000L
#define SQL_FN_STR_CHAR_LENGTH 0x00100000L
#define SQL_FN_STR_CHARACTER_LENGTH 0x00200000L
#define SQL_FN_STR_OCTET_LENGTH 0x00400000L
#define SQL_FN_STR_POSITION 0x00800000L
#endif  /* ODBCVER >= 0x0300 */
/* SQL_SQL92_STRING_FUNCTIONS */
#if (ODBCVER >= 0x0300)
#define SQL_SSF_CONVERT 0x00000001L
#define SQL_SSF_LOWER 0x00000002L
#define SQL_SSF_UPPER 0x00000004L
#define SQL_SSF_SUBSTRING 0x00000008L
#define SQL_SSF_TRANSLATE 0x00000010L
#define SQL_SSF_TRIM_BOTH 0x00000020L
#define SQL_SSF_TRIM_LEADING 0x00000040L
#define SQL_SSF_TRIM_TRAILING 0x00000080L
#endif /* ODBCVER >= 0x0300 */
/* SQL_NUMERIC_FUNCTIONS functions */
#define SQL_FN_NUM_ABS                      0x00000001L
#define SQL_FN_NUM_ACOS                     0x00000002L
#define SQL_FN_NUM_ASIN                     0x00000004L
#define SQL_FN_NUM_ATAN                     0x00000008L
#define SQL_FN_NUM_ATAN2                    0x00000010L
#define SQL_FN_NUM_CEILING                  0x00000020L
#define SQL_FN_NUM_COS                      0x00000040L
#define SQL_FN_NUM_COT                      0x00000080L
#define SQL_FN_NUM_EXP                      0x00000100L
#define SQL_FN_NUM_FLOOR                    0x00000200L
#define SQL_FN_NUM_LOG                      0x00000400L
#define SQL_FN_NUM_MOD                      0x00000800L
#define SQL_FN_NUM_SIGN                     0x00001000L
#define SQL_FN_NUM_SIN                      0x00002000L
#define SQL_FN_NUM_SQRT                     0x00004000L
#define SQL_FN_NUM_TAN                      0x00008000L
#define SQL_FN_NUM_PI                       0x00010000L
#define SQL_FN_NUM_RAND                     0x00020000L
#define SQL_FN_NUM_DEGREES                  0x00040000L
#define SQL_FN_NUM_LOG10                    0x00080000L
#define SQL_FN_NUM_POWER                    0x00100000L
#define SQL_FN_NUM_RADIANS                  0x00200000L
#define SQL_FN_NUM_ROUND                    0x00400000L
#define SQL_FN_NUM_TRUNCATE                 0x00800000L
/* SQL_SQL92_NUMERIC_VALUE_FUNCTIONS */
#if (ODBCVER >= 0x0300)
#define SQL_SNVF_BIT_LENGTH 0x00000001L
#define SQL_SNVF_CHAR_LENGTH 0x00000002L
#define SQL_SNVF_CHARACTER_LENGTH 0x00000004L
#define SQL_SNVF_EXTRACT 0x00000008L
#define SQL_SNVF_OCTET_LENGTH 0x00000010L
#define SQL_SNVF_POSITION 0x00000020L
#endif  /* ODBCVER >= 0x0300 */
/* SQL_TIMEDATE_FUNCTIONS functions */
#define SQL_FN_TD_NOW                       0x00000001L
#define SQL_FN_TD_CURDATE                   0x00000002L
#define SQL_FN_TD_DAYOFMONTH                0x00000004L
#define SQL_FN_TD_DAYOFWEEK                 0x00000008L
#define SQL_FN_TD_DAYOFYEAR                 0x00000010L
#define SQL_FN_TD_MONTH                     0x00000020L
#define SQL_FN_TD_QUARTER                   0x00000040L
#define SQL_FN_TD_WEEK                      0x00000080L
#define SQL_FN_TD_YEAR                      0x00000100L
#define SQL_FN_TD_CURTIME                   0x00000200L
#define SQL_FN_TD_HOUR                      0x00000400L
#define SQL_FN_TD_MINUTE                    0x00000800L
#define SQL_FN_TD_SECOND                    0x00001000L
#define SQL_FN_TD_TIMESTAMPADD              0x00002000L
#define SQL_FN_TD_TIMESTAMPDIFF             0x00004000L
#define SQL_FN_TD_DAYNAME                   0x00008000L
#define SQL_FN_TD_MONTHNAME                 0x00010000L
#if (ODBCVER >= 0x0300)
#define SQL_FN_TD_CURRENT_DATE 0x00020000L
#define SQL_FN_TD_CURRENT_TIME 0x00040000L
#define SQL_FN_TD_CURRENT_TIMESTAMP 0x00080000L
#define SQL_FN_TD_EXTRACT 0x00100000L
#endif  /* ODBCVER >= 0x0300 */
/* SQL_SQL92_DATETIME_FUNCTIONS */
#if (ODBCVER >= 0x0300)
#define SQL_SDF_CURRENT_DATE 0x00000001L
#define SQL_SDF_CURRENT_TIME 0x00000002L
#define SQL_SDF_CURRENT_TIMESTAMP 0x00000004L
#endif /* ODBCVER >= 0x0300 */
/* SQL_SYSTEM_FUNCTIONS functions */
#define SQL_FN_SYS_USERNAME                 0x00000001L
#define SQL_FN_SYS_DBNAME                   0x00000002L
#define SQL_FN_SYS_IFNULL                   0x00000004L
/* SQL_TIMEDATE_ADD_INTERVALS and SQL_TIMEDATE_DIFF_INTERVALS functions */
#define SQL_FN_TSI_FRAC_SECOND              0x00000001L
#define SQL_FN_TSI_SECOND                   0x00000002L
#define SQL_FN_TSI_MINUTE                   0x00000004L
#define SQL_FN_TSI_HOUR                     0x00000008L
#define SQL_FN_TSI_DAY                      0x00000010L
#define SQL_FN_TSI_WEEK                     0x00000020L
#define SQL_FN_TSI_MONTH                    0x00000040L
#define SQL_FN_TSI_QUARTER                  0x00000080L
#define SQL_FN_TSI_YEAR                     0x00000100L
/* bitmasks for SQL_DYNAMIC_CURSOR_ATTRIBUTES1,
 * SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1, 
 * SQL_KEYSET_CURSOR_ATTRIBUTES1, and SQL_STATIC_CURSOR_ATTRIBUTES1 
 */
#if (ODBCVER >= 0x0300)
/* supported SQLFetchScroll FetchOrientation's */
#define SQL_CA1_NEXT 0x00000001L
#define SQL_CA1_ABSOLUTE 0x00000002L
#define SQL_CA1_RELATIVE 0x00000004L
#define SQL_CA1_BOOKMARK 0x00000008L
/* supported SQLSetPos LockType's */
#define SQL_CA1_LOCK_NO_CHANGE 0x00000040L
#define SQL_CA1_LOCK_EXCLUSIVE 0x00000080L
#define SQL_CA1_LOCK_UNLOCK 0x00000100L
/* supported SQLSetPos Operations */
#define SQL_CA1_POS_POSITION 0x00000200L
#define SQL_CA1_POS_UPDATE 0x00000400L
#define SQL_CA1_POS_DELETE 0x00000800L
#define SQL_CA1_POS_REFRESH 0x00001000L
/* positioned updates and deletes */
#define SQL_CA1_POSITIONED_UPDATE 0x00002000L
#define SQL_CA1_POSITIONED_DELETE 0x00004000L
#define SQL_CA1_SELECT_FOR_UPDATE 0x00008000L
/* supported SQLBulkOperations operations */
#define SQL_CA1_BULK_ADD 0x00010000L
#define SQL_CA1_BULK_UPDATE_BY_BOOKMARK 0x00020000L
#define SQL_CA1_BULK_DELETE_BY_BOOKMARK 0x00040000L
#define SQL_CA1_BULK_FETCH_BY_BOOKMARK 0x00080000L
#endif  /* ODBCVER >= 0x0300 */
/* bitmasks for SQL_DYNAMIC_CURSOR_ATTRIBUTES2,
 * SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2, 
 * SQL_KEYSET_CURSOR_ATTRIBUTES2, and SQL_STATIC_CURSOR_ATTRIBUTES2 
 */
#if (ODBCVER >= 0x0300)
/* supported values for SQL_ATTR_SCROLL_CONCURRENCY */
#define SQL_CA2_READ_ONLY_CONCURRENCY 0x00000001L
#define SQL_CA2_LOCK_CONCURRENCY 0x00000002L
#define SQL_CA2_OPT_ROWVER_CONCURRENCY 0x00000004L
#define SQL_CA2_OPT_VALUES_CONCURRENCY 0x00000008L
/* sensitivity of the cursor to its own inserts, deletes, and updates */
#define SQL_CA2_SENSITIVITY_ADDITIONS 0x00000010L
#define SQL_CA2_SENSITIVITY_DELETIONS 0x00000020L
#define SQL_CA2_SENSITIVITY_UPDATES 0x00000040L
/* semantics of SQL_ATTR_MAX_ROWS */
#define SQL_CA2_MAX_ROWS_SELECT 0x00000080L
#define SQL_CA2_MAX_ROWS_INSERT 0x00000100L
#define SQL_CA2_MAX_ROWS_DELETE 0x00000200L
#define SQL_CA2_MAX_ROWS_UPDATE 0x00000400L
#define SQL_CA2_MAX_ROWS_CATALOG 0x00000800L
#define SQL_CA2_MAX_ROWS_AFFECTS_ALL (SQL_CA2_MAX_ROWS_SELECT | SQL_CA2_MAX_ROWS_INSERT | SQL_CA2_MAX_ROWS_DELETE | SQL_CA2_MAX_ROWS_UPDATE | SQL_CA2_MAX_ROWS_CATALOG)
/* semantics of SQL_DIAG_CURSOR_ROW_COUNT */
#define SQL_CA2_CRC_EXACT 0x00001000L
#define SQL_CA2_CRC_APPROXIMATE 0x00002000L
/* the kinds of positioned statements that can be simulated */
#define SQL_CA2_SIMULATE_NON_UNIQUE 0x00004000L
#define SQL_CA2_SIMULATE_TRY_UNIQUE 0x00008000L
#define SQL_CA2_SIMULATE_UNIQUE 0x00010000L
#endif  /* ODBCVER >= 0x0300 */
/* SQL_ODBC_API_CONFORMANCE values */
#define SQL_OAC_NONE                        0x0000
#define SQL_OAC_LEVEL1                      0x0001
#define SQL_OAC_LEVEL2                      0x0002
/* SQL_ODBC_SAG_CLI_CONFORMANCE values */
#define SQL_OSCC_NOT_COMPLIANT              0x0000
#define SQL_OSCC_COMPLIANT                  0x0001
/* SQL_ODBC_SQL_CONFORMANCE values */
#define SQL_OSC_MINIMUM                     0x0000
#define SQL_OSC_CORE                        0x0001
#define SQL_OSC_EXTENDED                    0x0002
/* SQL_CONCAT_NULL_BEHAVIOR values */
#define SQL_CB_NULL                         0x0000
#define SQL_CB_NON_NULL                     0x0001
/* SQL_SCROLL_OPTIONS masks */
#define SQL_SO_FORWARD_ONLY                 0x00000001L
#define SQL_SO_KEYSET_DRIVEN                0x00000002L
#define SQL_SO_DYNAMIC                      0x00000004L
#define SQL_SO_MIXED                        0x00000008L
#define SQL_SO_STATIC                       0x00000010L
/* SQL_FETCH_DIRECTION masks */
/* SQL_FETCH_RESUME is no longer supported */
#if (ODBCVER < 0x0300)
#define SQL_FD_FETCH_RESUME                 0x00000040L 
#endif
#define SQL_FD_FETCH_BOOKMARK               0x00000080L
/* SQL_TXN_ISOLATION_OPTION masks */
/* SQL_TXN_VERSIONING is no longer supported */
#if (ODBCVER < 0x0300)
#define SQL_TXN_VERSIONING                  0x00000010L
#endif
/* SQL_CORRELATION_NAME values */
#define SQL_CN_NONE                         0x0000
#define SQL_CN_DIFFERENT                    0x0001
#define SQL_CN_ANY                          0x0002
/* SQL_NON_NULLABLE_COLUMNS values */
#define SQL_NNC_NULL                        0x0000
#define SQL_NNC_NON_NULL                    0x0001
/* SQL_NULL_COLLATION values */
#define SQL_NC_START                        0x0002
#define SQL_NC_END                          0x0004
/* SQL_FILE_USAGE values */
#define SQL_FILE_NOT_SUPPORTED              0x0000
#define SQL_FILE_TABLE                      0x0001
#define SQL_FILE_QUALIFIER                  0x0002
#define SQL_FILE_CATALOG SQL_FILE_QUALIFIER /*ODBC 3.0*/
/* SQL_GETDATA_EXTENSIONS values */
#define SQL_GD_BLOCK                        0x00000004L
#define SQL_GD_BOUND                        0x00000008L
/* SQL_POSITIONED_STATEMENTS masks */
#define SQL_PS_POSITIONED_DELETE            0x00000001L
#define SQL_PS_POSITIONED_UPDATE            0x00000002L
#define SQL_PS_SELECT_FOR_UPDATE            0x00000004L
/* SQL_GROUP_BY values */
#define SQL_GB_NOT_SUPPORTED                0x0000
#define SQL_GB_GROUP_BY_EQUALS_SELECT       0x0001
#define SQL_GB_GROUP_BY_CONTAINS_SELECT     0x0002
#define SQL_GB_NO_RELATION                  0x0003
#if (ODBCVER >= 0x0300)
#define SQL_GB_COLLATE 0x0004
#endif  /* ODBCVER >= 0x0300 */
/* SQL_OWNER_USAGE masks */
#define SQL_OU_DML_STATEMENTS               0x00000001L
#define SQL_OU_PROCEDURE_INVOCATION         0x00000002L
#define SQL_OU_TABLE_DEFINITION             0x00000004L
#define SQL_OU_INDEX_DEFINITION             0x00000008L
#define SQL_OU_PRIVILEGE_DEFINITION         0x00000010L
/* SQL_SCHEMA_USAGE masks */
#if (ODBCVER >= 0x0300)
#define SQL_SU_DML_STATEMENTS SQL_OU_DML_STATEMENTS 
#define SQL_SU_PROCEDURE_INVOCATION SQL_OU_PROCEDURE_INVOCATION
#define SQL_SU_TABLE_DEFINITION SQL_OU_TABLE_DEFINITION
#define SQL_SU_INDEX_DEFINITION SQL_OU_INDEX_DEFINITION
#define SQL_SU_PRIVILEGE_DEFINITION SQL_OU_PRIVILEGE_DEFINITION
#endif  /* ODBCVER >= 0x0300 */
/* SQL_QUALIFIER_USAGE masks */
#define SQL_QU_DML_STATEMENTS               0x00000001L
#define SQL_QU_PROCEDURE_INVOCATION         0x00000002L
#define SQL_QU_TABLE_DEFINITION             0x00000004L
#define SQL_QU_INDEX_DEFINITION             0x00000008L
#define SQL_QU_PRIVILEGE_DEFINITION         0x00000010L
#if (ODBCVER >= 0x0300)
/* SQL_CATALOG_USAGE masks */
#define SQL_CU_DML_STATEMENTS SQL_QU_DML_STATEMENTS
#define SQL_CU_PROCEDURE_INVOCATION SQL_QU_PROCEDURE_INVOCATION 
#define SQL_CU_TABLE_DEFINITION SQL_QU_TABLE_DEFINITION
#define SQL_CU_INDEX_DEFINITION SQL_QU_INDEX_DEFINITION 
#define SQL_CU_PRIVILEGE_DEFINITION SQL_QU_PRIVILEGE_DEFINITION 
#endif  /* ODBCVER >= 0x0300 */
/* SQL_SUBQUERIES masks */
#define SQL_SQ_COMPARISON                   0x00000001L
#define SQL_SQ_EXISTS                       0x00000002L
#define SQL_SQ_IN                           0x00000004L
#define SQL_SQ_QUANTIFIED                   0x00000008L
#define SQL_SQ_CORRELATED_SUBQUERIES        0x00000010L
/* SQL_UNION masks */
#define SQL_U_UNION                         0x00000001L
#define SQL_U_UNION_ALL                     0x00000002L
/* SQL_BOOKMARK_PERSISTENCE values */
#define SQL_BP_CLOSE                        0x00000001L
#define SQL_BP_DELETE                       0x00000002L
#define SQL_BP_DROP                         0x00000004L
#define SQL_BP_TRANSACTION                  0x00000008L
#define SQL_BP_UPDATE                       0x00000010L
#define SQL_BP_OTHER_HSTMT                  0x00000020L
#define SQL_BP_SCROLL                       0x00000040L
/* SQL_STATIC_SENSITIVITY values */
#define SQL_SS_ADDITIONS                    0x00000001L
#define SQL_SS_DELETIONS                    0x00000002L
#define SQL_SS_UPDATES                      0x00000004L
/* SQL_VIEW values */
#define SQL_CV_CREATE_VIEW 0x00000001L
#define SQL_CV_CHECK_OPTION 0x00000002L
#define SQL_CV_CASCADED 0x00000004L
#define SQL_CV_LOCAL 0x00000008L
/* SQL_LOCK_TYPES masks */
#define SQL_LCK_NO_CHANGE                   0x00000001L
#define SQL_LCK_EXCLUSIVE                   0x00000002L
#define SQL_LCK_UNLOCK                      0x00000004L
/* SQL_POS_OPERATIONS masks */
#define SQL_POS_POSITION                    0x00000001L
#define SQL_POS_REFRESH                     0x00000002L
#define SQL_POS_UPDATE                      0x00000004L
#define SQL_POS_DELETE                      0x00000008L
#define SQL_POS_ADD                         0x00000010L
/* SQL_QUALIFIER_LOCATION values */
#define SQL_QL_START                        0x0001
#define SQL_QL_END                          0x0002
/* Here start return values for ODBC 3.0 SQLGetInfo */
#if (ODBCVER >= 0x0300)
/* SQL_AGGREGATE_FUNCTIONS bitmasks */
#define SQL_AF_AVG 0x00000001L
#define SQL_AF_COUNT 0x00000002L
#define SQL_AF_MAX 0x00000004L
#define SQL_AF_MIN 0x00000008L
#define SQL_AF_SUM 0x00000010L
#define SQL_AF_DISTINCT 0x00000020L
#define SQL_AF_ALL (SQL_AF_AVG | SQL_AF_COUNT | SQL_AF_MAX | SQL_AF_MIN | SQL_AF_SUM | SQL_AF_DISTINCT)
/* SQL_SQL_CONFORMANCE bit masks */
#define SQL_SC_SQL92_ENTRY 0x00000001L
#define SQL_SC_FIPS127_2_TRANSITIONAL 0x00000002L
#define SQL_SC_SQL92_INTERMEDIATE 0x00000004L
#define SQL_SC_SQL92_FULL 0x00000008L
/* SQL_DATETIME_LITERALS masks */
#define SQL_DL_SQL92_DATE 0x00000001L
#define SQL_DL_SQL92_TIME 0x00000002L
#define SQL_DL_SQL92_TIMESTAMP 0x00000004L
#define SQL_DL_SQL92_INTERVAL_YEAR 0x00000008L
#define SQL_DL_SQL92_INTERVAL_MONTH 0x00000010L
#define SQL_DL_SQL92_INTERVAL_DAY 0x00000020L
#define SQL_DL_SQL92_INTERVAL_HOUR 0x00000040L
#define SQL_DL_SQL92_INTERVAL_MINUTE 0x00000080L
#define SQL_DL_SQL92_INTERVAL_SECOND 0x00000100L
#define SQL_DL_SQL92_INTERVAL_YEAR_TO_MONTH 0x00000200L
#define SQL_DL_SQL92_INTERVAL_DAY_TO_HOUR 0x00000400L
#define SQL_DL_SQL92_INTERVAL_DAY_TO_MINUTE 0x00000800L
#define SQL_DL_SQL92_INTERVAL_DAY_TO_SECOND 0x00001000L
#define SQL_DL_SQL92_INTERVAL_HOUR_TO_MINUTE 0x00002000L
#define SQL_DL_SQL92_INTERVAL_HOUR_TO_SECOND 0x00004000L
#define SQL_DL_SQL92_INTERVAL_MINUTE_TO_SECOND 0x00008000L
/* SQL_CATALOG_LOCATION values */
#define SQL_CL_START SQL_QL_START
#define SQL_CL_END SQL_QL_END
/* values for SQL_BATCH_ROW_COUNT */
#define SQL_BRC_PROCEDURES 0x0000001
#define SQL_BRC_EXPLICIT 0x0000002
#define SQL_BRC_ROLLED_UP 0x0000004
/* bitmasks for SQL_BATCH_SUPPORT */
#define SQL_BS_SELECT_EXPLICIT 0x00000001L
#define SQL_BS_ROW_COUNT_EXPLICIT 0x00000002L
#define SQL_BS_SELECT_PROC 0x00000004L
#define SQL_BS_ROW_COUNT_PROC 0x00000008L
/* Values for SQL_PARAM_ARRAY_ROW_COUNTS getinfo */
#define SQL_PARC_BATCH 1
#define SQL_PARC_NO_BATCH 2
/* values for SQL_PARAM_ARRAY_SELECT_BATCH*/
#define SQL_PAS_BATCH 1
#define SQL_PAS_NO_BATCH 2
#define SQL_PAS_NO_SELECT 3
/* Bitmasks for SQL_INDEX_KEYWORDS */
#define SQL_IK_NONE 0x00000000L
#define SQL_IK_ASC 0x00000001L
#define SQL_IK_DESC 0x00000002L
#define SQL_IK_ALL (SQL_IK_ASC | SQL_IK_DESC)
/* Bitmasks for SQL_INFO_SCHEMA_VIEWS */
#define SQL_ISV_ASSERTIONS 0x00000001L
#define SQL_ISV_CHARACTER_SETS 0x00000002L
#define SQL_ISV_CHECK_CONSTRAINTS 0x00000004L
#define SQL_ISV_COLLATIONS 0x00000008L
#define SQL_ISV_COLUMN_DOMAIN_USAGE 0x00000010L
#define SQL_ISV_COLUMN_PRIVILEGES 0x00000020L
#define SQL_ISV_COLUMNS 0x00000040L
#define SQL_ISV_CONSTRAINT_COLUMN_USAGE 0x00000080L
#define SQL_ISV_CONSTRAINT_TABLE_USAGE 0x00000100L
#define SQL_ISV_DOMAIN_CONSTRAINTS 0x00000200L
#define SQL_ISV_DOMAINS 0x00000400L
#define SQL_ISV_KEY_COLUMN_USAGE 0x00000800L
#define SQL_ISV_REFERENTIAL_CONSTRAINTS 0x00001000L
#define SQL_ISV_SCHEMATA 0x00002000L
#define SQL_ISV_SQL_LANGUAGES 0x00004000L
#define SQL_ISV_TABLE_CONSTRAINTS 0x00008000L
#define SQL_ISV_TABLE_PRIVILEGES 0x00010000L
#define SQL_ISV_TABLES 0x00020000L
#define SQL_ISV_TRANSLATIONS 0x00040000L
#define SQL_ISV_USAGE_PRIVILEGES 0x00080000L
#define SQL_ISV_VIEW_COLUMN_USAGE 0x00100000L
#define SQL_ISV_VIEW_TABLE_USAGE 0x00200000L
#define SQL_ISV_VIEWS 0x00400000L
/* Bitmasks for SQL_ASYNC_MODE */
#define SQL_AM_NONE 0
#define SQL_AM_CONNECTION 1
#define SQL_AM_STATEMENT 2
/* Bitmasks for SQL_ALTER_DOMAIN */
#define SQL_AD_CONSTRAINT_NAME_DEFINITION 0x00000001L
#define SQL_AD_ADD_DOMAIN_CONSTRAINT   0x00000002L
#define SQL_AD_DROP_DOMAIN_CONSTRAINT   0x00000004L
#define SQL_AD_ADD_DOMAIN_DEFAULT      0x00000008L
#define SQL_AD_DROP_DOMAIN_DEFAULT      0x00000010L
#define SQL_AD_ADD_CONSTRAINT_INITIALLY_DEFERRED 0x00000020L
#define SQL_AD_ADD_CONSTRAINT_INITIALLY_IMMEDIATE 0x00000040L
#define SQL_AD_ADD_CONSTRAINT_DEFERRABLE 0x00000080L
#define SQL_AD_ADD_CONSTRAINT_NON_DEFERRABLE 0x00000100L
/* SQL_CREATE_SCHEMA bitmasks */
#define SQL_CS_CREATE_SCHEMA 0x00000001L
#define SQL_CS_AUTHORIZATION 0x00000002L
#define SQL_CS_DEFAULT_CHARACTER_SET 0x00000004L
/* SQL_CREATE_TRANSLATION bitmasks */
#define SQL_CTR_CREATE_TRANSLATION 0x00000001L
/* SQL_CREATE_ASSERTION bitmasks */
#define SQL_CA_CREATE_ASSERTION 0x00000001L
#define SQL_CA_CONSTRAINT_INITIALLY_DEFERRED 0x00000010L
#define SQL_CA_CONSTRAINT_INITIALLY_IMMEDIATE 0x00000020L
#define SQL_CA_CONSTRAINT_DEFERRABLE 0x00000040L
#define SQL_CA_CONSTRAINT_NON_DEFERRABLE 0x00000080L
/* SQL_CREATE_CHARACTER_SET bitmasks */
#define SQL_CCS_CREATE_CHARACTER_SET 0x00000001L
#define SQL_CCS_COLLATE_CLAUSE 0x00000002L
#define SQL_CCS_LIMITED_COLLATION 0x00000004L
/* SQL_CREATE_COLLATION bitmasks */
#define SQL_CCOL_CREATE_COLLATION 0x00000001L
/* SQL_CREATE_DOMAIN bitmasks */
#define SQL_CDO_CREATE_DOMAIN 0x00000001L
#define SQL_CDO_DEFAULT 0x00000002L
#define SQL_CDO_CONSTRAINT 0x00000004L
#define SQL_CDO_COLLATION 0x00000008L
#define SQL_CDO_CONSTRAINT_NAME_DEFINITION 0x00000010L
#define SQL_CDO_CONSTRAINT_INITIALLY_DEFERRED 0x00000020L
#define SQL_CDO_CONSTRAINT_INITIALLY_IMMEDIATE 0x00000040L
#define SQL_CDO_CONSTRAINT_DEFERRABLE 0x00000080L
#define SQL_CDO_CONSTRAINT_NON_DEFERRABLE 0x00000100L
/* SQL_CREATE_TABLE bitmasks */
#define SQL_CT_CREATE_TABLE 0x00000001L
#define SQL_CT_COMMIT_PRESERVE 0x00000002L
#define SQL_CT_COMMIT_DELETE 0x00000004L
#define SQL_CT_GLOBAL_TEMPORARY 0x00000008L
#define SQL_CT_LOCAL_TEMPORARY 0x00000010L
#define SQL_CT_CONSTRAINT_INITIALLY_DEFERRED 0x00000020L
#define SQL_CT_CONSTRAINT_INITIALLY_IMMEDIATE 0x00000040L
#define SQL_CT_CONSTRAINT_DEFERRABLE 0x00000080L
#define SQL_CT_CONSTRAINT_NON_DEFERRABLE 0x00000100L
#define SQL_CT_COLUMN_CONSTRAINT 0x00000200L
#define SQL_CT_COLUMN_DEFAULT 0x00000400L
#define SQL_CT_COLUMN_COLLATION 0x00000800L
#define SQL_CT_TABLE_CONSTRAINT 0x00001000L
#define SQL_CT_CONSTRAINT_NAME_DEFINITION 0x00002000L
/* SQL_DDL_INDEX bitmasks */
#define SQL_DI_CREATE_INDEX 0x00000001L
#define SQL_DI_DROP_INDEX 0x00000002L
/* SQL_DROP_COLLATION bitmasks */
#define SQL_DC_DROP_COLLATION 0x00000001L
/* SQL_DROP_DOMAIN bitmasks */
#define SQL_DD_DROP_DOMAIN 0x00000001L
#define SQL_DD_RESTRICT 0x00000002L
#define SQL_DD_CASCADE 0x00000004L
/* SQL_DROP_SCHEMA bitmasks */
#define SQL_DS_DROP_SCHEMA 0x00000001L
#define SQL_DS_RESTRICT 0x00000002L
#define SQL_DS_CASCADE 0x00000004L
/* SQL_DROP_CHARACTER_SET bitmasks */
#define SQL_DCS_DROP_CHARACTER_SET 0x00000001L
/* SQL_DROP_ASSERTION bitmasks */
#define SQL_DA_DROP_ASSERTION 0x00000001L
/* SQL_DROP_TABLE bitmasks */
#define SQL_DT_DROP_TABLE 0x00000001L
#define SQL_DT_RESTRICT 0x00000002L
#define SQL_DT_CASCADE 0x00000004L
/* SQL_DROP_TRANSLATION bitmasks */
#define SQL_DTR_DROP_TRANSLATION 0x00000001L
/* SQL_DROP_VIEW bitmasks */
#define SQL_DV_DROP_VIEW 0x00000001L
#define SQL_DV_RESTRICT 0x00000002L
#define SQL_DV_CASCADE 0x00000004L
/* SQL_INSERT_STATEMENT bitmasks */
#define SQL_IS_INSERT_LITERALS 0x00000001L
#define SQL_IS_INSERT_SEARCHED 0x00000002L
#define SQL_IS_SELECT_INTO 0x00000004L
/* SQL_ODBC_INTERFACE_CONFORMANCE values */
#define SQL_OIC_CORE 1UL
#define SQL_OIC_LEVEL1 2UL
#define SQL_OIC_LEVEL2 3UL
/* SQL_SQL92_FOREIGN_KEY_DELETE_RULE bitmasks */
#define SQL_SFKD_CASCADE 0x00000001L
#define SQL_SFKD_NO_ACTION 0x00000002L
#define SQL_SFKD_SET_DEFAULT 0x00000004L
#define SQL_SFKD_SET_NULL 0x00000008L
/* SQL_SQL92_FOREIGN_KEY_UPDATE_RULE bitmasks */
#define SQL_SFKU_CASCADE 0x00000001L
#define SQL_SFKU_NO_ACTION 0x00000002L
#define SQL_SFKU_SET_DEFAULT 0x00000004L
#define SQL_SFKU_SET_NULL 0x00000008L
/* SQL_SQL92_GRANT bitmasks */
#define SQL_SG_USAGE_ON_DOMAIN 0x00000001L
#define SQL_SG_USAGE_ON_CHARACTER_SET 0x00000002L
#define SQL_SG_USAGE_ON_COLLATION 0x00000004L
#define SQL_SG_USAGE_ON_TRANSLATION 0x00000008L
#define SQL_SG_WITH_GRANT_OPTION 0x00000010L
#define SQL_SG_DELETE_TABLE 0x00000020L
#define SQL_SG_INSERT_TABLE 0x00000040L
#define SQL_SG_INSERT_COLUMN 0x00000080L
#define SQL_SG_REFERENCES_TABLE 0x00000100L
#define SQL_SG_REFERENCES_COLUMN 0x00000200L
#define SQL_SG_SELECT_TABLE 0x00000400L
#define SQL_SG_UPDATE_TABLE 0x00000800L
#define SQL_SG_UPDATE_COLUMN 0x00001000L
/* SQL_SQL92_PREDICATES bitmasks */
#define SQL_SP_EXISTS 0x00000001L
#define SQL_SP_ISNOTNULL 0x00000002L
#define SQL_SP_ISNULL 0x00000004L
#define SQL_SP_MATCH_FULL 0x00000008L
#define SQL_SP_MATCH_PARTIAL 0x00000010L
#define SQL_SP_MATCH_UNIQUE_FULL 0x00000020L
#define SQL_SP_MATCH_UNIQUE_PARTIAL 0x00000040L
#define SQL_SP_OVERLAPS 0x00000080L
#define SQL_SP_UNIQUE 0x00000100L
#define SQL_SP_LIKE 0x00000200L
#define SQL_SP_IN 0x00000400L
#define SQL_SP_BETWEEN 0x00000800L
#define SQL_SP_COMPARISON 0x00001000L
#define SQL_SP_QUANTIFIED_COMPARISON 0x00002000L
/* SQL_SQL92_RELATIONAL_JOIN_OPERATORS bitmasks */
#define SQL_SRJO_CORRESPONDING_CLAUSE 0x00000001L
#define SQL_SRJO_CROSS_JOIN 0x00000002L
#define SQL_SRJO_EXCEPT_JOIN 0x00000004L
#define SQL_SRJO_FULL_OUTER_JOIN 0x00000008L
#define SQL_SRJO_INNER_JOIN 0x00000010L
#define SQL_SRJO_INTERSECT_JOIN 0x00000020L
#define SQL_SRJO_LEFT_OUTER_JOIN 0x00000040L
#define SQL_SRJO_NATURAL_JOIN 0x00000080L
#define SQL_SRJO_RIGHT_OUTER_JOIN 0x00000100L
#define SQL_SRJO_UNION_JOIN 0x00000200L
/* SQL_SQL92_REVOKE bitmasks */
#define SQL_SR_USAGE_ON_DOMAIN 0x00000001L
#define SQL_SR_USAGE_ON_CHARACTER_SET 0x00000002L
#define SQL_SR_USAGE_ON_COLLATION 0x00000004L
#define SQL_SR_USAGE_ON_TRANSLATION 0x00000008L
#define SQL_SR_GRANT_OPTION_FOR 0x00000010L
#define SQL_SR_CASCADE 0x00000020L
#define SQL_SR_RESTRICT 0x00000040L
#define SQL_SR_DELETE_TABLE 0x00000080L
#define SQL_SR_INSERT_TABLE 0x00000100L
#define SQL_SR_INSERT_COLUMN 0x00000200L
#define SQL_SR_REFERENCES_TABLE 0x00000400L
#define SQL_SR_REFERENCES_COLUMN 0x00000800L
#define SQL_SR_SELECT_TABLE 0x00001000L
#define SQL_SR_UPDATE_TABLE 0x00002000L
#define SQL_SR_UPDATE_COLUMN 0x00004000L
/* SQL_SQL92_ROW_VALUE_CONSTRUCTOR bitmasks */
#define SQL_SRVC_VALUE_EXPRESSION 0x00000001L
#define SQL_SRVC_NULL 0x00000002L
#define SQL_SRVC_DEFAULT 0x00000004L
#define SQL_SRVC_ROW_SUBQUERY 0x00000008L
/* SQL_SQL92_VALUE_EXPRESSIONS bitmasks */
#define SQL_SVE_CASE 0x00000001L
#define SQL_SVE_CAST 0x00000002L
#define SQL_SVE_COALESCE 0x00000004L
#define SQL_SVE_NULLIF 0x00000008L
/* SQL_STANDARD_CLI_CONFORMANCE bitmasks */
#define SQL_SCC_XOPEN_CLI_VERSION1 0x00000001L
#define SQL_SCC_ISO92_CLI 0x00000002L
/* SQL_UNION_STATEMENT bitmasks */
#define SQL_US_UNION SQL_U_UNION
#define SQL_US_UNION_ALL SQL_U_UNION_ALL
#endif  /* ODBCVER >= 0x0300 */
/* additional SQLDataSources fetch directions */
#if (ODBCVER >= 0x0300)
#define SQL_FETCH_FIRST_USER 31
#define SQL_FETCH_FIRST_SYSTEM 32
#endif  /* ODBCVER >= 0x0300 */
/* Defines for SQLSetPos */
#define SQL_ENTIRE_ROWSET            0
/* Operations in SQLSetPos */
#define SQL_POSITION                 0               /*      1.0 FALSE */
#define SQL_REFRESH                  1               /*      1.0 TRUE */
#define SQL_UPDATE                   2
#define SQL_DELETE                   3
/* Operations in SQLBulkOperations */
#define SQL_ADD                      4
#define SQL_SETPOS_MAX_OPTION_VALUE SQL_ADD
#if (ODBCVER >= 0x0300)
#define SQL_UPDATE_BY_BOOKMARK  5
#define SQL_DELETE_BY_BOOKMARK  6
#define SQL_FETCH_BY_BOOKMARK  7
#endif /*  ODBCVER >= 0x0300 */
/* Lock options in SQLSetPos */
#define SQL_LOCK_NO_CHANGE           0               /*      1.0 FALSE */
#define SQL_LOCK_EXCLUSIVE           1               /*      1.0 TRUE */
#define SQL_LOCK_UNLOCK              2
#define SQL_SETPOS_MAX_LOCK_VALUE SQL_LOCK_UNLOCK
/* Macros for SQLSetPos */
#define SQL_POSITION_TO(hstmt,irow) SQLSetPos(hstmt,irow,SQL_POSITION,SQL_LOCK_NO_CHANGE)
#define SQL_LOCK_RECORD(hstmt,irow,fLock) SQLSetPos(hstmt,irow,SQL_POSITION,fLock)
#define SQL_REFRESH_RECORD(hstmt,irow,fLock) SQLSetPos(hstmt,irow,SQL_REFRESH,fLock)
#define SQL_UPDATE_RECORD(hstmt,irow) SQLSetPos(hstmt,irow,SQL_UPDATE,SQL_LOCK_NO_CHANGE)
#define SQL_DELETE_RECORD(hstmt,irow) SQLSetPos(hstmt,irow,SQL_DELETE,SQL_LOCK_NO_CHANGE)
#define SQL_ADD_RECORD(hstmt,irow) SQLSetPos(hstmt,irow,SQL_ADD,SQL_LOCK_NO_CHANGE)
/* Column types and scopes in SQLSpecialColumns.  */
#define SQL_BEST_ROWID                  1
#define SQL_ROWVER                      2
/* Defines for SQLSpecialColumns (returned in the result set) 
   SQL_PC_UNKNOWN and SQL_PC_PSEUDO are defined in sql.h */
#define SQL_PC_NOT_PSEUDO               1
/* Defines for SQLStatistics */
#define SQL_QUICK                       0
#define SQL_ENSURE                      1
/* Defines for SQLStatistics (returned in the result set) 
   SQL_INDEX_CLUSTERED, SQL_INDEX_HASHED, and SQL_INDEX_OTHER are
   defined in sql.h */
#define SQL_TABLE_STAT                  0
/* Defines for SQLTables */
#if (ODBCVER >= 0x0300)
#define SQL_ALL_CATALOGS "%"
#define SQL_ALL_SCHEMAS "%"
#define SQL_ALL_TABLE_TYPES "%"
#endif  /* ODBCVER >= 0x0300 */
/* Options for SQLDriverConnect */
#define SQL_DRIVER_NOPROMPT             0
#define SQL_DRIVER_COMPLETE             1
#define SQL_DRIVER_PROMPT               2
#define SQL_DRIVER_COMPLETE_REQUIRED    3
#ifndef RC_INVOKED
SQLRETURN SQL_API SQLDriverConnect(
    SQLHDBC            hdbc,
    SQLHWND            hwnd,
    SQLCHAR    *szConnStrIn,
    SQLSMALLINT        cbConnStrIn,
    SQLCHAR           *szConnStrOut,
    SQLSMALLINT        cbConnStrOutMax,
    SQLSMALLINT    *pcbConnStrOut,
    SQLUSMALLINT       fDriverCompletion);
#endif /* RC_INVOKED */
/* Level 2 Functions                             */
/* SQLExtendedFetch "fFetchType" values */
#define SQL_FETCH_BOOKMARK               8
/* SQLExtendedFetch "rgfRowStatus" element values */
#define SQL_ROW_SUCCESS                  0
#define SQL_ROW_DELETED                  1
#define SQL_ROW_UPDATED                  2
#define SQL_ROW_NOROW                    3
#define SQL_ROW_ADDED                    4
#define SQL_ROW_ERROR                    5
#if (ODBCVER >= 0x0300)
#define SQL_ROW_SUCCESS_WITH_INFO  6
#define SQL_ROW_PROCEED  0
#define SQL_ROW_IGNORE  1
#endif
/* value for SQL_DESC_ARRAY_STATUS_PTR */
#if (ODBCVER >= 0x0300)
#define SQL_PARAM_SUCCESS 0
#define SQL_PARAM_SUCCESS_WITH_INFO 6
#define SQL_PARAM_ERROR 5
#define SQL_PARAM_UNUSED 7
#define SQL_PARAM_DIAG_UNAVAILABLE 1
#define SQL_PARAM_PROCEED 0
#define SQL_PARAM_IGNORE 1
#endif  /* ODBCVER >= 0x0300 */
/* Defines for SQLForeignKeys (returned in result set) */
#define SQL_CASCADE                      0
#define SQL_RESTRICT                     1
#define SQL_SET_NULL                     2
#if (ODBCVER >= 0x0250)
#define SQL_NO_ACTION  3
#define SQL_SET_DEFAULT  4
#endif  /* ODBCVER >= 0x0250 */
#if (ODBCVER >= 0x0300)
#define SQL_INITIALLY_DEFERRED 5
#define SQL_INITIALLY_IMMEDIATE 6
#endif  /* ODBCVER >= 0x0300 */
/* Defines for SQLBindParameter and
                           SQLProcedureColumns (returned in the result set) */
#define SQL_PARAM_TYPE_UNKNOWN           0
#define SQL_PARAM_INPUT                  1
#define SQL_PARAM_INPUT_OUTPUT           2
#define SQL_RESULT_COL                   3
#define SQL_PARAM_OUTPUT                 4
#define SQL_RETURN_VALUE                 5
/* Defines for SQLProcedures (returned in the result set) */
#define SQL_PT_UNKNOWN                   0
#define SQL_PT_PROCEDURE                 1
#define SQL_PT_FUNCTION                  2
#ifndef RC_INVOKED
/*      This define is too large for RC */
#define SQL_ODBC_KEYWORDS "ABSOLUTE,ACTION,ADA,ADD,ALL,ALLOCATE,ALTER,AND,ANY,ARE,AS," "ASC,ASSERTION,AT,AUTHORIZATION,AVG," "BEGIN,BETWEEN,BIT,BIT_LENGTH,BOTH,BY,CASCADE,CASCADED,CASE,CAST,CATALOG," "CHAR,CHAR_LENGTH,CHARACTER,CHARACTER_LENGTH,CHECK,CLOSE,COALESCE," "COLLATE,COLLATION,COLUMN,COMMIT,CONNECT,CONNECTION,CONSTRAINT," "CONSTRAINTS,CONTINUE,CONVERT,CORRESPONDING,COUNT,CREATE,CROSS,CURRENT," "CURRENT_DATE,CURRENT_TIME,CURRENT_TIMESTAMP,CURRENT_USER,CURSOR," "DATE,DAY,DEALLOCATE,DEC,DECIMAL,DECLARE,DEFAULT,DEFERRABLE," "DEFERRED,DELETE,DESC,DESCRIBE,DESCRIPTOR,DIAGNOSTICS,DISCONNECT," "DISTINCT,DOMAIN,DOUBLE,DROP," "ELSE,END,END-EXEC,ESCAPE,EXCEPT,EXCEPTION,EXEC,EXECUTE," "EXISTS,EXTERNAL,EXTRACT," "FALSE,FETCH,FIRST,FLOAT,FOR,FOREIGN,FORTRAN,FOUND,FROM,FULL," "GET,GLOBAL,GO,GOTO,GRANT,GROUP,HAVING,HOUR," "IDENTITY,IMMEDIATE,IN,INCLUDE,INDEX,INDICATOR,INITIALLY,INNER," "INPUT,INSENSITIVE,INSERT,INT,INTEGER,INTERSECT,INTERVAL,INTO,IS,ISOLATION," "JOIN,KEY,LANGUAGE,LAST,LEADING,LEFT,LEVEL,LIKE,LOCAL,LOWER," "MATCH,MAX,MIN,MINUTE,MODULE,MONTH," "NAMES,NATIONAL,NATURAL,NCHAR,NEXT,NO,NONE,NOT,NULL,NULLIF,NUMERIC," "OCTET_LENGTH,OF,ON,ONLY,OPEN,OPTION,OR,ORDER,OUTER,OUTPUT,OVERLAPS," "PAD,PARTIAL,PASCAL,PLI,POSITION,PRECISION,PREPARE,PRESERVE," "PRIMARY,PRIOR,PRIVILEGES,PROCEDURE,PUBLIC," "READ,REAL,REFERENCES,RELATIVE,RESTRICT,REVOKE,RIGHT,ROLLBACK,ROWS" "SCHEMA,SCROLL,SECOND,SECTION,SELECT,SESSION,SESSION_USER,SET,SIZE," "SMALLINT,SOME,SPACE,SQL,SQLCA,SQLCODE,SQLERROR,SQLSTATE,SQLWARNING," "SUBSTRING,SUM,SYSTEM_USER," "TABLE,TEMPORARY,THEN,TIME,TIMESTAMP,TIMEZONE_HOUR,TIMEZONE_MINUTE," "TO,TRAILING,TRANSACTION,TRANSLATE,TRANSLATION,TRIM,TRUE," "UNION,UNIQUE,UNKNOWN,UPDATE,UPPER,USAGE,USER,USING," "VALUE,VALUES,VARCHAR,VARYING,VIEW,WHEN,WHENEVER,WHERE,WITH,WORK,WRITE," "YEAR,ZONE"
SQLRETURN SQL_API SQLBrowseConnect(
    SQLHDBC            hdbc,
    SQLCHAR    *szConnStrIn,
    SQLSMALLINT        cbConnStrIn,
    SQLCHAR    *szConnStrOut,
    SQLSMALLINT        cbConnStrOutMax,
    SQLSMALLINT       *pcbConnStrOut);
#if (ODBCVER >= 0x0300)
SQLRETURN SQL_API SQLBulkOperations(
SQLHSTMT StatementHandle,
SQLSMALLINT Operation);
#endif  /* ODBCVER >= 0x0300 */
SQLRETURN SQL_API SQLColAttributes(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       icol,
    SQLUSMALLINT       fDescType,
    SQLPOINTER         rgbDesc,
    SQLSMALLINT        cbDescMax,
    SQLSMALLINT    *pcbDesc,
    SQLINTEGER    *pfDesc);
SQLRETURN SQL_API SQLColumnPrivileges(
    SQLHSTMT           hstmt,
    SQLCHAR    *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR    *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR    *szTableName,
    SQLSMALLINT        cbTableName,
    SQLCHAR    *szColumnName,
    SQLSMALLINT        cbColumnName);
SQLRETURN SQL_API SQLDescribeParam(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       ipar,
    SQLSMALLINT    *pfSqlType,
    SQLUINTEGER    *pcbParamDef,
    SQLSMALLINT    *pibScale,
    SQLSMALLINT    *pfNullable);
SQLRETURN SQL_API SQLExtendedFetch(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fFetchType,
    SQLINTEGER         irow,
    SQLUINTEGER    *pcrow,
    SQLUSMALLINT    *rgfRowStatus);
SQLRETURN SQL_API SQLForeignKeys(
    SQLHSTMT           hstmt,
    SQLCHAR    *szPkCatalogName,
    SQLSMALLINT        cbPkCatalogName,
    SQLCHAR    *szPkSchemaName,
    SQLSMALLINT        cbPkSchemaName,
    SQLCHAR    *szPkTableName,
    SQLSMALLINT        cbPkTableName,
    SQLCHAR    *szFkCatalogName,
    SQLSMALLINT        cbFkCatalogName,
    SQLCHAR    *szFkSchemaName,
    SQLSMALLINT        cbFkSchemaName,
    SQLCHAR    *szFkTableName,
    SQLSMALLINT        cbFkTableName);
SQLRETURN SQL_API SQLMoreResults(
    SQLHSTMT           hstmt);
SQLRETURN SQL_API SQLNativeSql(
    SQLHDBC            hdbc,
    SQLCHAR    *szSqlStrIn,
    SQLINTEGER         cbSqlStrIn,
    SQLCHAR    *szSqlStr,
    SQLINTEGER         cbSqlStrMax,
    SQLINTEGER    *pcbSqlStr);
SQLRETURN SQL_API SQLNumParams(
    SQLHSTMT           hstmt,
    SQLSMALLINT    *pcpar);
SQLRETURN SQL_API SQLParamOptions(
    SQLHSTMT           hstmt,
    SQLUINTEGER        crow,
    SQLUINTEGER    *pirow);
SQLRETURN SQL_API SQLPrimaryKeys(
    SQLHSTMT           hstmt,
    SQLCHAR    *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR    *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR    *szTableName,
    SQLSMALLINT        cbTableName);
SQLRETURN SQL_API SQLProcedureColumns(
    SQLHSTMT           hstmt,
    SQLCHAR    *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR    *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR    *szProcName,
    SQLSMALLINT        cbProcName,
    SQLCHAR    *szColumnName,
    SQLSMALLINT        cbColumnName);
SQLRETURN SQL_API SQLProcedures(
    SQLHSTMT           hstmt,
    SQLCHAR    *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR    *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR    *szProcName,
    SQLSMALLINT        cbProcName);
SQLRETURN SQL_API SQLSetPos(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       irow,
    SQLUSMALLINT       fOption,
    SQLUSMALLINT       fLock);
SQLRETURN SQL_API SQLTablePrivileges(
    SQLHSTMT           hstmt,
    SQLCHAR    *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR    *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR    *szTableName,
    SQLSMALLINT        cbTableName);
SQLRETURN SQL_API SQLDrivers(
    SQLHENV            henv,
    SQLUSMALLINT       fDirection,
    SQLCHAR    *szDriverDesc,
    SQLSMALLINT        cbDriverDescMax,
    SQLSMALLINT    *pcbDriverDesc,
    SQLCHAR    *szDriverAttributes,
    SQLSMALLINT        cbDrvrAttrMax,
    SQLSMALLINT    *pcbDrvrAttr);
SQLRETURN SQL_API SQLBindParameter(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       ipar,
    SQLSMALLINT        fParamType,
    SQLSMALLINT        fCType,
    SQLSMALLINT        fSqlType,
    SQLUINTEGER        cbColDef,
    SQLSMALLINT        ibScale,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValueMax,
    SQLINTEGER    *pcbValue);
#endif /* RC_INVOKED */
/*---------------------------------------------------------*/
/* SQLAllocHandleStd is implemented to make SQLAllocHandle */
/* compatible with X/Open standard.  an application should */
/* not call SQLAllocHandleStd directly    */ 
/*---------------------------------------------------------*/
#ifdef ODBC_STD
#define SQLAllocHandle  SQLAllocHandleStd
#define SQLAllocEnv(phenv)  SQLAllocHandleStd(SQL_HANDLE_ENV, SQL_NULL_HANDLE, phenv)
/* Internal type subcodes */
#define SQL_YEAR SQL_CODE_YEAR
#define SQL_MONTH SQL_CODE_MONTH
#define SQL_DAY SQL_CODE_DAY
#define SQL_HOUR SQL_CODE_HOUR
#define SQL_MINUTE SQL_CODE_MINUTE
#define SQL_SECOND SQL_CODE_SECOND
#define SQL_YEAR_TO_MONTH SQL_CODE_YEAR_TO_MONTH
#define SQL_DAY_TO_HOUR SQL_CODE_DAY_TO_HOUR
#define SQL_DAY_TO_MINUTE SQL_CODE_DAY_TO_MINUTE
#define SQL_DAY_TO_SECOND SQL_CODE_DAY_TO_SECOND
#define SQL_HOUR_TO_MINUTE SQL_CODE_HOUR_TO_MINUTE
#define SQL_HOUR_TO_SECOND SQL_CODE_HOUR_TO_SECOND
#define SQL_MINUTE_TO_SECOND SQL_CODE_MINUTE_TO_SECOND
#endif /* ODBC_STD */
#if (ODBCVER >= 0x0300)
#ifndef RC_INVOKED
SQLRETURN SQL_API SQLAllocHandleStd(
SQLSMALLINT fHandleType,
SQLHANDLE hInput,
SQLHANDLE    *phOutput);
#endif /* RC_INVOKED */
#endif
/*      Deprecated defines from prior versions of ODBC */
#define SQL_DATABASE_NAME               16    /* Use SQLGetConnectOption/SQL_CURRENT_QUALIFIER */
#define SQL_FD_FETCH_PREV               SQL_FD_FETCH_PRIOR
#define SQL_FETCH_PREV                  SQL_FETCH_PRIOR
#define SQL_CONCUR_TIMESTAMP            SQL_CONCUR_ROWVER
#define SQL_SCCO_OPT_TIMESTAMP          SQL_SCCO_OPT_ROWVER
#define SQL_CC_DELETE                   SQL_CB_DELETE
#define SQL_CR_DELETE                   SQL_CB_DELETE
#define SQL_CC_CLOSE                    SQL_CB_CLOSE
#define SQL_CR_CLOSE                    SQL_CB_CLOSE
#define SQL_CC_PRESERVE                 SQL_CB_PRESERVE
#define SQL_CR_PRESERVE                 SQL_CB_PRESERVE
/* SQL_FETCH_RESUME is not supported by 2.0+ drivers  */
#if (ODBCVER < 0x0300)
#define SQL_FETCH_RESUME                7    
#endif
#define SQL_SCROLL_FORWARD_ONLY         0L    /*-SQL_CURSOR_FORWARD_ONLY */
#define SQL_SCROLL_KEYSET_DRIVEN        (-1L) /*-SQL_CURSOR_KEYSET_DRIVEN */
#define SQL_SCROLL_DYNAMIC              (-2L) /*-SQL_CURSOR_DYNAMIC */
#define SQL_SCROLL_STATIC               (-3L) /*-SQL_CURSOR_STATIC */
/*      Deprecated functions from prior versions of ODBC */
#ifndef RC_INVOKED
SQLRETURN SQL_API SQLSetScrollOptions(    /*      Use SQLSetStmtOptions */
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fConcurrency,
    SQLINTEGER         crowKeyset,
    SQLUSMALLINT       crowRowset);
#endif /* RC_INVOKED */
#ifdef __cplusplus
}                                     /* End of extern "C" { */
#endif  /* __cplusplus */
#if defined(WIN32) 
#include "sqlucode.h"
#endif
/* Tracing section*/
#define TRACE_VERSION 1000 /* Version of trace API*/
RETCODE SQL_API TraceOpenLogFile(LPWSTR,LPWSTR,DWORD);/* open a trace log file*/
RETCODE SQL_API TraceCloseLogFile(); /* Request to close a trace log*/
VOID SQL_API TraceReturn(RETCODE,RETCODE); /* Processes trace after FN is called*/
DWORD SQL_API TraceVersion(); /* Returns trace API version*/
#endif /* __INFXSQL */

