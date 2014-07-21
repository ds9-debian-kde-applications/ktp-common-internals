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

#ifndef KTP_PROXY_OTR_HANDLER_HEADER
#define KTP_PROXY_OTR_HANDLER_HEADER

#include "otr-message.h"

#include <QSharedPointer>

namespace OTR
{
    struct SessionContext
    {
        const QString accountId;
        const QString accountName;
        const QString recipientName;
        const QString protocol;
    };

    class Handler : public QObject
    {
        Q_OBJECT

        public:
            virtual ~Handler();
            virtual const SessionContext& context() const = 0;

            virtual void injectMessage(const Message &message) = 0;
            virtual void handleSmpEvent() = 0;
            virtual void handleMsgEvent() = 0;
            virtual void handleError() = 0;
            /**
             * State of the recipient
             * 1 - logged in
             * 0 - not logged in
             * -1 - not sure if logged in
             */
            virtual int recipientStatus() = 0;
            virtual void goneSecure() = 0;
            virtual void goneInsecure() = 0;

        Q_SIGNALS:
            void invalidated(SessionContext *context);

    };

    typedef QSharedPointer<Handler> HandlerPtr;
}

#endif
