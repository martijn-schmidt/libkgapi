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

#include "commentdeletejob.h"
#include "bloggerservice.h"
#include "comment.h"
#include "utils.h"
#include "account.h"

#include <QNetworkRequest>
#include <QNetworkReply>

using namespace KGAPI2;
using namespace KGAPI2::Blogger;

class Q_DECL_HIDDEN CommentDeleteJob::Private
{
  public:
    Private(const QString &blogId,
            const QString &postId,
            const QString &commentId);

    QString blogId;
    QString postId;
    QString commentId;

};

CommentDeleteJob::Private::Private(const QString &blogId_,
                                   const QString &postId_,
                                   const QString &commentId_)
    : blogId(blogId_)
    , postId(postId_)
    , commentId(commentId_)
{
}

CommentDeleteJob::CommentDeleteJob(const CommentPtr &comment,
                                   const AccountPtr &account,
                                   QObject *parent)
    : DeleteJob(account, parent)
    , d(new Private(comment->blogId(), comment->postId(), comment->id()))
{

}

CommentDeleteJob::CommentDeleteJob(const QString &blogId,
                                   const QString &postId,
                                   const QString &commentId,
                                   const AccountPtr &account,
                                   QObject *parent)
    : DeleteJob(account, parent)
    , d(new Private(blogId, postId, commentId))
{
}

CommentDeleteJob::~CommentDeleteJob()
{
    delete d;
}


void CommentDeleteJob::start()
{
    QNetworkRequest request(BloggerService::deleteCommentUrl(d->blogId, d->postId, d->commentId));
    request.setRawHeader("Authorization", "Bearer " + account()->accessToken().toLatin1());

    enqueueRequest(request);
}

void CommentDeleteJob::handleReply(const QNetworkReply *reply, const QByteArray &rawData)
{
    Q_UNUSED(reply);
    Q_UNUSED(rawData);

    emitFinished();
}



