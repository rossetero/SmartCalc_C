#include "plotwindow.h"

#include <QtDebug>

#include "ui_plotwindow.h"

plotwindow::plotwindow(QWidget* parent, const QString func)
    : QWidget(parent), ui(new Ui::plotwindow) {
  ui->setupUi(this);
  connect(ui->Button_replot, SIGNAL(clicked()), this, SLOT(makeplot()));
  ui->funclabel->setText("f(x)=" + func);
  makeplot();
}

plotwindow::~plotwindow() { delete ui; }

void plotwindow::makeplot() {
  QDoubleValidator* validator = new QDoubleValidator();
  QDoubleValidator* stepvalidator = new QDoubleValidator();
  stepvalidator->setBottom(0);
  ui->x_minus->setValidator(validator);
  ui->x_plus->setValidator(validator);
  ui->y_minus->setValidator(validator);
  ui->y_minus->setValidator(validator);
  ui->stepEdit->setValidator(stepvalidator);
  double xm = ui->x_minus->text().toDouble();
  double xp = ui->x_plus->text().toDouble();
  double ym = ui->y_minus->text().toDouble();
  double yp = ui->y_plus->text().toDouble();
  double step = ui->stepEdit->text().toDouble();
  ui->plot->xAxis->setRange(xm, xp);
  ui->plot->yAxis->setRange(ym, yp);
  QVector<double> vecx, vecy;
  QString tmp = ui->funclabel->text().mid(5);
  QByteArray ba = tmp.toLocal8Bit();
  char* inp = ba.data();
  double y = 0;
  while (xm <= xp) {
    xm += step;
    if (evaluate(inp, xm, &y)) {
      vecy.push_back(qQNaN());
    } else {
      vecy.push_back(y);
    }
    vecx.push_back(xm);
    xm += step;
  }
  ui->plot->addGraph();
  ui->plot->graph(0)->setData(vecx, vecy);
  ui->plot->xAxis->setLabel("x");
  ui->plot->yAxis->setLabel("y");
  ui->plot->replot();
}
