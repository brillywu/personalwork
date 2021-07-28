#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <ui_mainwindow.h>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
};
#endif // MAINWIDGET_H
