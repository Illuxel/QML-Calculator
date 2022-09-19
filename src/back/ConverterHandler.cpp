#include "ConverterHandler.h"

#include <QFile>

ConverterHandler::ConverterHandler(QObject* parent)
	: QObject(parent)
{
    LoadConverterScheme();
}
ConverterHandler::~ConverterHandler()
{
	delete m_ConverterScheme;
}

bool ConverterHandler::LoadConverterScheme()
{
	QFile file("ConverterData.json");
	if (!file.open(QFile::ReadOnly))
		return false;

	QByteArray arr = file.readAll();
	QJsonDocument doc = QJsonDocument::fromJson(arr);

	m_ConverterScheme = new QJsonObject(doc.object());

	return true;
}

void ConverterHandler::SetConverter(const QString& converter)
{
	m_CurrentConverter = "";

	for (const auto& data : m_ConverterScheme->keys())
		if (data == converter)
			m_CurrentConverter = converter;
}

const QString& ConverterHandler::GetCurrentConverter() const
{
	return m_CurrentConverter;
}

Q_INVOKABLE QVariantMap ConverterHandler::getScheme() const
{
	return m_ConverterScheme->value(m_CurrentConverter).toObject().toVariantMap();
}
