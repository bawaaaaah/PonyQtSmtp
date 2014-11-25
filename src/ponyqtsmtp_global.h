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

#ifndef PONYQTSMTP_GLOBAL_H
#define PONYQTSMTP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PONYQTSMTP_LIBRARY)
#  define PONYQTSMTPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PONYQTSMTPSHARED_EXPORT Q_DECL_IMPORT
#endif

/* Because you secretly love My Little Pony
                                                  .-'''-.
                                         __     /`       `. .''', .--.
                                     ,-'`__`.  /           Y     X    `.
                                   .`   /  \ `Y                  U      |
                                  /    ( /  \_ ...---..      .--.       |
                                 (     | |    `        '.  .'    `.     j
                                 (     ( '.  \ _____    _v`       |    / ,;
                                  \     \   __/   __\  / `:       |   /.'/
                                   \,..  \_  (   / .-| |'.|        \ _.-'
               _----_             /`   `   ``.\ ( (WW| \W)j
             ,'      `-.         :        _  ; \_\_`/   ``-.
            /           `'.      |      .' `x          \__/
           (               \     l      '--' `.-,______.-'
           (     <:''-.    \ ____`.           \   /
            \      `.   `>-'`       ``>-        )(
       ,'``'.;       \  /   ( )      :         /  \
     ,'      '        )|     S       `.     <:'    |
    /                 )| ( ) S ( )     `'--.  `)   |
   (         ..---.  / |  S     S       `-.._-'    |
    \       (      `X / \ S     S/             \__/
     `.      `-..-'` )   |      /-,_______\       \
    .'               ) _/      /     |    |\       \
    |     __        / /       /     |     | `--,    \
    '.  .'  )     .'  |      |      |     |   /      l
      `x_.-`  _.-`\__/|      |      |      | (       |
   _  (.    <:        |      |      |      |  \      |
   \`-._`>    )       |       \     |       \  `.___/
    `-.___..-'         \_______)     \_______)
 */

#endif // PONYQTSMTP_GLOBAL_H
