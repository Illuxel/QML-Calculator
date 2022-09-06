#include "Converter.h"

#include <QFile>
#include <QException>

ConverterBack::ConverterBack(QObject* parent)
    : QObject(parent)
{
    QFile file("ConverterData.json");
    file.open(QFile::ReadOnly);

    QByteArray arr = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(arr);
    QJsonObject obj = doc.object();

    m_TypeList = obj.keys();
}
ConverterBack::~ConverterBack()
{
}

const QStringList& ConverterBack::converterList() const
{
    return m_TypeList;
}

const QString &ConverterBack::currentConverter() const
{
    return m_CurrentConverter;
}
void ConverterBack::SetConverter(const QString &converter)
{
    for (const auto& data : m_TypeList)
        if (data == converter)
            m_CurrentConverter = converter;
}
