#include "programinfo.h"
#include "ui_programinfo.h"

ProgramInfo::ProgramInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgramInfo)
{
    ui->setupUi(this);
}

ProgramInfo::~ProgramInfo()
{
    delete ui;
}
