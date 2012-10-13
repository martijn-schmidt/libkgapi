/*
    Copyright 2012  Andrius da Costa Ribas <andriusmao@gmail.com>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIBKGAPI_OBJECTS_DRIVEPERMISSION_P_H
#define LIBKGAPI_OBJECTS_DRIVEPERMISSION_P_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMap>

namespace KGAPI
{
    
namespace Objects
{

class DrivePermissionPrivate
{
public:
    DrivePermissionPrivate() { };
    DrivePermissionPrivate(const DrivePermissionPrivate& other);
    ~DrivePermissionPrivate() { };
    
    QString id;
    QString selfLink;
    QString name;
    QString role;
    QStringList additionalRoles;
    QString type;
    QString authKey;
    bool withLink;
    QString photoLink;
    QString value;
};

} /* namespace Objects */

} /* namespace KGAPI */
    
#endif // LIBKGAPI_OBJECTS_DRIVEPERMISSION_P_H
