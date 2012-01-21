/*
    libKGoogle - KGoogleAuth
    Copyright (C) 2011  Dan Vratil <dan@progdan.cz>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "kgoogleauth.h"
#include "authdialog.h"

#include <kwallet.h>
#include <kdebug.h>
#include <kio/accessmanager.h>

#include <qnetworkreply.h>
#include <qnetworkrequest.h>

#include <qjson/parser.h>

using namespace KWallet;
using namespace KGoogle;

KGoogleAuth::KGoogleAuth(const QString &clientId, const QString &clientSecret, const QString &scope):
  m_clientId(clientId),
  m_clientSecret(clientSecret),
  m_scope(scope)
{
  m_kwallet = Wallet::openWallet(Wallet::NetworkWallet(), 0, Wallet::Asynchronous);
  connect(m_kwallet, SIGNAL(walletOpened(bool)),
	  this, SLOT(walletOpened(bool)));
}


KGoogleAuth::~KGoogleAuth()
{
  if (m_kwallet)
    delete m_kwallet;
}

QString KGoogleAuth::accessToken()
{
  return m_accessToken;
}


void KGoogleAuth::requestToken(WId windowId)
{
  AuthDialog *dlg = new AuthDialog(windowId);
  connect(dlg, SIGNAL(finished(QString, QString)),
	  this, SLOT(setTokens(QString, QString)));
  connect(dlg, SIGNAL(finished(QString, QString)),
	  dlg, SLOT(deleteLater()));
  dlg->setScopes(QStringList() << m_scope);
  dlg->show();
  dlg->auth(m_clientId, m_clientSecret);
}


void KGoogleAuth::revokeTokens()
{
  setTokens(QString(), QString());
}


void KGoogleAuth::refreshToken()
{
  QNetworkAccessManager *nam = new KIO::Integration::AccessManager(this);
  QNetworkRequest request;
  QByteArray data;

  if (m_refreshToken.isEmpty()) {
    emit error("Failed to refresh token. Please reauthenticate");
    return;
  }

  connect(nam, SIGNAL(finished(QNetworkReply*)),
	  this, SLOT(refreshTokenFinished(QNetworkReply*)));
  connect(nam, SIGNAL(finished(QNetworkReply*)),
	  nam, SLOT(deleteLater()));
  
  request.setUrl(QUrl("https://accounts.google.com/o/oauth2/token"));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

  QUrl params;
  params.addQueryItem("client_id", m_clientId);
  params.addQueryItem("client_secret", m_clientSecret);
  params.addQueryItem("refresh_token", m_refreshToken);
  params.addQueryItem("grant_type", "refresh_token");

#ifdef DEBUG_RAWDATA
  kDebug() << "Requesting token refresh: " << params.encodedQuery();
#endif
  
  nam->post(request, params.encodedQuery());
  
}

/************************ PRIVATE IMPLEMENTATIONS ********************************/

void KGoogleAuth::setTokens(const QString &accessToken, const QString &refreshToken)
{
  m_accessToken = accessToken;
  m_refreshToken = refreshToken;
  
  QMap<QString,QString> tokens;
  tokens["accessToken"] = m_accessToken;
  tokens["refreshToken"] = m_refreshToken;
  if (m_kwallet)
    m_kwallet->writeMap(m_scope, tokens);
  
  kDebug() << "emitting tokensRecevied() signal";
  
  emit tokensRecevied(m_accessToken, m_refreshToken);
}


void KGoogleAuth::refreshTokenFinished(QNetworkReply* reply)
{
  if (reply->error()) {
    emit error("Failed to refresh tokens: " + reply->readAll());
    return;
  }
  
  QByteArray data = reply->readAll();
  QJson::Parser parser;
  
#ifdef DEBUG_RAWDATA
  kDebug() << "Tokens refreshed: " << data;
#endif
  
  /* Expected structure: 
   * {
   *  "access_token": "the_access_token",
   *  "token_type":"Bearer",
   *  "expires_in":3600
   * }
   */
  QVariantMap tokens = parser.parse(data).toMap();
  
  /* Refresh token does not change */
  setTokens(tokens["access_token"].toString(), m_refreshToken);
}

void KGoogleAuth::walletOpened(const bool success)
{
  if (success) {
    if (!m_kwallet->hasFolder("Akonadi Google"))
      m_kwallet->createFolder("Akonadi Google");
  
    m_kwallet->setFolder("Akonadi Google");

    QMap<QString,QString> tokens;
    if (m_kwallet->readMap(m_scope, tokens) == 0)
      setTokens(tokens["accessToken"], tokens["refreshToken"]);
  } else {
    emit error("Failed to open wallet.");
  }
}
