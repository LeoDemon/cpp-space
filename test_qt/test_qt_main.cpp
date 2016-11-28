/*
 * =====================================================================================
 *
 *       Filename:  test_qt_main.cpp
 *
 *    Description:  main()
 *
 *        Version:  1.0
 *        Created:  2014/3/10 15:20:30
 *       Revision:  none
 *       Compiler:  qtmake
 *
 *         Author:  LeoDemon
 *   Organization:  LD
 *
 * =====================================================================================
 */

#include <QApplication>
#include "test_qt_exp.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	ExtensionDlg extdlg;
	extdlg.show();
	return app.exec();
}

