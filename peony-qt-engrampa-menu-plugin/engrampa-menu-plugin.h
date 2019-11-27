#ifndef ENGRAMPAMENUPLUGIN_H
#define ENGRAMPAMENUPLUGIN_H

#include "peony-qt-engrampa-menu-plugin_global.h"
#include "peony-qt/menu-plugin-iface.h"
#include "peony-qt/plugin-iface.h"

namespace Peony {

class PEONYQTENGRAMPAMENUPLUGINSHARED_EXPORT EngrampaMenuPlugin: public QObject, public MenuPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MenuPluginInterface_iid)
    Q_INTERFACES(Peony::MenuPluginInterface)
public:
    explicit EngrampaMenuPlugin(QObject *parent = nullptr);

    PluginInterface::PluginType pluginType() override {return PluginInterface::MenuPlugin;}
    const QString name() override {return tr("Peony-Qt KArchive Menu Extension");}
    const QString description() override {return tr("KArchive Menu Extension.");}
    const QIcon icon() override {return QIcon::fromTheme("utilities-terminal-symbolic");}
    void setEnable(bool enable) override {m_enable = enable;}
    bool isEnable() override {return m_enable;}

    QString testPlugin() override {return "test compress";}
    QList<QAction *> menuActions(Types types, const QString &uri, const QStringList &selectionUris) override;

    bool is_uncompressed_file(QString file_name);

private:
    bool m_enable;
    QStringList m_file_type_list = {"7z","ar","cbz","ear","exe","jar","tar","tar.7z",
                                    "tar.bz2","tar.gz","tar.lzma","tar.xz","war","zip"};
};

}

#endif // ENGRAMPAMENUPLUGIN_H
