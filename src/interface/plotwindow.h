#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QWidget>
extern "C" {
#include "../core/core.h"
}

namespace Ui {
class plotwindow;
}

class plotwindow : public QWidget {
  Q_OBJECT

 public:
  explicit plotwindow(QWidget *parent = nullptr, const QString func = "x");
  ~plotwindow();

 private:
  Ui::plotwindow *ui;

 private slots:
  void makeplot();
};

#endif  // PLOTWINDOW_H
