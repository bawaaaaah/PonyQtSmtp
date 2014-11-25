/*
   Copyright 2014 Samuel Lemaitre

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#define sendMessage(a, b)   do{\
                    a->write(QString(b).toUtf8() + "\r\n");\
                    if(!a->waitForBytesWritten())\
                    return false;\
                } while(0)

#define respMessage(a, b)   do{\
                    if (getLastResponseCode(a) != b){\
                        a->close();\
                        delete a;\
                        socket = NULL;\
                        return false;\
                    } \
            }while(0)

#include "PonyQtSmtp.h"

/*EncryptionType encType;
  int port;
  QString host, login, password;*/

PonyQtSmtp::PonyQtSmtp() : encType(NONE), port(0), host(""), login(""), password("")
{
    socket = NULL;
}

// if the port was 0 the constructor change the port according to the encryption type
PonyQtSmtp::PonyQtSmtp(const QString & host, const EncryptionType & encType, const int port) : encType(NONE), port(0), host(""), login(""), password("")
{
    init(host, encType, port);
    socket = NULL;
}

PonyQtSmtp::PonyQtSmtp(const QString & host,const QString & login ,const QString & password, const EncryptionType & encType, const int port) : encType(NONE), port(0), host(""), login(login), password(password)
{
    init(host, encType, port);
    socket = NULL;
}

void PonyQtSmtp::setHost(QString host)
{
    this->host = host;
}

void PonyQtSmtp::setLogin(QString login)
{
    this->login = login;
}

void PonyQtSmtp::setPassword(QString password)
{
    this->password = password;
}

void PonyQtSmtp::setPort(int port)
{
    this->port = port;
}

void PonyQtSmtp::setEncType(EncryptionType encType)
{
    this->encType = encType;
}

void PonyQtSmtp::init(const QString & host, const EncryptionType & encType, const int port)
{
    setHost(host);
    setEncType(encType);
    if(port)
        setPort(port);
    else
        // if no encryption use default port 25 else it's an encrypted connection we use default ssmtp for STARTTLS port 587 and finaly 465 for SSLTLS
        setPort((encType == NONE)?25:((encType == STARTTLS)?587:465));
}

bool PonyQtSmtp::sendMail(const IPonyQtMessage * iPonym, bool keepConnected)
{
    return sendMail(((IPonyQtMessage *)iPonym)->getFrom(), ((IPonyQtMessage *)iPonym)->getRcpt(), ((IPonyQtMessage *)iPonym)->getMessage(), keepConnected);
}

bool PonyQtSmtp::sendMail(const QString from, const std::vector<QString> tos, const QString message, bool keepConnected)
{
    /**************
     * CONNECTION *
     **************/
    if (socket == NULL)
    {
        // initialise a new socket according to the encryption type for the connection if no socket initialised before
        if(encType == NONE)
            socket = new QTcpSocket;
        else
            socket = new QSslSocket;

        // initialise the connection depending of encryption type
        if(encType != SSLTLS)
            socket->connectToHost(host,port);
        else
            ((QSslSocket*)socket)->connectToHostEncrypted(host,port);

        // wait the connection if is timeout return false else process continue
        if (!socket->waitForConnected())
            return false;

        // Check if server is OK
        respMessage(socket, 220);

        //send HELO
        sendMessage(socket, ("HELO "+host));
        respMessage(socket, 250);

        // if startls session
        if (encType == STARTTLS)
        {
            // Start encrypted session
            sendMessage(socket, "STARTTLS");
            respMessage(socket, 220);
            ((QSslSocket*)socket)->startClientEncryption();

            if(!((QSslSocket*)socket)->waitForEncrypted())
                return false;

            //send HELO
            sendMessage(socket, ("HELO "+host));
            respMessage(socket, 250);
        }

        // Login if we have password and username
        if(!login.isEmpty() || !password.isEmpty())
        {
            sendMessage(socket, ("AUTH PLAIN "+QByteArray().append(char(0)+login+char(0)+password).toBase64()));
            int auth = getLastResponseCode(socket);
            if (auth != 235){
                // if is not "Unrecognized authentication type"
                if(auth != 504)
                {
                    socket->close();
                    delete socket;
                    return false;
                }
                // else try "AUTH LOGIN" method
                sendMessage(socket, "AUTH LOGIN");
                respMessage(socket, 334);

                sendMessage(socket, QByteArray().append(login).toBase64());
                respMessage(socket, 334);

                sendMessage(socket, QByteArray().append(password).toBase64());
                respMessage(socket, 235);
            }
        }
    }
    else
    {
        // we reset the session
        sendMessage(socket, ("RSET"));
        respMessage(socket, 250);
    }
    /*************
     * CONNECTED *
     *************/

    /****************
     * SENDING MAIL *
     ****************/

    sendMessage(socket, ("MAIL FROM: "+from));
    respMessage(socket, 250);

    for(unsigned int i =0; i < tos.size(); i++)
    {
        sendMessage(socket, ("RCPT TO: "+tos[i]));
        respMessage(socket, 250);
    }

    sendMessage(socket, "DATA");
    respMessage(socket, 354);

    sendMessage(socket, message);
    sendMessage(socket, ("."));
    respMessage(socket, 250);

    /*************
     * MAIL SENT *
     *************/

    // close connection and remove socket element from memory if we don't keep open the connection
    if(!keepConnected)
    {
        forceClose();
    }

    return true;
}

