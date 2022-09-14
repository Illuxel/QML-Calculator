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
    Q_PROPERTY(QStringList typeList READ GetConverterList)
    Q_PROPERTY(QString currentConverter MEMBER m_CurrentConverter READ GetCurrentConverter WRITE SetConverter NOTIFY converterChanged)
    QString m_CurrentConverter;

    Q_PROPERTY(QString firstType READ GetFirstType WRITE SetFirstType NOTIFY selectedTypesChanged)
    Q_PROPERTY(QString secondType READ GetSecondType WRITE SetSecondType NOTIFY selectedTypesChanged)

public:
    Converter(QObject* parent = nullptr);

    void SetConverter(const QString& type);

    void SetFirstType(const QString& first);
    const QString& GetFirstType() const;

    void SetSecondType(const QString& second);
    const QString& GetSecondType() const;

    QStringList    GetConverterList() const;
    const QString& GetCurrentConverter() const;

    ~Converter() override;

signals:
    void converterChanged();
    void selectedTypesChanged();

private:
    QJSEngine* m_jsEngine = nullptr;
    QJsonObject* m_ConverterScheme = nullptr;

    QPair <QString, QString> m_selectedTypes;
};

