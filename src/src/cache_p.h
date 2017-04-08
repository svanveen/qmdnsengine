/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef QMDNSENGINE_CACHE_P_H
#define QMDNSENGINE_CACHE_P_H

#include <QDateTime>
#include <QMap>
#include <QObject>
#include <QTimer>

#include <qmdnsengine/record.h>

namespace QMdnsEngine {

class Cache;

// The record name and type make it unique
struct CacheKey {
    QByteArray name;
    quint16 type;
};

// Store the time of expiry with the record
struct CacheValue
{
    QDateTime expiry;
    Record record;
};

bool operator<(const CacheKey &key1, const CacheKey &key2);

class CachePrivate : public QObject
{
    Q_OBJECT

public:

    CachePrivate(Cache *cache);

    QTimer timer;
    QDateTime nextExpiry;
    QMap<CacheKey, CacheValue> records;

private Q_SLOTS:

    void onTimeout();

private:

    Cache *const q;
};

}

#endif // QMDNSENGINE_CACHE_P_H
