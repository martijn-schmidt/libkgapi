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

#include "pagemodifyjob.h"
#include "page.h"
#include "bloggerservice.h"
#include "utils.h"
#include "account.h"

#include <QNetworkReply>
#include <QNetworkRequest>

using namespace KGAPI2;
using namespace KGAPI2::Blogger;

class Q_DECL_HIDDEN PageModifyJob::Private
{
  public:
    Private(const PagePtr &page);

    PagePtr page;
};

PageModifyJob::Private::Private(const PagePtr &page_)
    : page(page_)
{
}

PageModifyJob::PageModifyJob(const PagePtr &page,
                             const AccountPtr &account,
                             QObject *parent)
    : ModifyJob(account, parent)
    , d(new Private(page))
{
}

PageModifyJob::~PageModifyJob()
{
    delete d;
}


void PageModifyJob::start()
{
    const QUrl url = BloggerService::modifyPageUrl(d->page->blogId(), d->page->id());
    QNetworkRequest request;
    request.setRawHeader("Authorization", "Bearer " + account()->accessToken().toLatin1());
    request.setUrl(url);

    const QByteArray rawData = Page::toJSON(d->page);
    enqueueRequest(request, rawData, QStringLiteral("application/json"));
}

ObjectsList PageModifyJob::handleReplyWithItems(const QNetworkReply *reply, const QByteArray &rawData)
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

    items << Page::fromJSON(rawData);
    emitFinished();
    return items;
}


