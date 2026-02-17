#ifndef LICENCIAMANAGER_H
#define LICENCIAMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class LicenciaManager : public QObject {
    Q_OBJECT
public:
    explicit LicenciaManager(QObject *parent = nullptr);
    void solicitarValidacion(QString key, QString hwid);

signals:
    void resultadoValidacion(bool exito, QString mensaje);

private slots:
    void procesarRespuesta(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
};

#endif // LICENCIAMANAGER_H
