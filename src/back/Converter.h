#pragma once

#include <QObject>
#include <qqmlregistration.h>

#include <QStringListModel>
#include <QHash>

#include <QJsonDocument>
#include <QJsonObject>

#include <QJSEngine>

class ConverterBack
    : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList typeList MEMBER m_TypeList READ converterList)
    QStringList m_TypeList;
    Q_PROPERTY(QString currentConverter MEMBER m_CurrentConverter READ currentConverter WRITE SetConverter NOTIFY converterChanged)
    QString m_CurrentConverter;

public:
    ConverterBack(QObject* parent = nullptr);
    ~ConverterBack() override;

    const QStringList& converterList() const;
    const QString& currentConverter() const;

    void SetConverter(const QString& converter);

signals:
    void converterChanged();

private:

};

