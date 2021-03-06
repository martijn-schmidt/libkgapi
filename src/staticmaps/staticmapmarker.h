/*
    Copyright (C) 2012  Jan Grulich <grulja@gmail.com>

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


#ifndef LIBKGAPI2_STATICMAPMARKER_H
#define LIBKGAPI2_STATICMAPMARKER_H

#include "kgapimaps_export.h"

#include <QColor>

#include <KContacts/Address>
#include <KContacts/Geo>

namespace KGAPI2
{

/**
 * @brief Represents marker with defined label, color, size and markers
 *
 * @author: Jan Grulich <grulja@gmail.com>
 * @since: 0.4
 */
class KGAPIMAPS_EXPORT StaticMapMarker
{

  public:

    enum MarkerSize {
        Tiny,
        Small,
        Middle,
        Normal
    };

    enum LocationType {
        Undefined = -1,
        String,
        KABCAddress,
        KABCGeo
    };

    /**
     * @brief Constructs an empty marker
     */
    StaticMapMarker();

    /**
     * @brief Constructs a new marker
     *
     * @param address Location in QString where marker will be visible
     * @param label Specifies a single uppercase alphanumeric character from
     *              set {A-Z, 0-9} which will be displayed in the marker
     * @param size Specifies the size of marker
     * @param color Color of marker
     */
    explicit StaticMapMarker(const QString & address, const QChar & label = QChar(),
                             const MarkerSize size = Normal, const QColor & color = Qt::red);

    /**
     * @brief Constructs a new marker
     *
     * @param address Location in KContacts::Address where marker will be visible
     * @param label Specifies a single uppercase alphanumeric character from
     *              set {A-Z, 0-9} which will be displayed in the marker
     * @param size Specifies the size of marker
     * @param color Color of marker
     */
    explicit StaticMapMarker(const KContacts::Address & address, const QChar & label = QChar(),
                             const MarkerSize size = Normal, const QColor & color = Qt::red);

    /**
     * @brief Constructs a new marker
     *
     * @param address Location in KContacts::Geo where marker will be visible
     * @param label Specifies a single uppercase alphanumeric character from
     *              set {A-Z, 0-9} which will be displayed in the marker
     * @param size Specifies the size of marker
     * @param color Color of marker
     */
    explicit StaticMapMarker(const KContacts::Geo & address, const QChar & label = QChar(),
                             const MarkerSize size = Normal, const QColor & color = Qt::red);

    /**
     * @brief Constructs a new marker
     *
     * @param label Specifies a single uppercase alphanumeric character from
     *              set {A-Z, 0-9} which will be displayed in the marker
     * @param size Specifies the size of marker
     * @param color Color of marker
     */
    explicit StaticMapMarker(const QStringList & locations, const QChar & label = QChar(),
                             const MarkerSize size = Normal, const QColor & color = Qt::red);

    /**
     * @brief Constructs a new marker
     *
     * @param locations Locations in KContacts::Address where marker will be visible
     * @param label Specifies a single uppercase alphanumeric character from
     *              set {A-Z, 0-9} which will be displayed in the marker
     * @param size Specifies the size of marker
     * @param color Color of marker
     */
    explicit StaticMapMarker(const KContacts::Address::List &locations, const QChar & label = QChar(),
                             const MarkerSize size = Normal, const QColor & color = Qt::red);

    /**
     * @brief Constructs a new marker
     *
     * @param locations Locations in KContacts::Geo where marker will be visible
     * @param label Specifies a single uppercase alphanumeric character from
     *              set {A-Z, 0-9} which will be displayed in the marker
     * @param size Specifies the size of marker
     * @param color Color of marker
     */
    explicit StaticMapMarker(const QList<KContacts::Geo> & locations, const QChar & label = QChar(),
                             const MarkerSize size = Normal, const QColor & color = Qt::red);

    /**
     * @brief Copy constructor
     */
    StaticMapMarker(const StaticMapMarker & other);

    /**
     * @brief Destructor
     */
    ~StaticMapMarker();

    /**
     * @brief Returns in which format is location saved.
     */
    LocationType locationType() const;

    /**
     * @brief Returns color of marker
     */
    QColor color() const;

    /**
     * @brief Sets color of marker
     *
     * @param color Color for marker
     */
    void setColor(const QColor & color);

    /**
     * @brief Returns if marker is valid. It means that marker needs defined location
     */
    bool isValid() const;

    /**
     * @brief Returns label of marker
     */
    QChar label() const;

    /**
     * @brief Sets label of marker
     *
     * @param label Specifies a single uppercase alphanumeric character from
     *              set {A-Z, 0-9} which will be displayed in the marker
     */
    void setLabel(const QChar & label);

    /**
     * @brief Returns locations in QString
     */
    QStringList locationsString() const;

    /**
     * @brief Sets one location for marker
     *
     * @param location Location for marker in QString
     */
    void setLocation(const QString & location);

    /**
     * @brief Sets locations for marker
     *
     * @param locations Locations for marker in QString
     */
    void setLocations(const QStringList & locations);

    /**
     * @brief Returns locations in KContacts::Address
     */
    KContacts::Address::List locationsAddress() const;

    /**
     * @brief Sets one location for marker
     *
     * @param location Location for marker in KContacts::Address
     */
    void setLocation(const KContacts::Address & location);

    /**
     * @brief Sets locations for marker
     *
     * @param locations Locations for marker in KContacts::Address
     */
    void setLocations(const KContacts::Address::List &locations);

    /**
     * @brief Returns locations in KContacts::Geo
     */
    QList<KContacts::Geo> locationsGeo() const;

    /**
     * @brief Sets one location for marker
     *
     * @param location Location for marker in KContacts::Geo
     */
    void setLocation(const KContacts::Geo & location);

    /**
     * @brief Sets locations for marker
     *
     * @param locations Locations for marker in KContacts::Geo
     */
    void setLocations(const QList<KContacts::Geo> & locations);

    /**
     * @brief Returns all locations and markers preferences in format to URL query.
     */
    QString toString() const;

    /**
     * @brief Returns size of marker
     */
    MarkerSize size() const;

    /**
     * @brief Sets size of marker
     *
     * @param size Specifies the size of marker
     */
    void setSize(const MarkerSize size);

    /**
     * @brief Assignment operator
     */
    StaticMapMarker& operator=(const StaticMapMarker &other);

  private:
    class Private;
    Private * const d;
    friend class Private;

};

} // namespace KGAPI2


#endif // LIBKGAPI2_STATICMAPMARKER_H
