#include "ReceiptFormatter.h"


static QImage composeLogos(const QImage& leftSrc, const QImage& rightSrc)
{
    const int paperWidth = 576;

    QImage left  = leftSrc.convertToFormat(QImage::Format_Mono);
    QImage right = rightSrc.convertToFormat(QImage::Format_Mono);

    int height = qMax(left.height(), right.height());

    QImage result(paperWidth, height, QImage::Format_Mono);
    result.fill(1);
    //qDebug() << "IMAGE:" << result.width() << "x" << result.height();
    QPainter p(&result);

    int leftY  = (height - left.height()) / 2;
    int rightY = (height - right.height()) / 2;

    // Logo izquierdo
    p.drawImage(0, leftY, left);

    // Logo derecho
    p.drawImage(paperWidth - right.width(), rightY, right);

    p.end();

    return result;
}

static QImage trimTopWhite(const QImage& src)
{
    int top = 0;

    for (int y = 0; y < src.height(); ++y) {
        for (int x = 0; x < src.width(); ++x) {
            if (qGray(src.pixel(x, y)) == 0) {
                goto found;
            }
        }
        top++;
    }

found:
    if (top == 0)
        return src;

    return src.copy(0, top, src.width(), src.height() - top);
}


QByteArray ReceiptFormatter::format()
{
    EscPosBuilder b;

    b.init()
        .codePageCP858();                 // SOLO una vez

    printHeader(b);           // COMÚN
    printBody(b);             // PARTICULAR

    if (hasFooter()) {
        printFooter(b);
    }

    b.cut();

    return b.build();
}

void ReceiptFormatter::printHeader(EscPosBuilder& b)
{
    auto& cfg = PrintConfig::instance();

    QImage logoLeft(cfg.logoLeftPath());
    QImage logoRight(cfg.logoLeftPath());

    QImage header = composeLogos(logoLeft, logoRight);
    header = trimTopWhite(header);

    b.image(header);

    b.center()
        .bold(true)
        .font(EscPosFont::FontB)
        .textSize(2, 2)
        .text("PARQUEADERO")
        .text(cfg.companyName())
        .textNormal()
        .bold(false)
        .fontNormal()
        .line(0)
        .smallText(cfg.address())
        .smallText("Telefono " + cfg.phone())
        .smallText("NIT: " + cfg.nit())
        .line(0);
}

void ReceiptFormatter::printFooter(EscPosBuilder& b)
{
    auto& cfg = PrintConfig::instance();

    b.center()
        .bold(true)
        .text("REGLAMENTO")
        .bold(false)
        .smallText(cfg.footerLines())
        .line(3);
        //.left();

    //for (const auto& line : cfg.footerLines())
    //    b.smallText(line).line(0);

        //.line(5);
}
