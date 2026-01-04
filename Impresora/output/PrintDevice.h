#ifndef PRINTDEVICE_H
#define PRINTDEVICE_H

//#pragma once
#include <memory>
#include "Impresora/transport/ITransport.h"

class PrintDevice {
public:
    explicit PrintDevice(std::unique_ptr<ITransport> transport);

    bool connect();
    void disconnect();
    bool send(const QByteArray& data);

private:
    std::unique_ptr<ITransport> transport_;
};


#endif // PRINTDEVICE_H
