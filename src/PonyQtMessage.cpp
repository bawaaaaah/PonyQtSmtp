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

#include "PonyQtMessage.h"
#include <QFileInfo>
#include <QDebug>
#include <QUuid>
#include <QRegExp>

// Constructor. ho! you know that and you think is a useless comment... Ok you're right.
PonyQtMessage::PonyQtMessage() : subject(""), body(""), from(""),vTos(0), vBccs(0), vAttachment(0)
{
}

// set mail sender
void PonyQtMessage::setFrom(QString from)
{
    this->from = from;
}

// Add email address
void PonyQtMessage::addRcpt(QString to)
{
    vTos.push_back(to);
}

// Add  multiple email address
void PonyQtMessage::addRcpts(std::vector<QString> tos)
{
    vTos.insert(vTos.end(),tos.begin(),tos.end());
}

// Add Bcc email address
void PonyQtMessage::addBcc(QString bcc)
{
    vBccs.push_back(bcc);
}

// Add multiple Bcc email address
void PonyQtMessage::addBccs(std::vector<QString> bccs)
{
    vBccs.insert(vBccs.end(),bccs.begin(),bccs.end());
}

// purge Rcpt and Bcc
void PonyQtMessage::purgeDest()
{
    vBccs.clear();
    vTos.clear();
}

// purge Attachment
void PonyQtMessage::purgeAttachment()
{
    vAttachment.clear();
}

// Set subject
void PonyQtMessage::setSubject(QString subject)
{
    subject.replace("\r","");
    subject.replace("\n","");
    this->subject = subject;
}

// Add file from a stream and possibility to change the Mime
void PonyQtMessage::addFile(const QByteArray &stream, const QString &name, const QString &mime)
{
    // get Filename
    QString fileName(QFileInfo(name).fileName());
    // convert stream to base 64 and generate header for the file
    vAttachment.push_back("Content-Type: "+mime+"; name=\""+fileName+"\"\r\nContent-Transfer-Encoding: base64\r\nContent-Disposition: attachment; filename=\""+fileName+"\"\r\n\r\n"+stream.toBase64());
}

// Add file and possibility to change the Mime
void PonyQtMessage::addFile(QFile &file, const QString &mime)
{
    // Open file or reset it if already open
    if(!file.isOpen())
        file.open(QIODevice::ReadOnly);
    else
        file.reset();
    // Use PonyQtMessage::addFile function with QByteArray for uniform function and reuse of code
    addFile(QByteArray(file.readAll()), file.fileName(), mime);
}

// Set the message body
void PonyQtMessage::setBody(QString body, const QString &mime, const QString &charset)
{
    // Sanitisation of data
    sanitiseData(body);
    this->body = "Content-Type: "+mime+"; charset="+charset+"\r\n\r\n"+ body;
}

QString PonyQtMessage::getMessage()
{
    // message vars used to sotck body and attachment and rcpt
    // uuid stock uuid used to stock boundary based on a uuid
    QString message("");

    // Generate the base message
    message =   "From: " + from + "\r\n"+
                "MIME-Version: 1.0\r\n"+
                "Subject: " + subject + "\r\n" ;
    for(unsigned int i =0; i < vTos.size(); i++)
        message += "To: " + vTos[i] + "\r\n";

    // Construction of mail without attachment
    if(vAttachment.size() == 0)
    {
        message +=  body;
    }
    else
    {
        // construction of mail with attachment
        QString uuid("");
        QRegExp regexUuid("");
        bool nextUuid(false);
        // while uuid is in body or attachment regenerate uuid
        while(1)
        {
            // generate new uuid
            uuid = QUuid().createUuid().toString();
            regexUuid.setPattern(uuid);

            // check uuid is present in body
            if(regexUuid.indexIn(body)!=-1)
                continue;

            // reinit nextUuid to false
            nextUuid = false;
            // check uuid is present in attachment
            for(unsigned int i =0; i < vAttachment.size() && !nextUuid; i++)
                if(regexUuid.indexIn(vAttachment[i])!=-1)
                    nextUuid = true;
            // if nextUuid is true we have the uuid present in attachment
            if (nextUuid)
                continue;

            // end of while beacause no uuid found in body and attachment (uuid can be used as boundary)
            break;
        }
        message += "Content-Type: multipart/mixed; Boundary=\"" + uuid + "\"\r\n\r\n--" + uuid + "\r\n" + body + "\r\n\r\n";
        for(unsigned int i =0; i < vAttachment.size(); i++)
            message += "--" + uuid + "\r\n" + vAttachment[i] + "\r\n\r\n";
        message += "--" + uuid + "--";
    }

    return message;
}

std::vector<QString> PonyQtMessage::getRcpt()
{
    std::vector<QString> tmp(vTos);
    tmp.insert(tmp.end(),vBccs.begin(),vBccs.end());
    return tmp;
}

QString PonyQtMessage::getFrom()
{
    return from;
}

// TODO: Add encoding special char etc...
void PonyQtMessage::sanitiseData(QString &data)
{
    data.replace(".\r\n",".\n\r");
}

/* Because you secretly love My Little Pony
                                                .....-----...
                                         __  .-`             `.
                                        /  \`             .:'--:.
                                       ( /  \               `-.__..-;
                                       | |   `-..__  .,            -
                                       ( '.  \ _____\ )`-._     _-`
                                       '\   __/   __\' / `:``''`
                                       .|\_  (   / .-| |'.|
                                       |' / ,'\ ( (WW| \W)j
                                      .|  |    \_\_`/   ``-.
            .--''''````-.             |'  l            \__/
           /             `.           |    `.  -,______.-'
          /                `.________.|      `.   /
         (         ,.--''>-',:       |'        | (
         |        |     /   (_)     .|        ,'),-``''-.
         |       .'    | ,;         |'       / ,'        `.
        .|       |.    | (_)  ;,    '.      (.(            :
        |'       '|    |     (_)      `'---'`  `.       `:`;
        |         '.  / \        /           `:. ;        ':
        |.          `'   |      /-,_______\   ' `     .-;  |
        '|            \_/      /     |    |\   `----'`.' .'
         |             )      /     |     | `--,    \`''`
         '.           /      |      |     |   /      l
           `--_____--'|      |      |      | (       |
      `:._.`       '. |      |      |      |  \      |
       '        .-.  )|       \     |       \  `.___/
        `---;    ) )'  \_______)     \_______)
          .:___-'
 */
