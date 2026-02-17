#include "licenciamanager.h"

LicenciaManager::LicenciaManager(QObject *parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
}

void LicenciaManager::solicitarValidacion(QString key, QString hwid) {
    QUrl url("http://127.0.0.1:8080/validar_licencia");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["key"] = key;
    json["hwid"] = hwid;

    connect(networkManager, &QNetworkAccessManager::finished, this, &LicenciaManager::procesarRespuesta);
    networkManager->post(request, QJsonDocument(json).toJson());
}

void LicenciaManager::procesarRespuesta(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();

        if (obj["status"].toString() == "authorized") {
            emit resultadoValidacion(true, "Sede: " + obj["sede"].toString());
        } else {
            emit resultadoValidacion(false, obj["message"].toString());
        }
    } else {
        emit resultadoValidacion(false, "Servidor central no disponible.");
    }
    reply->deleteLater();
}
