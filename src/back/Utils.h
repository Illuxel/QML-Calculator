#pragma once

#include <QObject>
#include <QMetaEnum>

template <typename Enum>
inline Enum ConvertStringToEnum(const QString& enStr)
{
	QMetaEnum en = QMetaEnum::fromType<Enum>();
	if (enStr.isEmpty())
		return static_cast<Enum>(-1);
	return static_cast<Enum>(en.keyToValue(enStr.toUtf8()));
}