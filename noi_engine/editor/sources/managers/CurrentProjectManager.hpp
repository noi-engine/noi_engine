#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QString>

namespace noi_engine_editor
{
    class CurrentProjectManager : public QObject
    {
        Q_OBJECT
        QML_ELEMENT
        QML_SINGLETON

        Q_PROPERTY(QString name READ name NOTIFY projectChanged)
        Q_PROPERTY(QString path READ path NOTIFY projectChanged)
        Q_PROPERTY(bool isOpen READ isOpen NOTIFY projectChanged)

    public:
        explicit CurrentProjectManager(QObject* parent = nullptr);

        Q_INVOKABLE [[nodiscard]] auto openProject(const QString& path) -> bool;
        Q_INVOKABLE auto closeProject() -> void;

        [[nodiscard]] auto name() const -> QString;
        [[nodiscard]] auto path() const -> QString;
        [[nodiscard]] auto isOpen() const -> bool;

    signals:
        void projectChanged();
        void projectOpenFailed(const QString& reason);

    private:
        QString m_name;
        QString m_path;
        bool m_isOpen{false};
    };
}
