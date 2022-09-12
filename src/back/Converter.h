#pragma once

#include <QStringListModel>
#include <QHash>

#include <QJsonDocument>
#include <QJsonObject>

#include <QJSEngine>

class Converter
    : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList typeList MEMBER m_TypeList READ GetConverterList NOTIFY datatypeListChanged)
    QStringList m_TypeList;
    Q_PROPERTY(QString currentConverter MEMBER m_CurrentConverter READ GetCurrentConverter WRITE SetConverter NOTIFY converterChanged)
    QString m_CurrentConverter;

public:
    Converter(QObject* parent = nullptr);

    void SetConverter(const QString& type);

    const QString& GetCurrentConverter() const;
    const QStringList& GetConverterList() const;

    ~Converter() override;

private:
    void LoadObjectToList();

signals:
    void datatypeListChanged();
    void converterChanged();

private:
    QJSEngine* m_jsEngine = nullptr;
    QJsonObject* m_ConverterScheme = nullptr;
};

