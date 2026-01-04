#include "UsbLpTransport.h"

UsbLpTransport::UsbLpTransport(const QString& devicePath)
    : device_(devicePath) {}

bool UsbLpTransport::open() {
    return device_.open(QIODevice::WriteOnly);
}

void UsbLpTransport::close() {
    if (device_.isOpen())
        device_.close();
}

bool UsbLpTransport::write(const QByteArray& data) {
    if (!device_.isOpen())
        return false;

    return device_.write(data) == data.size();
}
