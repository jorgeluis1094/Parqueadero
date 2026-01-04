#ifndef PRINTCONFIG_H
#define PRINTCONFIG_H

#include <QString>
#include <QStringList>

class PrintConfig {
public:
    static PrintConfig& instance();

    bool load(const QString& basePath);

    // datos empresa
    QString companyName() const;
    QString address() const;
    QString nit() const;
    QString owner() const;
    QString phone() const;

    // imágenes
    QString logoLeftPath() const;
    QString logoRightPath() const;

    // textos largos
    QString footerLines() const;

private:
    PrintConfig() = default;

    QString companyName_;
    QString address_;
    QString nit_;
    QString owner_;
    QString phone_;

    QString logoLeft_;
    QString logoRight_;

    QString footerLines_;
};

#endif // PRINTCONFIG_H
