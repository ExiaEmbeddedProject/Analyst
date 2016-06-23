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
    manager = new QNetworkAccessManager(this);
    QString url(QString("%1/_all_dbs").arg(this->baseUrl));
    qDebug() << "Making a GET http request to " << url;
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotDatabaseListingFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
}

void Couchdb::getAllDocuments(const QString &db)
{
    manager = new QNetworkAccessManager(this);
    QString url(QString("%1/%2/_all_docs").arg(this->baseUrl).arg(db));
    qDebug() << "Making a GET http request to " << url;
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotAllDocumentRetrievalFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
}

void Couchdb::getDocument(const QString &db, const QString id)
{
    manager = new QNetworkAccessManager(this);
    QString url(QString("%1/%2/%3").arg(this->baseUrl).arg(db).arg(id));
    qDebug() << "Making a GET http request to " << url;
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotDocumentRetrievalFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
}

void Couchdb::slotDatabaseListingFinished(QNetworkReply *reply)
{
    qDebug() << "Databases listing finished";
    const QByteArray response = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(response);
    QJsonArray array = document.array();
    QStringList list;
    foreach(QVariant item, array.toVariantList())
    {
        list << item.toString();
    }
    emit databasesListed(list);
}

void Couchdb::slotAllDocumentRetrievalFinished(QNetworkReply *reply)
{
    qDebug() << "Documents listing finished";
    const QByteArray response = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(response);
    QJsonObject object = document.object();
    QJsonArray array = object["rows"].toArray();
    QVariantList list = array.toVariantList();
    emit allDocumentsRetrieved(list);
}

void Couchdb::slotDocumentRetrievalFinished(QNetworkReply *reply)
{
    qDebug() << "Document retrieval finished";
    const QByteArray response = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(response);
    QVariant object = document.toVariant();
    emit documentRetrieved(object);
}
