#include "Converter.h"

#include <QFile>

Converter::Converter(QObject* parent)
    : QObject(parent)
    , m_jsEngine(new QJSEngine(this))
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

void Converter::LoadObjectToList()
{
    m_TypeList = m_ConverterScheme->value(m_CurrentConverter).toObject().keys();
    emit datatypeListChanged();
}

void Converter::SetConverter(const QString& converter)
{
    m_CurrentConverter = "";

	for (const auto& data : m_ConverterScheme->keys())
		if (data == converter)
			m_CurrentConverter = converter;

    LoadObjectToList();

    emit converterChanged();
}

const QStringList& Converter::GetConverterList() const
{
    return m_TypeList;
}
const QString &Converter::GetCurrentConverter() const
{
    return m_CurrentConverter;
}