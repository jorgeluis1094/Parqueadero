#ifndef ESCPOSBUILDER_H
#define ESCPOSBUILDER_H

//#pragma once
#include <QByteArray>
#include <QString>
#include <QImage>
#include <QtMath>
#include <QStringEncoder>

enum class EscPosFont {
    FontA = 0,
    FontB = 1,
    FontC = 2
};

class EscPosBuilder {
public:

    EscPosBuilder& init();
    EscPosBuilder& left();
    EscPosBuilder& center();
    EscPosBuilder& right();
    EscPosBuilder& bold(bool on);
    EscPosBuilder& text(const QString& txt);
    EscPosBuilder& textSize(int width, int height);
    EscPosBuilder& textNormal();
    EscPosBuilder& font(EscPosFont f);
    EscPosBuilder& fontNormal(); // alias de FontA
    EscPosBuilder& line(int n = 1);
    EscPosBuilder& cut();
    EscPosBuilder& barcode(const QString &data, int type, int height, int width, int textPosition);
    EscPosBuilder& image(const QImage& img);

    EscPosBuilder& smallText(const QString& text);

    //QByteArray toPrinterEncoding(const QString& text);
    EscPosBuilder& codePageCP858();
    EscPosBuilder& codePageCP850();

    QByteArray build() const;

private:
    QByteArray buffer_;
};

#endif // ESCPOSBUILDER_H
