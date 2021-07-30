#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QJsonDocument>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_openfolder_clicked();

    void on_cb_folders_currentTextChanged(const QString &arg1);

    void on_treeView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    QFileSystemModel model;
    QJsonDocument appcfg;
    QMenu* file_item_menu;
    QMenu* folder_item_menu;
    QMenu* file_open_with;

private slots:
     void openwith();
};

#endif // MAINWINDOW_H
