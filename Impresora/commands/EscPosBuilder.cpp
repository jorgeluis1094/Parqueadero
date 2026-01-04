#include "EscPosBuilder.h"

EscPosBuilder& EscPosBuilder::init() {
    buffer_.clear();
    buffer_.append("\x1B\x40");
    return *this;
}

EscPosBuilder& EscPosBuilder::left()
{
    buffer_.append('\x1B');
    buffer_.append('\x61');
    buffer_.append('\x00');   // 0 = izquierda
    return *this;
}

EscPosBuilder& EscPosBuilder::center() {
    buffer_.append("\x1B\x61\x01");
    return *this;
}

EscPosBuilder& EscPosBuilder::right()
{
    buffer_.append('\x1B');
    buffer_.append('\x61');
    buffer_.append('\x02');   // 2 = derecha
    return *this;
}

EscPosBuilder& EscPosBuilder::bold(bool on)
{
    buffer_.append('\x1B'); // ESC
    buffer_.append('\x45'); // E
    buffer_.append(on ? '\x01' : '\x00');
    return *this;
}

static QByteArray toPrinterEncoding(const QString &text)
{
    // Convertir a CP850 (Latin-1 extended)
    QStringEncoder encoder("CP850");
    return encoder.encode(text);
}

EscPosBuilder& EscPosBuilder::text(const QString& txt)
{
    buffer_.append(toPrinterEncoding(txt));
    buffer_.append('\n');
    return *this;
}

EscPosBuilder& EscPosBuilder::textSize(int width, int height)
{
    // límites seguros
    width  = qBound(1, width, 4);
    height = qBound(1, height, 4);

    uchar n = ((width - 1) << 4) | (height - 1);

    buffer_.append('\x1D');   // GS
    buffer_.append('\x21');   // !
    buffer_.append(n);

    return *this;
}

EscPosBuilder& EscPosBuilder::textNormal()
{
    buffer_.append('\x1D');
    buffer_.append('\x21');
    buffer_.append('\x00');   // 1x1

    buffer_.append('\x1B');
    buffer_.append('\x21');
    buffer_.append('\x00');

    return *this;
}

EscPosBuilder& EscPosBuilder::font(EscPosFont f)
{
    buffer_.append('\x1B');   // ESC
    buffer_.append('\x4D');   // M
    buffer_.append(static_cast<char>(f));
    return *this;
}

EscPosBuilder& EscPosBuilder::fontNormal()
{
    return font(EscPosFont::FontA);
}

EscPosBuilder& EscPosBuilder::line(int n) {
    for (int i = 0 ; i <= n; i++)
        buffer_.append('\n');
    return *this;
}

EscPosBuilder& EscPosBuilder::cut() {
    buffer_.append("\x1D\x56\x01");
    return *this;
}


EscPosBuilder& EscPosBuilder::barcode(const QString &data, int type, int height, int width, int textPosition) {
    // 1. Configura altura
    buffer_.append(0x1D); // GS
    buffer_.append('h');  // h
    buffer_.append(static_cast<char>(height));

    // 2. Configura ancho del módulo
    buffer_.append(0x1D); // GS
    buffer_.append('w');  // w
    buffer_.append(static_cast<char>(width));

    // 3. Posición del texto
    buffer_.append(0x1D); // GS
    buffer_.append('H');  // H
    buffer_.append(static_cast<char>(textPosition));

    // 4. Imprimir el código de barras
    buffer_.append(0x1D);       // GS
    buffer_.append('k');        // k
    buffer_.append(static_cast<char>(type));      // tipo
    buffer_.append(static_cast<char>(data.size())); // longitud
    buffer_.append(data.toUtf8());               // datos

    return *this;
}

EscPosBuilder& EscPosBuilder::image(const QImage& img)
{

    QImage image = img.convertToFormat(QImage::Format_Mono);

    int width = image.width();
    int height = image.height();

    buffer_.append("\x1B\x33\x01"); // ESC 3 0

    for (int y = 0; y < height; y += 24) {

        buffer_.append('\x1B');
        buffer_.append('*');
        buffer_.append('\x21'); // 24-dot double density

        buffer_.append(char(width & 0xFF));
        buffer_.append(char((width >> 8) & 0xFF));

        for (int x = 0; x < width; ++x) {
            for (int k = 0; k < 3; ++k) {
                uchar slice = 0;
                for (int b = 0; b < 8; ++b) {
                    int yy = y + k * 8 + b;
                    if (yy < height) {
                        bool black = (qGray(image.pixel(x, yy)) == 0);
                        if (black)
                            slice |= (1 << (7 - b));
                    }
                }
                buffer_.append(slice);
            }
        }
    }
    buffer_.append("\x1B\x32"); // ESC 2

    return *this;
}

EscPosBuilder& EscPosBuilder::smallText(const QString& text)
{
    font(EscPosFont::FontB);
    textNormal();
    this->text(text);
    fontNormal();

    return *this;
}

EscPosBuilder& EscPosBuilder::codePageCP850()
{
    buffer_.append("\x1B\x74\x02"); // ESC t 2 → CP850
    return *this;
}

EscPosBuilder& EscPosBuilder::codePageCP858()
{
    buffer_.append("\x1B\x74\x13"); // ESC t 19
    return *this;
}

QByteArray EscPosBuilder::build() const {
    return buffer_;
}

