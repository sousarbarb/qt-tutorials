#ifndef MYCLASS_H
#define MYCLASS_H

#include <QWidget>
#include <QMessageBox>

class MyClass : public QWidget
{
  Q_OBJECT
public:
  explicit MyClass(QWidget *parent = nullptr);

public slots:
  void doSomething();

signals:

};

#endif // MYCLASS_H
