#include "engrampa-menu-plugin.h"

#include <QAction>
#include <QFileInfo>
#include <QTranslator>
#include <QLocale>
#include <QApplication>
#include <QProcess>
#include <QDebug>


using namespace Peony;

EngrampaMenuPlugin::EngrampaMenuPlugin(QObject *parent) : QObject (parent)
{
    QTranslator *t = new QTranslator(this);
    qDebug()<<"system().name:"<<QLocale::system().name();
    qDebug()<<"\n\n\n\n\n\n\ntranslate:"<<t->load(":/translations/peony-qt-karchive-extension_"+QLocale::system().name());
    QApplication::installTranslator(t);
}

QList<QAction*> EngrampaMenuPlugin::menuActions(Types types, const QString &uri, const QStringList &selectionUris)
{
    QList<QAction*> actions;
    if (types == MenuPluginInterface::DirectoryView || types == MenuPluginInterface::DesktopWindow)
    {
        if (! selectionUris.isEmpty()) {
            QFileInfo file(selectionUris.first());
            QAction *compress = new QAction(tr("compress..."));
            actions<<compress;
            connect(compress, &QAction::triggered, [=](){
                qDebug()<<"compress file:"<<uri<<selectionUris;
                QProcess p;
                p.setProgram("engrampa");
                p.setArguments(QStringList()<<"-d"<<selectionUris);
                p.start();
                p.waitForFinished();
            });

            //check is compressed file
            qDebug()<<"file.suffix"<<file.suffix()<<file.isDir()<<file;
            if (!file.isDir() && is_uncompressed_file(selectionUris.first()))
            {
                QAction *un_compress_default = new QAction(tr("uncompress to current path"));
                actions<<un_compress_default;
                connect(un_compress_default, &QAction::triggered, [=](){
                    QProcess p;
                    p.setProgram("engrampa");
                    p.setArguments(QStringList()<<"-h"<<selectionUris);
                    p.start();
                    p.waitForFinished();
                });

                QAction *un_compress_specific = new QAction(tr("uncompress to specific path"));
                actions<<un_compress_specific;
                connect(un_compress_specific, &QAction::triggered, [=](){
                    QProcess p;
                    p.setProgram("engrampa");
                    p.setArguments(QStringList()<<"-f"<<selectionUris);
                    p.start();
                    p.waitForFinished();
                });
            }
        }
    }


    return actions;
}

bool EngrampaMenuPlugin::is_uncompressed_file(QString file_name)
{
    for(auto name: m_file_type_list)
    {
        if (file_name.endsWith(name))
            return true;
    }

    return false;
}

