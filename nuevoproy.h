#ifndef NUEVOPROY_H
#define NUEVOPROY_H

#include <QDialog>

namespace Ui {
class NuevoProy;
}

class NuevoProy : public QDialog
{
    Q_OBJECT

public:
    explicit NuevoProy(QWidget *parent = nullptr);
    ~NuevoProy();

private:
    Ui::NuevoProy *ui;
};

#endif // NUEVOPROY_H
