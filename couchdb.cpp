#include "couchdb.h"
#include "QJsonObject"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonValue"
#include "QVariant"
#include "QVariantList"

Couchdb::Couchdb(QObject* parent) : QObject(parent)
{
    this->baseUrl = "http://localhost:5984/";
}

QString Couchdb::getBaseUrl() const
{
    return baseUrl;
}

void Couchdb::setBaseUrl(const QString &value)
{
    baseUrl = value;
}

void Couchdb::listDatabases()
{
    QNetworkAccessManager network;
    QString url(QString("%1/_all_dbs").arg(this->baseUrl));
    QNetworkReply *reply = network.get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, SIGNAL(finished()), SLOT(slotDatabaseListingFinished()));
    QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(slotConnectionErrorOccured(QNetworkReply::NetworkError)));
}

void Couchdb::getAllDocuments(const QString &db)
{
    QNetworkAccessManager network;
    QString url(QString("%1/%2/_all_docs").arg(this->baseUrl).arg(db));
    QNetworkReply *reply = network.get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, SIGNAL(finished()), SLOT(slotDocumentListingFinished()));
    QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(slotConnectionErrorOccured(QNetworkReply::NetworkError)));
}

void Couchdb::getDocument(const QString &db, const QString id)
{
    QNetworkAccessManager network;
    QString url(QString("%1/%2/%3").arg(this->baseUrl).arg(db).arg(id));
    QNetworkReply *reply = network.get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, SIGNAL(finished()), SLOT(slotDocumentRetrievalFinished()));
    QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(slotConnectionErrorOccured(QNetworkReply::NetworkError)));
}

void Couchdb::slotConnectionErrorOccured(QNetworkReply::NetworkError error)
{
    if (error == QNetworkReply::ConnectionRefusedError)
    {
        qDebug() << "Connection refused";
    }
    else if (error == QNetworkReply::HostNotFoundError)
    {
        qDebug() << "Host Not Found";
    }
    else if (error == QNetworkReply::ProtocolFailure)
    {
        qDebug() << "Protocol failure";
    }
    else if (error == QNetworkReply::RemoteHostClosedError)
    {
        qDebug() << "Remote Host closed";
    }
}

void Couchdb::slotDatabaseListingFinished()
{
    const QByteArray response = ((QNetworkReply*)QObject::sender())->readAll();
    QJsonDocument document = QJsonDocument::fromJson(response);
    QJsonArray array = document.array();
    QStringList list;
    foreach(QVariant item, array.toVariantList())
    {
        list << item.toString();
    }
    emit databasesListed(list);
}

void Couchdb::slotAllDocumentRetrievalFinished()
{
    const QByteArray response = ((QNetworkReply*)QObject::sender())->readAll();
    QJsonDocument document = QJsonDocument::fromJson(response);
    QJsonObject object = document.object();
    QJsonArray array = object["rows"].toArray();
    QVariantList list = array.toVariantList();
    emit allDocumentsRetrieved(list);
}

void Couchdb::slotDocumentRetrievalFinished()
{
    const QByteArray response = ((QNetworkReply*)QObject::sender())->readAll();
    QJsonDocument document = QJsonDocument::fromJson(response);
    QVariant object = document.toVariant();
    emit documentRetrieved(object);
}
