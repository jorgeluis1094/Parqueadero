#ifndef USBLPTRANSPORT_H
#define USBLPTRANSPORT_H

//#pragma once
#include "ITransport.h"
#include <QFile>

class UsbLpTransport : public ITransport {
public:
    explicit UsbLpTransport(const QString& devicePath);

    bool open() override;
    void close() override;
    bool write(const QByteArray& data) override;

private:
    QFile device_;
};


#endif // USBLPTRANSPORT_H
