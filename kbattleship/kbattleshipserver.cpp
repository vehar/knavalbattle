/***************************************************************************
                            kbattleshipserver.cpp
                             -------------------
    Developers: (c) 2000-2001 Nikolas Zimmermann <wildfox@kde.org>
                (c) 2000-2001 Daniel Molkentin <molkentin@kde.org>

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <qtextstream.h>

#include "kbattleshipserver.moc"

KBattleshipServer::KBattleshipServer(int port) : QServerSocket(port)
{
    internalPort = port;
    serverSocket = 0;
    allowWrite();
}

KBattleshipServer::~KBattleshipServer()
{
}

void KBattleshipServer::start()
{
    if(!ok())
    {
	KMessageBox::error(0L, i18n("Failed to bind to local port \"%1\"\n\nPlease check if another KBattleship server instance\nis running or another application uses this port.").arg(internalPort));
	emit serverFailure();
    }
}

void KBattleshipServer::newConnection(int socket)
{
    if(serverSocket == 0)
    {
	serverSocket = new QSocket(this);
	connect(serverSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
	connect(serverSocket, SIGNAL(connectionClosed()), this, SLOT(discardClient()));
	serverSocket->setSocket(socket);
	emit newConnect();
    }
}

void KBattleshipServer::readClient()
{
    int len = serverSocket->bytesAvailable();
    char *buf = new char[len + 1];
    serverSocket->readBlock(buf, len);
    buf[len] = 0;
    KMessage *msg = new KMessage();
    QString buffer = QString::fromUtf8(buf);
    msg->setDataStream(buffer);
    emit newMessage(msg);
    delete msg;
    delete []buf;
}

void KBattleshipServer::sendMessage(KMessage *msg)
{
    if(writeable)
    {
	QTextStream post(serverSocket);
        post.setEncoding(QTextStream::UnicodeUTF8);
	post << msg->returnSendStream();
	emit wroteToClient();
	if(msg->enemyReady())
	{
	    forbidWrite();
	    emit senemylist(true);
	}
	delete msg;
    }
}

void KBattleshipServer::discardClient()
{
    delete serverSocket;
    serverSocket = 0;
    emit endConnect();
}
