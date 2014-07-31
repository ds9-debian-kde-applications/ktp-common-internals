/***************************************************************************
 *   Copyright (C) 2014 by Marcin Ziemiński <zieminn@gmail.com>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2.1 of the License, or   *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#ifndef KTP_PROXY_PROXY_SERVICE_ADAPTEE_HEADER
#define KTP_PROXY_PROXY_SERVICE_ADAPTEE_HEADER

#include <QDBusObjectPath>
#include <QDBusConnection>

#include "svc-proxy-service.h"

namespace Tp
{
namespace Service
{
    class ProxyServiceAdaptor;
}
}
class ProxyService;

class ProxyServiceAdaptee : public QObject
{
    Q_OBJECT

        Q_PROPERTY(uint policySettings READ policy WRITE setPolicy)

    public:
        ProxyServiceAdaptee(ProxyService *ps, const QDBusConnection &dbusConnection);
        ~ProxyServiceAdaptee();

        uint policy() const;
        void setPolicy(uint otrPolicy);

    Q_SIGNALS:
        void proxyConnected(const QDBusObjectPath &proxyPath);
        void proxyDisconnected(const QDBusObjectPath &proxyPath);
        void keyGenerationStarted(const QDBusObjectPath &accountPath);
        void keyGenerationFinished(const QDBusObjectPath &accountPath, bool error);

    public Q_SLOTS:
        void onProxyConnected(const QDBusObjectPath &proxyPath);
        void onProxyDisconnected(const QDBusObjectPath &proxyPath);
        void generatePrivateKey(const QDBusObjectPath &accountPath,
                const Tp::Service::ProxyServiceAdaptor::GeneratePrivateKeyContextPtr &context);
        void getFingerprintForAccount(QDBusObjectPath accountPath,
                const Tp::Service::ProxyServiceAdaptor::GetFingerprintForAccountContextPtr &context);
    private Q_SLOTS:
        void onKeyGenerationStarted(const QString &accountId);
        void onKeyGenerationFinished(const QString &accountId, bool error);

    private:
        Tp::Service::ProxyServiceAdaptor *adaptor;
        ProxyService *ps;
};

#endif
