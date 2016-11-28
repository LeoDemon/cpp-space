/*
 * =====================================================================================
 *
 *       Filename:  test_qt_exp.h
 *
 *    Description:  the head file for test_qt_exp.cpp
 *
 *        Version:  1.0
 *        Created:  2014/3/10 16:03:30
 *       Revision:  none
 *       Compiler:  qtmake
 *
 *         Author:  LeoDemon
 *   Organization:  LD
 *
 * =====================================================================================
 */

#ifndef TEST_QT_EXP_H_
#define TEST_QT_EXP_H_

#include <QtGui>

class ExtensionDlg:public QDialog
{
    Q_OBJECT

 public:
    ExtensionDlg();
    void initBasicInfo();
    void initDetailInfo();

    public slots:
        void slot2Extension();

 private:
        QWidget *baseWidget;
        QWidget *detailWidget;
};

#endif//TEST_QT_EXP_H_
