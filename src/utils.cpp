/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Alexander Chumakov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "utils.h"

#include <QDebug>

void Utils::hexDump(const char *pData)
{
  const int length = strlen (pData);
  hexDump (reinterpret_cast<const unsigned char *>(pData), length);
}

void Utils::hexDump(const QByteArray &data)
{
  hexDump(reinterpret_cast<const unsigned char *>(data.data()), data.length());
}

void Utils::hexDump(const unsigned char *pData, int length)
{
  char buffer[20];
  QDebug debug = qDebug();
  debug.nospace();
  for (int i = 0; i < length; ++i) {
    if (!(i % 16)) {
      snprintf(buffer, 20, "%4.4x: ", i);
      debug << buffer;
    }
    char byte = pData[i];
    char lowByte = (0xFU&byte) + '0';
    char highByte = (0xFU&(byte>>4)) + '0';
    if (lowByte > '9') {
      // 0x0A => 'A', etc...
      lowByte += 'A' - ('9' + 1);
    }
    if (highByte > '9') {
      // 0x0A => 'A', etc...
      highByte += 'A' - ('9' + 1);
    }
    if (byte < 32 || byte >= 127) {
      byte = '.';
    }
    debug << highByte << lowByte << "(" << byte << ") ";
    if (i%16 == 15) {
      debug << "\n";
    }
  }
  debug << "\n";
  debug.space();
}
