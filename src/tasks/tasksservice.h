/*
    Copyright (C) 2012 - 2018  Daniel Vrátil <dvratil@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIBKGAPI2_TASKSSERVICE_H
#define LIBKGAPI2_TASKSSERVICE_H

#include "kgapitasks_export.h"
#include "types.h"

namespace KGAPI2
{

/**
 * @brief Additional methods for implementing support for Google Tasks service
 *
 * You should never need to use these methods, unless implementing your own Job
 */
namespace TasksService
{

    /**
     * @brief Parses JSON data into a Task object
     *
     * @param jsonData
     */
    KGAPITASKS_EXPORT TaskPtr JSONToTask(const QByteArray& jsonData);

    /**
     * @brief Serializes a Task object into JSON
     *
     * @param task
     */
    KGAPITASKS_EXPORT QByteArray taskToJSON(const TaskPtr& task);

    /**
     * @brief Parses JSON data into a TaskList object
     *
     * @param jsonData
     */
    KGAPITASKS_EXPORT TaskListPtr JSONToTaskList(const QByteArray& jsonData);

    /**
     * @brief Serializes a TaskList into JSON data
     *
     * @param taskList
     */
    KGAPITASKS_EXPORT QByteArray taskListToJSON(const TaskListPtr& taskList);

    /**
     * @brief Parses JSON feed into list of Tasks or TaskLists
     *
     * @param jsonFeed
     * @param feedData The structure will be filled with additional information
     *                 about the feed
     */
    KGAPITASKS_EXPORT ObjectsList parseJSONFeed(const QByteArray& jsonFeed, FeedData& feedData);

    /**
     * @brief Returns URL to create a single task
     *
     * @param tasklistID ID of parent task list
     */
    KGAPITASKS_EXPORT QUrl createTaskUrl(const QString &tasklistID);

    /**
     * @brief Returns URL to fetch all tasks from a single tasklist
     *
     * @param tasklistID ID of parent task list
     */
    KGAPITASKS_EXPORT QUrl fetchAllTasksUrl(const QString &tasklistID);

    /**
     * @brief Returns URL for fetching a single task
     *
     * @param tasklistID ID of parent task list
     * @param taskID ID of task to fetch
     */
    KGAPITASKS_EXPORT QUrl fetchTaskUrl(const QString &tasklistID, const QString &taskID);

    /**
     * @brief Returns URL for updating a task
     *
     * @param tasklistID ID of parent task list
     * @param taskID ID of task to update
     */
    KGAPITASKS_EXPORT QUrl updateTaskUrl(const QString &tasklistID, const QString &taskID);

    /**
     * @brief Returns URL for removing a task
     *
     * @param tasklistID ID of parent task list
     * @param taskID ID of task to remove
     */
    KGAPITASKS_EXPORT QUrl removeTaskUrl(const QString &tasklistID, const QString &taskID);

    /**
     * @brief Returns URL to reparent task.
     *
     * @param tasklistID ID of parent task list
     * @param taskID ID of task to move
     * @param newParent UID of new parent item
     */
    KGAPITASKS_EXPORT QUrl moveTaskUrl(const QString &tasklistID, const QString &taskID, const QString &newParent);

    /**
     * @brief Returns URL for fetching all tasklists
     */
    KGAPITASKS_EXPORT QUrl fetchTaskListsUrl();

    /**
     * @brief Returns URL for creating a new tasklist
     */
    KGAPITASKS_EXPORT QUrl createTaskListUrl();

    /**
     * @brief Returns URL for modifying a tasklist
     *
     * @param tasklistID ID of task list to update
     */
    KGAPITASKS_EXPORT QUrl updateTaskListUrl(const QString &tasklistID);

    /**
     * @brief Returns URL for deleting a tasklist
     *
     * @param tasklistID ID of task list to remove
     */
    KGAPITASKS_EXPORT QUrl removeTaskListUrl(const QString &tasklistID);

} /* namespace TasksServices */

} /* namespace KGAPI2 */

#endif // LIBKGAPI2_TASKSSERVICE_H
