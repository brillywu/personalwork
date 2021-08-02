#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString appcfg_filename= QCoreApplication::applicationDirPath() + "/app.cfg";
    qDebug() << appcfg_filename;
    QFile loadFile( appcfg_filename );
    QJsonDocument appcfg;

    if (loadFile.open(QIODevice::ReadOnly)) {
        qInfo("open app.cfg ok.");
        QByteArray saveData = loadFile.readAll();
        appcfg =  QJsonDocument::fromJson(saveData);
        loadFile.close();

        qDebug() << appcfg << "\n" ;
        qDebug() << appcfg["filehandler"] << "\n" << appcfg["filehandler"]["md"];

        QString ext="md";
        if( appcfg["filehandler"][ext].isArray() ){
            const QJsonArray oa = appcfg["filehandler"][ext].toArray();
            for( QJsonArray::const_iterator it=oa.begin(); it != oa.end() ;it ++){
                QJsonObject one=(*it).toObject();
                for (QJsonObject::const_iterator i = one.begin(); i != one.end(); ++i) {
                    if (i.value().isNull()){
                            qDebug() << i.key();
                    } else {
                        qDebug() << i.key() << i.value();
                    }
                }
            }
        }
    }

    return a.exec();
}
