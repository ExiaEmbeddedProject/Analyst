#ifndef COUCHDB_H
#define COUCHDB_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QMap>
#include <QJsonDocument>
#include <QJsonValue>


class Couchdb : public QObject
{
    Q_OBJECT

public:
    Couchdb(QObject *parent = 0);
    QString getBaseUrl() const;
    void setBaseUrl(const QString &value);

public slots:
    void listDatabases();
    void getAllDocuments(const QString &db);
    void getDocument(const QString &db, const QString id);

signals:
    void databasesListed(const QStringList &list);
    void allDocumentsRetrieved(const QVariantList &list);
    void documentRetrieved(const QVariant &value);

private:
    QString baseUrl;

private slots:
    void slotConnectionErrorOccured(QNetworkReply::NetworkError error);
    void slotDatabaseListingFinished();
    void slotAllDocumentRetrievalFinished();
    void slotDocumentRetrievalFinished();
};

#endif // COUCHDB_H
