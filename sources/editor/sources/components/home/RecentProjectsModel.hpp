#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>

#include "../managers/RecentProjectsManager.hpp"

namespace noi_engine_editor
{
    class RecentProjectsModel : public QAbstractListModel
    {
        Q_OBJECT
        QML_ELEMENT

        Q_PROPERTY(RecentProjectsManager* manager READ manager WRITE setManager NOTIFY managerChanged)

    public:
        enum Roles
        {
            NameRole = Qt::UserRole + 1,
            PathRole,
            LastOpenedRole,
        };

        explicit RecentProjectsModel(QObject* parent = nullptr);

        [[nodiscard]] auto roleNames() const -> QHash<int, QByteArray> override;

        [[nodiscard]] auto rowCount(const QModelIndex& parent) const -> int override;

        [[nodiscard]] auto data(const QModelIndex& index, int role) const -> QVariant override;

        [[nodiscard]] auto manager() const -> RecentProjectsManager*;

        auto setManager(RecentProjectsManager* manager) -> void;

    signals:
        void managerChanged();

    private:
        auto refreshModel() -> void;

        QList<ProjectInfo> m_cachedProjects;
        RecentProjectsManager* m_manager = nullptr;
    };
}