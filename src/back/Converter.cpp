#include "Converter.h"

Converter::Converter(QObject* parent)
    : QObject(parent)
    , m_jsEngine(new QJSEngine()) {}
Converter::~Converter()
{
    delete m_jsEngine;
}

Q_INVOKABLE void Converter::processInput(const QString& value)
{
    if (value.isEmpty())
        return;

	QString func = m_DataList[m_SelectedType].arg(value);
    QString finalValue = ExecuteFunction(func);

    SetConverted(finalValue);
}

const QString& Converter::GetInputValue() const
{
    return m_InputValue;
}
void Converter::SetInputValue(const QString& val)
{
    m_InputValue = val;
    emit inputValueChanged();
}

QString Converter::GetConverted() const
{
    return m_LastInputed;
}
void Converter::SetConverted(const QString& val)
{
    m_LastInputed = val;
	emit lastConvertedChanged();
}

QString Converter::ExecuteFunction(const QString& func)
{
    QJSValue val = m_jsEngine->evaluate(func);
    return val.toString();
}

void Converter::SetSecondType(const QString& second)
{
    m_SelectedType = second;

    processInput(m_LastInputed);
}
const QString& Converter::GetSecondType() const
{
    return m_SelectedType;
}

QStringList Converter::GetConverterList() const
{
	return m_DataList.keys();
}
Q_INVOKABLE void Converter::setScheme(const QVariantMap& scheme)
{
    for (const auto& [name, function] : scheme.toStdMap())
        m_DataList.insert(name, function.toString());

    emit schemeLoaded();
}
