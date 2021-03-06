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

#ifndef LIBKGAPI2_REMINDER_H
#define LIBKGAPI2_REMINDER_H

#include "object.h"
#include "types.h"
#include "kgapicalendar_export.h"

#include <KCalCore/Alarm>
#include <KCalCore/Incidence>

namespace KGAPI2
{

/**
 * @brief Represents a default calendar reminder.
 *
 * @author Daniel Vrátil <dvratil@redhat.com>
 * @since 0.4
 */
class KGAPICALENDAR_EXPORT Reminder
{
  public:

    /**
     * @brief Constrcutor
     */
    explicit Reminder();

    /**
     * @brief Constructor
     *
     * @param type Type of the reminder (email, notification, etc.)
     * @param startOffset How long before the event should the reminder be shown
     */
    explicit Reminder( const KCalCore::Alarm::Type &type,
                       const KCalCore::Duration &startOffset = KCalCore::Duration( 0 ) );

    /**
     * @brief Copy constructor
     */
    Reminder( const Reminder &other );

    /**
     * @brief Destructor
     */
    virtual ~Reminder();

    bool operator==(const Reminder &other) const;

    /**
     * @brief Returns type of the remider
     */
    KCalCore::Alarm::Type type() const;

    /**
     * @brief Sets type of the reminder
     *
     * @param type
     */
    void setType(KCalCore::Alarm::Type type );

    /**
     * @brief Returns how long before the event should reminder be shown
     */
    KCalCore::Duration startOffset() const;

    /**
     * @brief Sets how long before the event should reminder be shown
     */
    void setStartOffset( const KCalCore::Duration &startOffset );

    /**
     * @brief Converts the reminder to a KCalCore::Alarm
     *
     * @param incidence An incidence on which the reminder should be applied
     * @return Returns a new KCalCore::Alarm
     */
    KCalCore::Alarm *toAlarm( KCalCore::Incidence *incidence ) const;

  private:
    class Private;
    Private *const d;
};

} // namespace KGAPI2

#endif // LIBKGAPI2_REMINDER_H
