#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <qcustomplot.h>

#include <QMainWindow>

extern "C" {
#include "../core/core.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  void connections();
  bool get_xval(double *);

 private slots:
  void inputs();
  void clean_entry();
  void clean_all();
  void eval();

 signals:
  void sendFunc(const QString &text);
};
#endif  // MAINWINDOW_H
