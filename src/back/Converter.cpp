#include "Converter.h"

#include <QFile>

Converter::Converter(QObject* parent)
    : QObject(parent)
    , m_jsEngine(new QJSEngine())
{
    QFile file("ConverterData.json");
    file.open(QFile::ReadOnly);

    QByteArray arr = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(arr);
    m_ConverterScheme = new QJsonObject(doc.object());
}
Converter::~Converter()
{
    delete m_jsEngine;
    delete m_ConverterScheme;
}

void Converter::SetConverter(const QString& converter)
{
    m_CurrentConverter = "";

	for (const auto& data : m_ConverterScheme->keys())
		if (data == converter)
			m_CurrentConverter = converter;

    emit converterChanged();
}

void Converter::SetFirstType(const QString& first)
{
    m_selectedTypes.first = first;
    emit selectedTypesChanged();
}
const QString& Converter::GetFirstType() const
{
    return m_selectedTypes.first;
}

void Converter::SetSecondType(const QString& second)
{
    m_selectedTypes.second = second;
    emit selectedTypesChanged();
}
const QString& Converter::GetSecondType() const
{
    return m_selectedTypes.second;
}

QStringList Converter::GetConverterList() const
{
    return m_ConverterScheme->value(m_CurrentConverter).toObject().keys();
}
const QString &Converter::GetCurrentConverter() const
{
    return m_CurrentConverter;
}