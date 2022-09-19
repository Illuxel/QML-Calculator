#pragma once

#include <QStringListModel>
#include <QHash>

#include "Utils.h"
#include "ConverterHandler.h"

class Converter
    : public QObject
{
    Q_OBJECT

		Q_PROPERTY(QStringList typeList READ GetConverterList NOTIFY schemeLoaded)
		Q_PROPERTY(QString secondType READ GetSecondType WRITE SetSecondType)
		Q_PROPERTY(QString inputValue READ GetInputValue WRITE SetInputValue NOTIFY inputValueChanged)
        
    Q_PROPERTY(QString convertedValue READ GetConverted NOTIFY lastConvertedChanged)

public:
    enum ButtonType 
    {
        Value = 2,
        Function
    };
    Q_ENUM(ButtonType)

    Converter(QObject* parent = nullptr);

    Q_INVOKABLE void processInput(const QString& value);

    const QString& GetInputValue() const;
    void SetInputValue(const QString& val);

    QString GetConverted() const;
    void SetConverted(const QString& val);

    void SetSecondType(const QString& second);
    const QString& GetSecondType() const;

	QStringList GetConverterList() const;
	Q_INVOKABLE void setScheme(const QVariantMap& scheme);

    ~Converter() override;

private:
    QString ExecuteFunction(const QString& func);

signals:
    void schemeLoaded();

    void inputValueChanged();
    void lastConvertedChanged();

private:
	QJSEngine* m_jsEngine = nullptr;
    // first - data name 
    // second - data function
    QMap <QString, QString> m_DataList;

    QString m_InputValue;

    QString m_SelectedType;
    QString m_LastInputed;
};

