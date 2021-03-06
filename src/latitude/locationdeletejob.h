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

#ifndef LIBKGAPI2_LOCATIONDELETEJOB_H
#define LIBKGAPI2_LOCATIONDELETEJOB_H

#include "deletejob.h"
#include "kgapilatitude_export.h"

namespace KGAPI2 {

/**
 * @brief A job to delete one or more location from user's account on
 *        Google Latitude service
 *
 * Note that operation is irreversible.
 *
 * @author Daniel Vrátil <dvratil@redhat.com>
 * @since 2.0
 */
class KGAPILATITUDE_DEPRECATED_EXPORT LocationDeleteJob : public KGAPI2::DeleteJob
{
    Q_OBJECT

  public:

    /**
     * @brief Constructs a job that will delete user's current location from
     *        his/her Google Latitude account.
     *
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit LocationDeleteJob(const AccountPtr &account, QObject* parent);

    /**
     * @brief Constructs a job that will delete given @p location from user's
     *        Google Latitude account.
     *
     * @param location Location to delete
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit LocationDeleteJob(const LocationPtr &location,
                               const AccountPtr &account, QObject* parent);

    /**
     * @brief Constructs a job that will delete given location with given
     *         @p timestamp from user'sGoogle Latitude account.
     *
     * @param timestamp Timestamp of location to delete
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit LocationDeleteJob(qulonglong timestamp,
                               const AccountPtr &account, QObject* parent);

    /**
     * @brief Destructor
     */
    ~LocationDeleteJob() override;

  protected:

    /**
     * @brief KGAPI2::Job::start implementation
     */
    void start() override;

  private:
    class Private;
    Private * const d;
    friend class Private;

};

} // namespace KGAPI2

#endif // LIBKGAPI2_LOCATIONDELETEJOB_H
