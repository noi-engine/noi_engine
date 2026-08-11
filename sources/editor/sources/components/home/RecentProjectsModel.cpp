#include "RecentProjectsModel.hpp"

namespace noi_engine_editor
{
    RecentProjectsModel::RecentProjectsModel(QObject* parent)
        : QAbstractListModel(parent)
    {
        m_manager = qobject_cast<RecentProjectsManager*>(
            qmlEngine(this)
                ? qmlEngine(this)->singletonInstance<RecentProjectsManager*>(
                    "noi_engine_editor", "RecentProjectsManager")
                : nullptr
        );
        refreshModel();
    }

    auto RecentProjectsModel::refreshModel() -> void
    {
        beginResetModel();
        if (m_manager)
        {
            m_cachedProjects = m_manager->projects();
        }
        endResetModel();
    }

    auto RecentProjectsModel::rowCount(const QModelIndex& parent) const -> int
    {
        if (parent.isValid()) return 0;
        return static_cast<int>(m_cachedProjects.size());
    }

    auto RecentProjectsModel::data(const QModelIndex& index, int role) const -> QVariant
    {
        if (!index.isValid() || index.row() >= m_cachedProjects.size())
        {
            return {};
        }

        const auto& [name, path, lastOpened] = m_cachedProjects[index.row()];

        switch (role)
        {
        case NameRole: return name;
        case PathRole: return path;
        case LastOpenedRole: return lastOpened;
        default: return {};
        }
    }

    auto RecentProjectsModel::roleNames() const -> QHash<int, QByteArray>
    {
        return {
            {NameRole, "name"},
            {PathRole, "path"},
            {LastOpenedRole, "lastOpened"}
        };
    }
}
