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

#include "contactsgroupmodifyjob.h"
#include "contactsgroup.h"
#include "contactsservice.h"
#include "../debug.h"
#include "utils.h"
#include "account.h"
#include "private/queuehelper_p.h"

#include <QNetworkRequest>
#include <QNetworkReply>


using namespace KGAPI2;

class Q_DECL_HIDDEN ContactsGroupModifyJob::Private
{
  public:
    QueueHelper<ContactsGroupPtr> groups;
};

ContactsGroupModifyJob::ContactsGroupModifyJob(const ContactsGroupsList& groups, const AccountPtr& account, QObject* parent):
    ModifyJob(account, parent),
    d(new Private)
{
    d->groups = groups;
}

ContactsGroupModifyJob::ContactsGroupModifyJob(const ContactsGroupPtr& group, const AccountPtr& account, QObject* parent):
    ModifyJob(account, parent),
    d(new Private)
{
    d->groups << group;
}

ContactsGroupModifyJob::~ContactsGroupModifyJob()
{
    delete d;
}


void ContactsGroupModifyJob::start()
{
    if (d->groups.atEnd()) {
        emitFinished();
        return;
    }

    const ContactsGroupPtr group = d->groups.current();

    const QUrl url = ContactsService::updateGroupUrl(account()->accountName(), group->id());
    QNetworkRequest request;
    request.setRawHeader("Authorization", "Bearer " + account()->accessToken().toLatin1());
    request.setRawHeader("GData-Version", ContactsService::APIVersion().toLatin1());
    request.setUrl(url);

    QByteArray rawData = ContactsService::contactsGroupToXML(group);
    rawData.prepend("<atom:entry xmlns:atom=\"http://www.w3.org/2005/Atom\" "
                     "xmlns:gd=\"http://schemas.google.com/g/2005\" "
                     "xmlns:gContact=\"http://schemas.google.com/contact/2008\">"
                    "<atom:category scheme=\"http://schemas.google.com/g/2005#kind\" "
                     "term=\"http://schemas.google.com/g/2008#group\"/>");
    rawData.append("</atom:entry>");

    QStringList headers;
    auto rawHeaderList = request.rawHeaderList();
    headers.reserve(rawHeaderList.size());
    for (const QByteArray &str : qAsConst(rawHeaderList)) {
        headers << QLatin1String(str) + QLatin1String(": ") + QLatin1String(request.rawHeader(str));
    }
    qCDebug(KGAPIRaw) << headers;

    enqueueRequest(request, rawData, QStringLiteral("application/atom+xml"));
}

ObjectsList ContactsGroupModifyJob::handleReplyWithItems(const QNetworkReply *reply, const QByteArray& rawData)
{
    const QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
    ContentType ct = Utils::stringToContentType(contentType);
    ObjectsList items;
    if (ct == KGAPI2::JSON) {
        items << ContactsService::JSONToContactsGroup(rawData);
        d->groups.currentProcessed();
    } else if (ct == KGAPI2::XML) {
        items << ContactsService::XMLToContactsGroup(rawData);
        d->groups.currentProcessed();
    } else {
        setError(KGAPI2::InvalidResponse);
        setErrorString(tr("Invalid response content type"));
        emitFinished();
        return items;
    }

    // Enqueue next item or finish
    start();

    return items;
}