//if fail return -1
int PonyQtSmtp::getLastResponseCode(QAbstractSocket *socket)
{
    if(!socket->waitForReadyRead())
        return -1;
    // error code for smtp contain are integer and was greater than 99 and lower than 1000
    bool ok(false);
    int respCode(-1), tmp(-1);
    QString pouet("");
    while (socket->canReadLine())
    {
        pouet = socket->readLine();
        qDebug()<<pouet;
        tmp = pouet.left(3).toInt(&ok);
        if(ok)
            respCode = tmp;
    }

    return respCode;
}

void PonyQtSmtp::forceClose()
{
    if(socket != NULL)
    {
        socket->write(QString("QUIT").toUtf8() + "\r\n");
        socket->waitForBytesWritten();
        socket->waitForReadyRead();
        socket->close();
        delete socket;
        socket = NULL;
    }
}

PonyQtSmtp::~PonyQtSmtp()
{
    forceClose();
}

/* Because you secretly love My Little Pony
                                         __         __----__
                                        /  \__..--'' `-__-__''-_
                                       ( /  \    ``--,,  `-.''''`
                                       | |   `-..__  .,\    `.
                         ___           ( '.  \ _____\ )`-_    `.
                  ___   (   `.         '\   __/   __\' / `:-.._ \
                 (   `-. `.   `.       .|\_  (   / .-| |'.|    ``'
                  `-.   `-.`.   `.     |' ( ,'\ ( (WW| \W)j
          ..---'''':-`.    `.\   _\   .||  ',  \_\_`/   ``-.
        ,'      .'` .'_`-,   `  (  |  |''.   `.        \__/
       /   _  .'  :' ( ```    __ \  \ |   \ ._:7,______.-'
      | .-'/  : .'  .-`-._   (  `.\  '':   `-\    /
      '`  /  :' : .: .-''>`-. `-. `   | '.    |  (
         -  .' :' : /   / _( `_: `_:. `.  `;.  \  \
         |  | .' : /|  | (___(   (      \   )\  ;  |
        .' .' | | | `. |   \\\`---:.__-'') /  )/   |
        |  |  | | |  | |   ///           |/   '    |
       .' .'  '.'.`; |/ \  /     /             \__/
       |  |    | | |.|   |      /-,_______\       \
      /  / )   | | '|' _/      /     |    |\       \
    .:.-' .'  .' |   )/       /     |     | `--,    \
         /    |  |  / |      |      |     |   /      l
    .__.'    /`  :|/_/|      |      |      | (       |
    `-.___.-`;  / '   |      |      |      |  \      |
           .:_-'      |       \     |       \  `.___/
                       \_______)     \_______)
 */
