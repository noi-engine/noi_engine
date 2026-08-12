#include "CurrentProjectManager.hpp"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace noi_engine_editor
{
    CurrentProjectManager::CurrentProjectManager(QObject* parent) : QObject(parent)
    {
    }

    auto CurrentProjectManager::openProject(const QString& path) -> bool
    {
        QFile file(path + "/project.noiproj");
        if (!file.open(QIODevice::ReadOnly))
        {
            emit projectOpenFailed(tr("Cannot find project.noiproj"));
            return false;
        }

        const auto doc = QJsonDocument::fromJson(file.readAll());
        if (!doc.isObject())
        {
            emit projectOpenFailed(tr("Invalid project file"));
            return false;
        }

        m_name = doc.object()["name"].toString();
        m_path = path;
        m_isOpen = true;

        emit projectChanged();
        return true;
    }

    auto CurrentProjectManager::closeProject() -> void
    {
        m_name.clear();
        m_path.clear();
        m_isOpen = false;

        emit projectChanged();
    }

    auto CurrentProjectManager::name() const -> QString
    {
        return m_name;
    }

    auto CurrentProjectManager::path() const -> QString
    {
        return m_path;
    }

    auto CurrentProjectManager::isOpen() const -> bool
    {
        return m_isOpen;
    }
}