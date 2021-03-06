/*
 * Copyright (C) 2014  Daniel Vrátil <dvratil@redhat.com>
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

#include "blogfetchjob.h"
#include "blog.h"
#include "bloggerservice.h"
#include "account.h"
#include "utils.h"

#include <QNetworkRequest>
#include <QNetworkReply>

using namespace KGAPI2;
using namespace KGAPI2::Blogger;

class Q_DECL_HIDDEN BlogFetchJob::Private
{
  public:
    Private(const QString &id, FetchBy fetchBy);
    ~Private();

    QString id;
    FetchBy fetchBy;
};

BlogFetchJob::Private::Private(const QString &id_, FetchBy fetchBy_)
    : id(id_)
    , fetchBy(fetchBy_)
{
}

BlogFetchJob::Private::~Private()
{
}

BlogFetchJob::BlogFetchJob(const QString &id,
                           FetchBy fetchBy,
                           const AccountPtr &account,
                           QObject *parent)
    : FetchJob(account, parent)
    , d(new Private(id, fetchBy))
{
}

BlogFetchJob::~BlogFetchJob()
{
    delete d;
}


void BlogFetchJob::start()
{
    QNetworkRequest request;
    switch (d->fetchBy) {
        case FetchByBlogId:
            request.setUrl(BloggerService::fetchBlogByBlogIdUrl(d->id));
            break;
        case FetchByBlogUrl:
            request.setUrl(BloggerService::fetchBlogByBlogUrlUrl(d->id));
            break;
        case FetchByUserId:
            request.setUrl(BloggerService::fetchBlogsByUserIdUrl(d->id));
            break;
    }
    if (account()) {
        request.setRawHeader("Authorization", "Bearer " + account()->accessToken().toLatin1());
    }

    enqueueRequest(request);
}

ObjectsList BlogFetchJob::handleReplyWithItems(const QNetworkReply *reply, const QByteArray &rawData)
{
    ObjectsList items;

    const QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
    ContentType ct = Utils::stringToContentType(contentType);
    if (ct == KGAPI2::JSON) {
        if (d->fetchBy == FetchByUserId) {
            items << Blog::fromJSONFeed(rawData);
        } else {
            items << Blog::fromJSON(rawData);
        }
    } else {
        setError(KGAPI2::InvalidResponse);
        setErrorString(tr("Invalid response content type"));
    }

    emitFinished();
    return items;
}


