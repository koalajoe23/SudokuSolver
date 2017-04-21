#ifndef SUDOKUSOLVER_QML_PLUGIN_H
#define SUDOKUSOLVER_QML_PLUGIN_H

#include <QQmlExtensionPlugin>

namespace SudokuSolver { namespace Qml {
class Plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri);
};
}}
#endif // SUDOKUSOLVER_QML_PLUGIN_H
