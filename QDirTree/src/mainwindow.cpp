#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QScroller>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);

//    if (parser.isSet(dontUseCustomDirectoryIconsOption))
//        model.setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
//    if (parser.isSet(dontWatchOption))
//        model.setOption(QFileSystemModel::DontWatchForChanges);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_openfolder_clicked()
{
    QFileDialog dialog;
//    QTreeView *tree = dialog.findChild <QTreeView*>();
//    tree->setRootIsDecorated(true);
//    tree->setItemsExpandable(true);

    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.setViewMode(QFileDialog::Detail);
    int result =dialog.exec();
    QString directory;
    if (result)
    {
        directory = dialog.selectedFiles()[0];
        qDebug()<<directory;
        int item_idx= ui->cb_folders->findText(directory);
        if(  item_idx != -1) {
            ui->cb_folders->setCurrentIndex(item_idx);
            return;
        }

        ui->cb_folders->addItem(directory);
        ui->cb_folders->setCurrentIndex(ui->cb_folders->count()-1);
    }
}

void MainWindow::on_cb_folders_currentTextChanged(const QString &arg1)
{
    model.setRootPath(arg1);
    const QString& rootPath = arg1;

    QTreeView& tree = *ui->treeView;

    tree.setModel(&model);
    if (!rootPath.isEmpty()) {
        const QModelIndex rootIndex = model.index(QDir::cleanPath(rootPath));
        if (rootIndex.isValid())
            tree.setRootIndex(rootIndex);
    }

    // Demonstrating look and feel features
    tree.setAnimated(false);
    tree.setIndentation(20);
    tree.setSortingEnabled(false);
    tree.setColumnWidth(0, tree.width() / 3);

    // Make it flickable on touchscreens
    QScroller::grabGesture(&tree, QScroller::TouchGesture);

}

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    //! 创建右键菜单
    QMenu menu;

    //! 添加右键菜单中的action

    QAction* action1 = new QAction(&menu);
    action1 ->setObjectName("action1 ");
    action1 ->setText(tr("1111"));
    menu.addAction(action1 );

    //! 显示该菜单，进入消息循环
    menu.exec(ui->treeView->mapToGlobal(pos)/*全局位置*/);

}
