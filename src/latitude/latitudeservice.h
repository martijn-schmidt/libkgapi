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


#ifndef LIBKGAPI2_LATITUDESERVICE_H
#define LIBKGAPI2_LATITUDESERVICE_H

#include "types.h"
#include "latitude.h"
#include "kgapilatitude_export.h"


namespace KGAPI2
{


/**
 * @brief Additional methods for implementing support for Google Latitude service
 *
 * You should never need to use these methods, unless implementing your own Job
 */
namespace LatitudeService
{

    /**
     * @brief Parses JSON data into a Location object
     *
     * @param jsonData
     */
    KGAPILATITUDE_DEPRECATED_EXPORT LocationPtr JSONToLocation(const QByteArray& jsonData);

    /**
     * @brief Serializes a Location object to JSON
     *
     * @param location
     */
    KGAPILATITUDE_DEPRECATED_EXPORT QByteArray locationToJSON(const LocationPtr &location);


    /**
     * @brief Parses a JSON feed into list of Locations
     *
     * @param jsonFeed
     * @param feedData The structure will be filled with additional data about
     *                 the feed
     */
    KGAPILATITUDE_DEPRECATED_EXPORT ObjectsList parseLocationJSONFeed(const QByteArray& jsonFeed, FeedData& feedData);

    /**
     * @brief Supported version of API
     */
    KGAPILATITUDE_DEPRECATED_EXPORT QString APIVersion();

    /**
     * @brief Returns URL for fetch current user's location
     *
     * @param granularity
     */
    KGAPILATITUDE_DEPRECATED_EXPORT QUrl retrieveCurrentLocationUrl(const Latitude::Granularity granularity = Latitude::City);

    /**
     *  @brief Returns URL for deleting user's current location
     */
    KGAPILATITUDE_DEPRECATED_EXPORT QUrl deleteCurrentLocationUrl();

    /**
     *  @brief Returns URL for uploading user's current location
     */
    KGAPILATITUDE_DEPRECATED_EXPORT QUrl insertCurrentLocationUrl();

    /**
     * @brief Returns URL for fetching history of user's locations
     *
     * @param granularity Precision of the coordinates
     * @param maxResults Maximum amount of results to return
     * @param maxTime Maximum timestamp since epoch (in ms)
     * @param minTime Minimum timestamp since epoch (in ms)
     */
    KGAPILATITUDE_DEPRECATED_EXPORT QUrl locationHistoryUrl(const Latitude::Granularity granularity,
                                            const int maxResults = 0,
                                            const qlonglong maxTime = 0,
                                            const qlonglong minTime = 0);

    /**
     * @brief URL for fetching a specific location
     *
     * @param id
     * @param granularity;
     */
    KGAPILATITUDE_DEPRECATED_EXPORT QUrl retrieveLocationUrl(const qlonglong id,
                                             const Latitude::Granularity granularity = Latitude::City);

    /**
     * @brief Returns URL for uploading a location
     */
    KGAPILATITUDE_DEPRECATED_EXPORT QUrl insertLocationUrl();

    /**
     * @brief Returns URL to delete a specific location
     *
     * @param id
     */
    KGAPILATITUDE_DEPRECATED_EXPORT QUrl deleteLocationUrl(const qlonglong id);

} // namespace LatitudeService

} // namespace KGAPI2

#endif // LIBKGAPI2_LATITUDESERVICE_H
