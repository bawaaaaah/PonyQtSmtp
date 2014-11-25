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

#ifndef IPONYQTEMAIL_H
#define IPONYQTEMAIL_H

#include <QString>
#include <vector>
#include <QFile>
#include <QByteArray>

class IPonyQtMessage
{
    public:
        // return message formated for smtp
        virtual QString getMessage() = 0;
        // return vector of mail recipient for smtp
        virtual std::vector<QString> getRcpt() = 0;
        // return sender for smtp
        virtual QString getFrom() = 0;
        // destructor
        virtual ~IPonyQtMessage(){}
};

/* Because you secretly love My Little Pony
                                              ,'/
                                             . / ___
                                    ___/\   / /'`_  `'.
                       __  _     .-' :v  :u/ /-'` \   )
                  .-'``  \` \  .'.') ) /\ / /      :  |
               .'`  .--.  ) .)/ / /-'__\// /       |  |
            .'` .-'`  .| .'.|: @_-'`` \  \/\..--.  |  |     ___
          ,' .'`      |' | |'| ( /.    '-.__\    ) (  `--''`'` `.
        .'.-`         | .| | | \  ) \__.  |      |  `---``      )
      .' (_.'         | |'.| | ('` ,_     `.     :       .--.   /
    .'    /   .       | | |' (  \    `\-.-'       \  .-'`    |  \
   -  .  (_.-'        | | |   \ |\     \    __     ``        |   `''--.,
 .` .'  .   /  /      | | :    \| `-._  \.'`  '.       .--.  `-..-'``'. )
 '-'/  /   (  /       | : (     |'-,  `-.)\     \    .'    )       __ ) )
   /  /    /``(  .'   ( (  '..-':'  `-,  A )     \_.'      (_ .---:  )| /
  /  /    /    '`'  .  \ '---''`       \ V )`-.            .-`     '.(((
 '  /    /    /  `'`(_. `''    .'`      )-'    `-..___..-'`          \ ``.'
(  /    /    /   /  /  / / ,'-`      |  | \                           ''`
 '`/   /    /   /  /  /.''`.'        |  :  \
  /   /    /   /  /`-'    /  ..---.  |  '.  \
 (   //   /   /(_/     _ /. . ,    )/|.  '.  \
  `-'(   /   /     .-'` ( -(_)-   /  '|   '. (\
      `-'`--'    /`      \' ' ` .'    |.  ('.` \  ,.---.
                (_        `--''`````\ '| .-` \.-'`_     \
                 /       ___        /  '..''``''`` `\    .
                (``''''``   \       `--'`            \   |       ..--.
                 \          (__,..-'`        ___     (   '\   .-`__\  \  .--.
                  '-..----..,          ,.-'``   `-.   \__.'''` ,'  ``--``    '.'
                             \     .-'`           __     .--.-''.     .-'``''`
                              \.-'`            .-'  `\`'`.'`     \_.-'
                               '.__________.-'`       `'`
*/

#endif // IPONYQTEMAIL_H
