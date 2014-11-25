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

#ifndef PONYQTEMAIL_H
#define PONYQTEMAIL_H

#include <QString>
#include <vector>
#include <QFile>
#include <QByteArray>
#include "IPonyQtMessage.h"
#include <QtNetwork/QAbstractSocket>

class PonyQtMessage : public IPonyQtMessage
{
    public:
        // Constructor
        PonyQtMessage();
        // set mail sender
        void setFrom(QString from);
        // Add email address
        void addRcpt(QString to);
        // Add multiple email address
        void addRcpts(std::vector<QString> tos);
        // Add Bcc email address
        void addBcc(QString bcc);
        // Add multiple Bcc email address
        void addBccs(std::vector<QString> bccs);
        // purge Rcpt and Bcc
        void purgeDest();
        // purge Attachment
        void purgeAttachment();
        // Set subject
        void setSubject(QString subject);
        // Add file from a stream and possibility to change the Mime
        void addFile(const QByteArray &stream, const QString &name, const QString &mime = QString("application/octet-stream"));
        // Add file and possibility to change the Mime
        void addFile(QFile &file, const QString &mime = QString("application/octet-stream"));
        // Set the message body
        void setBody(QString body, const QString &mime = QString("text/plain"), const QString &charset = QString("UTF-8"));
        // return message formated for smtp
        virtual QString getMessage();
        // return vector of mail recipient for smtp
        virtual std::vector<QString> getRcpt();
        // return sender for smtp
        virtual QString getFrom();
    private:
        // Set the message body
        void sanitiseData(QString &data);
        QString subject, body, from;
        std::vector<QString> vTos;
        std::vector<QString> vBccs;
        std::vector<QString> vAttachment;
};

/* Because you secretly love My Little Pony
                                         _,,..--''.>      _
                                       .`__    .:`.-''--,'/
                                     .` /  \--..      .' /'-.
                                    /  ( /  \_  `-. ,'  /    `.
                                   ( .-| |    `-.  `-._'       \
                                   .`  ( '.  \ __`''---''''``-. \
                                   |    \   __/   __\  / `:    `'`
                                   |     \_  (   / .-| |'.|
                                   \`.     \,'\ ( (WW| \W)j
          ..---'''''---             \ `.    `-.\_\_`/   ``-.
        ,'    _----__  `'.           \  `.  <'-'`      \__/
       /   _,'    ___`-.  '.          )   `. `.-,______.-'
      | .-'/    .'   ``-`.  :________/      \  \  /
      '`  -     :    .-''>-'     \`-'  .   / |  |(
          |    :'   /   /         `-.-'J  /  |  : \
          |   .'    |  |  T:::T     .:'--'   | /   |
         .'   |     |  |  |:::|              |/    |
         |    |     |  |  \_:_/              '     |
         |    '.    | / \        /             \__/
         '.    |   .''   |      /-,_______\       \
          |    |   |   _/      /     |    |\       \
          |   .'   |  /       /     |     | `--,    \
         .'   |   :   |      |      |     |   /      l
   .__..'    ;`  :\__/|      |      |      | (       |
    `-.___.-`;  /     |      |      |      |  \      |
           .:_-'      |       \     |       \  `.___/
                       \_______)     \_______)
 */

#endif // PONYQTEMAIL_H
