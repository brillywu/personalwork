#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class IoWorker;
class IIoLoger;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(IoWorker* w, QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    IoWorker* worker;
    IIoLoger* serial_loger;
    IIoLoger* udp_loger;
    void closeEvent(QCloseEvent *event);

Q_SIGNALS:
    void stop();

public slots:
    void on_filter_go_clicked();
    void on_choice_go_clicked();
    void on_serial_go_clicked();


};
#endif // WIDGET_H
