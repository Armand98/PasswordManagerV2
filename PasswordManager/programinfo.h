#ifndef PROGRAMINFO_H
#define PROGRAMINFO_H

#include <QDialog>

namespace Ui {
class ProgramInfo;
}

class ProgramInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ProgramInfo(QWidget *parent = nullptr);
    ~ProgramInfo();

private:
    Ui::ProgramInfo *ui;
};

#endif // PROGRAMINFO_H
