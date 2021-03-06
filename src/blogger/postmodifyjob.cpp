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

#include "postmodifyjob.h"
#include "post.h"
#include "bloggerservice.h"
#include "account.h"
#include "utils.h"

#include <QNetworkRequest>
#include <QNetworkReply>

using namespace KGAPI2;
using namespace KGAPI2::Blogger;

class Q_DECL_HIDDEN PostModifyJob::Private
{
  public:
    Private(const PostPtr &post);

    PostPtr post;
};

PostModifyJob::Private::Private(const PostPtr &post_)
    : post(post_)
{
}

PostModifyJob::PostModifyJob(const PostPtr &post,
                             const AccountPtr &account,
                             QObject *parent)
    : ModifyJob(account, parent)
    , d(new Private(post))
{
}

PostModifyJob::~PostModifyJob()
{
    delete d;
}

void PostModifyJob::start()
{
    const QUrl url = BloggerService::modifyPostUrl(d->post->blogId(), d->post->id());
    QNetworkRequest request;
    request.setRawHeader("Authorization", "Bearer " + account()->accessToken().toLatin1());
    request.setUrl(url);

    const QByteArray rawData = Post::toJSON(d->post);
    enqueueRequest(request, rawData, QStringLiteral("application/json"));
}

ObjectsList PostModifyJob::handleReplyWithItems(const QNetworkReply *reply, const QByteArray &rawData)
{
    const QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
    ContentType ct = Utils::stringToContentType(contentType);
    ObjectsList items;
    if (ct != KGAPI2::JSON) {
        setError(KGAPI2::InvalidResponse);
        setErrorString(tr("Invalid response content type"));
        emitFinished();
        return items;
    }

    items << Post::fromJSON(rawData);
    emitFinished();
    return items;
}
