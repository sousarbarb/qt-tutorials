#include "myclass.h"

MyClass::MyClass(QWidget *parent) : QWidget(parent) {  }

void MyClass::doSomething(){
  QMessageBox::information(this,"Hello Window","Hello World!");
}
