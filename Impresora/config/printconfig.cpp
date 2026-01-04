#include "Impresora/config/printconfig.h"

#include <QSettings>
#include <QFile>
#include <QTextStream>

PrintConfig& PrintConfig::instance()
{
    static PrintConfig cfg;
    return cfg;
}

bool PrintConfig::load(const QString& basePath)
{
    QSettings s(basePath + "/parking.conf", QSettings::IniFormat);

    companyName_ = s.value("Company/name").toString();
    address_     = s.value("Company/address").toString();
    nit_         = s.value("Company/nit").toString();
    owner_       = s.value("Company/owner").toString();
    phone_       = s.value("Company/phone").toString();

    logoLeft_  = s.value("Images/logo_left").toString();
    logoRight_ = s.value("Images/logo_right").toString();

    footerLines_ = s.value("Normas/Reglamento").toString();

    /*QFile f(basePath + "/ReglamentoParqueadero.txt");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(&f);
        while (!ts.atEnd())
            footerLines_ << ts.readLine();
    }*/

    return true;
}

QString PrintConfig::companyName() const { return companyName_; }
QString PrintConfig::address() const { return address_; }
QString PrintConfig::nit() const { return nit_; }
QString PrintConfig::owner() const { return owner_; }
QString PrintConfig::phone() const { return phone_; }

QString PrintConfig::logoLeftPath() const { return logoLeft_; }
QString PrintConfig::logoRightPath() const { return logoRight_; }

QString PrintConfig::footerLines() const { return footerLines_; }
