#ifndef ITRANSPORT_H
#define ITRANSPORT_H

//#pragma once
#include <QByteArray>

class ITransport {
public:
    virtual ~ITransport() = default;
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual bool write(const QByteArray& data) = 0;
};



#endif // ITRANSPORT_H
