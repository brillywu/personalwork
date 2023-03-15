#include "wmain.h"
#include "ui_main.h"
#include "ioworker.h"
#include "IoLoger.h"

Widget::Widget(IoWorker* w,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , worker(w)
{
    ui->setupUi(this);
    QFile file("c6657-cmdlist.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            ui->comboBox->addItem(line);
        }
    }
    serial_loger = new PlainTextEditLoger( ui->serial_txt);
    udp_loger = new PlainTextEditLoger(ui->udp_txt);
    worker->registerLoger(udp_loger, serial_loger);
    worker->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    if(worker){
        worker->stop();
    }
}

void Widget::on_filter_go_clicked()
{
}

void Widget::on_choice_go_clicked()
{
    QList<uint16_t> filter;
    QStringList l = ui->choice_txt->text().split(",");
    for (auto t : l) {
        filter.push_back(t.toInt());
    }
    udp_loger->register_filter(filter);
}

void Widget::on_serial_go_clicked()
{
    QStringList l1 = ui->comboBox->currentText().split(":");
    QStringList l2 = l1[1].split(",");
    QByteArray data;
    bool ok;
    for (QString t : l2) {
        uint8_t tmp = t.toInt(&ok,16);        
        data.push_back(tmp);
    }
    qDebug() << "Serial send:" << l1[0] << ":" << data.toHex(' ');
    worker->serial_sender()->send(data.data(), data.size());
    serial_loger->chardump(false, data.data(), data.size());
}

