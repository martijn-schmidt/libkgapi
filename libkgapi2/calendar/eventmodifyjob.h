/*
 * This file is part of LibKGAPI library
 *
 * Copyright (C) 2013  Daniel Vrátil <dvratil@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef LIBKGAPI2_EVENTMODIFYJOB_H
#define LIBKGAPI2_EVENTMODIFYJOB_H

#include <libkgapi2/modifyjob.h>
#include <libkgapi2/libkgapi2_export.h>

namespace KGAPI2 {

/**
 * @brief A job to modify events in a calendar on user's Google Calendar account.
 *
 * @author Daniel Vrátil <dvratil@redhat.com>
 * @since 2.0
 */
class LIBKGAPI2_EXPORT EventModifyJob : public KGAPI2::ModifyJob
{
    Q_OBJECT

  public:

    /**
     * @brief Constructs a job that will write changes in given @p event to
     *        corresponding event in calendar with given @p calendarId
     *
     * @param event Event to modify
     * @param calendarId ID of calendar where the event is stored
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit EventModifyJob(const EventPtr &event, const QString &calendarId,
                            const AccountPtr &account, QObject* parent = 0);

    /**
     * @brief Constructs a job that will write changes in given @p events to
     *        corresponding events in calendar with given @p calendarId
     *
     * @param events Events to modify
     * @param calendarId ID of calendar where the event is stored
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit EventModifyJob(const EventsList &events, const QString &calendarId,
                            const AccountPtr &account, QObject* parent = 0);

    /**
     * @brief Destructor
     */
    virtual ~EventModifyJob();

  protected:

    /**
     * @brief KGAPI2::Job::start implementation
     */
    virtual void start();

    /**
     * @brief KGAPI2::ModifyJob::handleReplyWithItems implementation
     *
     * @param reply
     * @param rawData
     */
    virtual ObjectsList handleReplyWithItems(const QNetworkReply *reply, const QByteArray& rawData);

  private:
    class Private;
    Private * const d;
    friend class Private;

};

} // namespace KGAPI

#endif // LIBKGAPI2_EVENTMODIFYJOB_H