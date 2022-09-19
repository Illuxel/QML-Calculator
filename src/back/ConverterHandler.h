#pragma once

#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>

#include <QJSEngine>

class ConverterHandler
	: public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString currentConverter MEMBER m_CurrentConverter READ GetCurrentConverter WRITE SetConverter)
	//Q_PROPERTY(QString  MEMBER  READ  WRITE )

public:
	ConverterHandler(QObject* parent = nullptr);

	void SetConverter(const QString& type);
	const QString& GetCurrentConverter() const;

	Q_INVOKABLE QVariantMap getScheme() const;

	~ConverterHandler() override;

private:
	bool LoadConverterScheme();

signals:
	void convterterTypeChanged();

private:
	QJsonObject* m_ConverterScheme = nullptr;
	QString m_CurrentConverter;
};

