/*
 * =====================================================================================
 *
 *       Filename:  test_qt_tmp001.cpp
 *
 *    Description:  main()
 *
 *        Version:  1.0
 *        Created:  2014/2/25 17:51:30
 *       Revision:  none
 *       Compiler:  qtmake
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
//    QLabel hello("<center><h2><i>Hello</i>"
//            "<font color=red> QT!</font></h2></center>", 0);
//    QPushButton hello("click and Quit", 0);
//    QObject::connect(&hello, SIGNAL(clicked()), &app, SLOT(quit()));
//    hello.resize(300, 120);
//    hello.show();

	QWidget *window = new QWidget;
	window->setWindowTitle("Enter Your Age");
	QSpinBox *spinBox = new QSpinBox;
	QSlider *slider = new QSlider(Qt::Horizontal);
	spinBox->setRange(0,130);
	slider->setRange(0,130);
	QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
	QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
	spinBox->setValue(26);
	//QHBoxLayout *layout = new QHBoxLayout;
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(spinBox);
	layout->addWidget(slider);
	window->setLayout(layout);
	window->show();

	return app.exec();
}

