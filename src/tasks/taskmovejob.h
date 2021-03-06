/*
 * This file is part of LibKGAPI library
 *
 * Copyright (C) 2013  Daniel Vrátil <dvratil@redhat.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef LIBKGAPI2_TASKMOVEJOB_H
#define LIBKGAPI2_TASKMOVEJOB_H

#include "modifyjob.h"
#include "kgapitasks_export.h"

namespace KGAPI2 {

/**
 * @brief A job that can reparent tasks to become subtasks of another task
 *
 * @author Daniel Vrátil <dvratil@redhat.com>
 * @since 2.0
 */
class KGAPITASKS_EXPORT TaskMoveJob : public KGAPI2::ModifyJob
{

    Q_OBJECT

  public:

    /**
     * @brief Constructs a job that will move given \p task in a tasklist
     *        with given @p taskListId to be a subtask of another task with
     *        @p newParentId.
     *
     * Passing an empty string in @p newParentId will move the task to top-level.
     *
     * @param task Task to move
     * @param taskListId ID of tasklist where the task is stored
     * @param newParentId ID of another task this task should become subtask of
     *                    or empty string to move the task to top level
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit TaskMoveJob(const TaskPtr &task, const QString &taskListId, 
                         const QString &newParentId, const AccountPtr &account,
                         QObject* parent = nullptr);

    /**
     * @brief Constructs a job that will move given \p tasks in a tasklist
     *        with given @p taskListId to be subtasks of given task with
     *        @p newParentId.
     *
     * Passing an empty string in @p newParentId will move the tasks to top-level.
     *
     * @param tasks Tasks to move
     * @param taskListId ID of tasklist where the task is stored
     * @param newParentId ID of another task this tasks should become subtasks of.
     *                    or empty string to move the tasks to top level
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit TaskMoveJob(const TasksList &tasks, const QString &taskListId,
                         const QString &newParentId, const AccountPtr &account,
                         QObject* parent = nullptr);

    /**
     * @brief Constructs a job that will move task with given \p taskId in a
     *        tasklist with given @p taskListId to be a subtask of another task
     *        with @p newParentId.
     *
     * Passing an empty string in @p newParentId will move the task to top-level.
     *
     * @param taskId ID of task to move
     * @param taskListId ID of tasklist where the task is stored
     * @param newParentId ID of another task this task should become subtask of.
     *                    or empty string to move the task to top level
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit TaskMoveJob(const QString &taskId, const QString &taskListId,
                         const QString &newParentId, const AccountPtr &account,
                         QObject* parent = nullptr);

    /**
     * @brief Constructs a job that will move tasks with given \p tasksIds in a
     *        tasklist with given @p taskListId to be subtasks of another task
     *        with @p newParentId.
     *
     * Passing an empty string in @p newParentId will move the tasks to top-level.
     *
     * @param tasksIds IDs of tasks to move
     * @param taskListId ID of tasklist where the tasks is stored
     * @param newParentId ID of another task this tasks should become subtasks of,
     *                    or empty string to move the tasks to top level
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit TaskMoveJob(const QStringList &tasksIds, const QString &taskListId,
                         const QString &newParentId, const AccountPtr &account,
                         QObject* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~TaskMoveJob() override;

  protected:

    /**
     * @brief KGAPI2::Job::start implementation
     */
    void start() override;

    /**
     * @brief KGAPI2::Job::dispatchRequest implementation
     *
     * @param accessManager
     * @param request
     * @param data
     * @param contentType
     */
    void dispatchRequest(QNetworkAccessManager *accessManager,
                                 const QNetworkRequest &request,
                                 const QByteArray &data,
                                 const QString &contentType) override;

    /**
     * @brief KGAPI2::Job::handleReply implementation
     *
     * @param reply
     * @param rawData
     */
    void handleReply(const QNetworkReply *reply,
                             const QByteArray& rawData) override;

  private:
    class Private;
    Private * const d;
    friend class Private;

};

} // namespace KGAPI2

#endif // LIBKGAPI2_TASKMOVEJOB_H
