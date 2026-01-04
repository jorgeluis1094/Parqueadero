#include "PrintDevice.h"

PrintDevice::PrintDevice(std::unique_ptr<ITransport> transport)
    : transport_(std::move(transport)) {}

bool PrintDevice::connect() {
    return transport_->open();
}

void PrintDevice::disconnect() {
    transport_->close();
}

bool PrintDevice::send(const QByteArray& data) {
    return transport_->write(data);
}
