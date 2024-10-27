#include "mainwindow.h"

#include "plotwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->XValField->setValidator(new QDoubleValidator);
  connections();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::inputs() {
  QPushButton *button = (QPushButton *)sender();
  QString tmp = ui->EnterField->text() + button->text();
  if (button->text().length() > 1 && button->text() != "mod") tmp += "(";
  ui->EnterField->setText(tmp);
}

void MainWindow::clean_all() {
  ui->EnterField->setText("");
  ui->EnterField->setPlaceholderText("Enter expression");
  ui->XValField->setText("0");
}

void MainWindow::clean_entry() {
  QString tmp = ui->EnterField->text();
  tmp.chop(1);
  ui->EnterField->setText(tmp);
  if (ui->EnterField->text().length() == 0) {
    ui->EnterField->setPlaceholderText("Enter expression");
    ui->XValField->setText("0");
  }
}

bool MainWindow::get_xval(double *x) {
  bool status = true;
  if (ui->XValField->hasAcceptableInput()) {
    *x = ui->XValField->text().toDouble();
  } else {
    status = false;
  }
  return status;
}

void MainWindow::eval() {
  QPushButton *button = (QPushButton *)sender();
  double x = 0;
  if (get_xval(&x)) {
    double result = 0;
    QByteArray ba = ui->EnterField->text().toLocal8Bit();
    char *inp = ba.data();
    int status = evaluate(inp, x, &result);
    switch (status) {
      case OK:
        if (button->objectName() == "Button_eq") {
          ui->EnterField->setText(QString::number(result, 'g', 10));
        } else {
          plotwindow *plotw = new plotwindow(nullptr, ui->EnterField->text());
          plotw->show();
        }
        break;
      case INVALID_SINTAX:
        ui->EnterField->setText("");
        ui->EnterField->setPlaceholderText("INVALID_SYNTAX");
        break;
      case CALCULATION_ERROR:
        if (button->objectName() == "Button_eq") {
          ui->EnterField->setText("");
          ui->EnterField->setPlaceholderText("CALCULATION_ERROR");
        } else {
          plotwindow *plotw = new plotwindow(nullptr, ui->EnterField->text());
          plotw->show();
        }
        break;
    }
  } else {
    ui->EnterField->setText("");
    ui->EnterField->setPlaceholderText("INVALID_X");
  }
}

void MainWindow::connections() {
  connect(ui->Button_plot, SIGNAL(clicked()), this, SLOT(eval()));
  connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_plus, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_sub, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_mul, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_div, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_dot, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_AC, SIGNAL(clicked()), this, SLOT(clean_all()));
  connect(ui->Button_CE, SIGNAL(clicked()), this, SLOT(clean_entry()));
  connect(ui->Button_eq, SIGNAL(clicked()), this, SLOT(eval()));
  connect(ui->Button_lb, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_rb, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_mod, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_pow, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_sin, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_cos, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_tan, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_acos, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_asin, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_atan, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_sqrt, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_ln, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_log, SIGNAL(clicked()), this, SLOT(inputs()));
  connect(ui->Button_x, SIGNAL(clicked()), this, SLOT(inputs()));
}
