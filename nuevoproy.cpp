#include "nuevoproy.h"
#include "ui_nuevoproy.h"

NuevoProy::NuevoProy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevoProy)
{
    ui->setupUi(this);
}

NuevoProy::~NuevoProy()
{
    delete ui;
}
