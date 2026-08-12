#include "SettingsManager.hpp"

#include <QDir>
#include <QSettings>
#include <QStandardPaths>

namespace noi_engine_editor
{
    namespace
    {
        constexpr auto DEFAULT_PROJECTS_PATH_KEY = "defaultProjectsPath";
    }

    SettingsManager::SettingsManager(QObject* parent) : QObject(parent)
    {
        QSettings settings;
        const auto fallback = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/NoiEngine/Projects";

        m_defaultProjectsPath = settings.value(DEFAULT_PROJECTS_PATH_KEY, fallback).toString();
        QDir().mkpath(m_defaultProjectsPath);
    }

    auto SettingsManager::defaultProjectsPath() const -> QString
    {
        return m_defaultProjectsPath;
    }

    auto SettingsManager::setDefaultProjectsPath(const QString& path) -> void
    {
        if (m_defaultProjectsPath == path)
        {
            return;
        }

        m_defaultProjectsPath = path;

        QSettings settings;
        settings.setValue(DEFAULT_PROJECTS_PATH_KEY, path);

        emit defaultProjectsPathChanged();
    }
}