/*
 * =====================================================================================
 *
 *       Filename:  test_qt_exp.cpp
 *
 *    Description:  study examples for Qt
 *
 *        Version:  1.0
 *        Created:  2014/3/10 17:08:30
 *       Revision:  none
 *       Compiler:  qtmake
 *
 *         Author:  LeoDemon
 *   Organization:  LD
 *
 * =====================================================================================
 */

#include "test_qt_exp.h"

ExtensionDlg::ExtensionDlg()
{
    setWindowTitle(tr("INFO DIALOG"));
    initBasicInfo();
    initDetailInfo();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(baseWidget);
    layout->addWidget(detailWidget);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(6);
    setLayout(layout);
}

void ExtensionDlg::initBasicInfo()
{
    baseWidget = new QWidget;
    QLabel *nameLabel = new QLabel(tr("name"));
    QLineEdit *nameEdit = new QLineEdit;
    QLabel *sexLabel = new QLabel(tr("sex"));
    QComboBox *sexComboBox = new QComboBox;
    sexComboBox->addItem(tr("male"));
    sexComboBox->addItem(tr("female"));
    QPushButton *okButton = new QPushButton(tr("OK"));
    QPushButton *detailButton = new QPushButton(tr("More"));
    connect(detailButton, SIGNAL(clicked()), this, SLOT(slot2Extension()));
    QDialogButtonBox *btnBox = new QDialogButtonBox(Qt::Horizontal);
    btnBox->addButton(okButton, QDialogButtonBox::ActionRole);
    btnBox->addButton(detailButton, QDialogButtonBox::ActionRole);
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(nameLabel, nameEdit);
    formLayout->addRow(sexLabel, sexComboBox);
    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addLayout(formLayout);
    vboxLayout->addWidget(btnBox);
    baseWidget->setLayout(vboxLayout);
}

void ExtensionDlg::initDetailInfo()
{
    detailWidget = new QWidget;
    QLabel *ageLabel = new QLabel(tr("Age"));
    QLineEdit *ageEdit = new QLineEdit;
    ageEdit->setText("26");
    QLabel *deptLabel = new QLabel(tr("Department"));
    QComboBox *deptComboBox = new QComboBox;
    deptComboBox->addItem(tr("department 1"));
    deptComboBox->addItem(tr("department 2"));
    deptComboBox->addItem(tr("department 3"));
    QLabel *addressLabel = new QLabel(tr("address"));
    QLineEdit *addressEdit = new QLineEdit;
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(ageLabel, ageEdit);
    formLayout->addRow(deptLabel, deptComboBox);
    formLayout->addRow(addressLabel, addressEdit);
    detailWidget->setLayout(formLayout);
    detailWidget->hide();
}

void ExtensionDlg::slot2Extension()
{
    if(detailWidget->isHidden())
    {
        detailWidget->show();
    }
    else
    {
        detailWidget->hide();
    }   
}

