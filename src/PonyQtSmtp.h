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

#ifndef PONYQTSMTP_H
#define PONYQTSMTP_H

#include <QtNetwork/QSslSocket>
#include "IPonyQtMessage.h"

class PonyQtSmtp
{
    public:
        enum EncryptionType {NONE, SSLTLS, STARTTLS};
        PonyQtSmtp();
        PonyQtSmtp(const QString & host, const EncryptionType & encType = SSLTLS, const int port = 0);
        PonyQtSmtp(const QString & host, const QString & login ,const QString & password, const EncryptionType & encType = SSLTLS, const int port = 0);
        bool sendMail(const QString from,const std::vector<QString> tos,const QString message, bool keepConnected = false);
        bool sendMail(const IPonyQtMessage * iPonym, bool keepConnected = false);
        void setHost(QString host);
        void setLogin(QString login);
        void setPassword(QString password);
        void setPort(int port);
        void setEncType(EncryptionType encType);
        // if the port was 0 the port will be changed for according to the encryption type
        void init(const QString & host, const EncryptionType & encType = SSLTLS, const int port = 0);
        // force connection close if exist
        void forceClose();
        // Destructor
        ~PonyQtSmtp();
    private:
        // if fail return -1
        int getLastResponseCode(QAbstractSocket *socket);
        EncryptionType encType;
        int port;
        QString host, login, password;
        QAbstractSocket *socket;
};

/* Because you secretly love My Little Pony
                                         __         _____   _
                                        /  \__..--""  ;-.",'/
                                       ( /  \_         `.' / `.
                                       | |    )  `;.  ,'  / \  \
                                       ( '.  /___/_j_    / ) |  )
                                       '\     /   __\``::'/__'  |
                                        |\_  (   / .-| |-.|  `-,|
                                       .| (   \ ( (WW| \W)j     '
                 ..-----,             .|'  ',  \_\_`_|  ``-.
              .-` ..::.  `,___        |,   ._:7        \__/
            ,'  .:::'':::.|.`.`-.    |:'.   \    ______.-'
          .'  .::'      '::\`.`. `-._| \ \   `"7  /
         /   ./:'  ,.--''>-'\ `.`-.(`'  `.`.._/  (
        -   :/:'  |     /    \  `.(   `.  `._/    \
        |  :::'  .'    | * \|/`. (     |`-_./      |
       .'  |||  .'     |   /|\ *`.___.-'           |
       |   |||  |      | *                         |
       |   ':|| '.    / \    *   /             \__/
       | .  |||  |.--'   |      /-,_______\       \
       |/|  |||  |     _/      /     |    |\       \
       ` )  '::. '.   /       /     |     | `--,    \
         \   |||  |   |      |      |     |   /      l
          `. |||  | _/|      |      |      | (       |
            `::||  |  |      |      |      |  \      |
               `-._|  |       \     |       \  `.___/
                       \_______)     \_______)
 */

#endif // PONYQTSMTP_H
