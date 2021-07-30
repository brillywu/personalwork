#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QScroller>
#include <QJsonArray>
#include <QJsonObject>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    file_item_menu(new QMenu()),
    folder_item_menu(new QMenu())
{
    ui->setupUi(this);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    QString appcfg_filename= QCoreApplication::applicationDirPath() + "/app.cfg";
    qDebug() << appcfg_filename;
    QFile loadFile( appcfg_filename );

    if (loadFile.open(QIODevice::ReadOnly)) {
        qInfo("open app.cfg ok.");
        QByteArray saveData = loadFile.readAll();
        appcfg =  QJsonDocument::fromJson(saveData);
        loadFile.close();
        file_open_with = file_item_menu->addMenu(tr("open with...") );

    } else {
        qWarning("Couldn't open appcfg file.");
    }
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


void MainWindow::openwith()
{
    qDebug() << "openwith()...";
}

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    //! 创建右键菜单

    QModelIndex index = ui->treeView->currentIndex();
//    QString fileName = this->model.data(
//                this->model.index(index.row(), 1)
//                ).toString();
//    fileName="123.md";
//    QFileInfo fi(fileName);
    QMenu* menu=nullptr;

    if( model.isDir(index) ){
    } else {
        menu=this->file_item_menu;
        QString ext=model.fileInfo(index).suffix();
        if( appcfg["filehandler"][ext].isArray() ){
            const QJsonArray oa = appcfg["filehandler"][ext].toArray();
            for( QJsonArray::const_iterator it=oa.begin(); it != oa.end() ;it ++){
                QJsonObject one=(*it).toObject();
                for (QJsonObject::const_iterator i = one.begin(); i != one.end(); ++i) {
                    if (i.value().isNull()){
                            qDebug() << i.key();
                    } else {
                        qDebug() << i.key() << i.value();
                        QAction* action =this->file_open_with->addAction(i.key() );
                        action->setData( i.value() );
                        connect(action, &QAction::triggered, this, &MainWindow::openwith);
                    }
                }
            }
        } else {
            menu->addMenu("no operation.");
        }

    }

    if( menu != nullptr) menu->exec(ui->treeView->mapToGlobal(pos)/*全局位置*/);
}
