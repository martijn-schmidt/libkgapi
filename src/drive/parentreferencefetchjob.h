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

#ifndef KGAPI2_DRIVEPARENTREFERENCEFETCHJOB_H
#define KGAPI2_DRIVEPARENTREFERENCEFETCHJOB_H

#include "fetchjob.h"
#include "kgapidrive_export.h"

namespace KGAPI2
{

namespace Drive
{

class KGAPIDRIVE_EXPORT ParentReferenceFetchJob : public KGAPI2::FetchJob
{
    Q_OBJECT

  public:
    explicit ParentReferenceFetchJob(const QString &fileId,
                                     const AccountPtr &account,
                                     QObject *parent = 0);
    explicit ParentReferenceFetchJob(const QString &fileId,
                                     const QString &referenceId,
                                     const AccountPtr &account,
                                     QObject *parent = 0);
    virtual ~ParentReferenceFetchJob();

  protected:
    virtual void start();
    virtual KGAPI2::ObjectsList handleReplyWithItems(const QNetworkReply *reply,
                                                     const QByteArray &rawData);

  private:
    class Private;
    Private *const d;
    friend class Private;

};

} // namespace Drive

} // namespace KGAPI2

#endif // KGAPI2_DRIVEPARENTREFERENCEFETCHJOB_H