#include "couchdb.h"
#include "QJsonObject"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonValue"
#include "QVariant"
#include "QVariantList"

Couchdb::Couchdb(QObject* parent) : QObject(parent)
{

}

QJsonArray Couchdb::documents = QJsonArray();

void Couchdb::getAllDocuments(const QString &url, const QString &db)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QString finalUrl(QString("%1/%2/_all_docs").arg(url).arg(db));
    QNetworkRequest request = QNetworkRequest(QUrl(finalUrl));
    request.setRawHeader("User-Agent", "Mozilla Firefox");

    qDebug() << "Making a GET http request to " << finalUrl;


    manager->get(request);
}

void Couchdb::replyFinished(QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        qDebug() << "Couchdb response: " << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        const QByteArray response = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(response);
        QJsonObject object = document.object();
        Couchdb::documents = object["rows"].toArray();
        qDebug() << Couchdb::documents.size() << " documents retrieved.";
    }

    reply->deleteLater();
}
