#pragma once

#include "OperationHistory.h"

#include <QMetaEnum>
#include <QStringListModel>

#include <QJSEngine>

class Standart
    : public QObject
{
    Q_OBJECT

	Q_PROPERTY(QString finalValue MEMBER m_FinalValue READ GetFinalValue NOTIFY finalValueChanged)
	QString m_FinalValue;
	Q_PROPERTY(QString enteredValue MEMBER m_UnsavedValue WRITE SetEnteredValue NOTIFY enteredValueChanged)
	QString m_UnsavedValue;

    Q_PROPERTY(QString lastOperation MEMBER m_LastJoined READ GetLastOperation NOTIFY lastOperationChanged)
    QString m_LastJoined;

public:
	enum Command {
		del = 0,
		clr,
		clrall,
		cnvrt,
		equal
	};
	Q_ENUM(Command)
	enum WaitOperation {
		Cmd = 4,
		Function,
		Operator,
		Value/*,
		Undefined*/
	};
	Q_FLAG(WaitOperation)
	Q_DECLARE_FLAGS(WaitOperations, WaitOperation)

public:
    Standart(QObject *parent = nullptr);
    ~Standart() override;

    Q_INVOKABLE virtual void processButton(const QString& type, const QString& func, const QString& placeHolder);
	Q_INVOKABLE void setHistory(History* history);

	Q_INVOKABLE void update();

	Q_INVOKABLE void getEqual();

    const QString& GetFinalValue() const;
    const QString& GetLastOperation() const;

private:
    void ExecuteCommand(const QString& cmd);

	QString CalculateProduct();

	QString ConcatPHFunctionWithValue(const QString& placeHolder, double value) const;

	Q_INVOKABLE void SetEnteredValue(const QString& value);
	void AddEnteredValue(const QChar& value);

	void AddOperator(const QChar& op);
	void AddFunction(const QString& func, const QString& placeHolder);

	void DeleteEnteredValue();
	void ClearEntered();
	void ClearCalculations();

private slots:
	void onHistoryItemClicked(HistoryElement* item);

signals:
    void finalValueChanged();
	void enteredValueChanged();
    void lastOperationChanged();

private:
    QJSEngine* m_jsEngine = nullptr;
	History* m_History = nullptr;

	QString m_BackEndExpression, m_FrontEndExpression;

	Command m_LastCommand;
    WaitOperation m_LastOperation;
};

class OperationElement
	: public HistoryElement
{
public:
	QString placeHolderText() const override;

	const QString& GetFinalValue() const;
	void SetFinalValue(QString val);

	const QString& GetUnsavedValue() const;
	void SetUnsavedValue(QString val);

	const QString& GetLastJoined() const;
	void SetLastJoined(QString val);

	const QString& GetBackEndExpression() const;
	void SetBackEndExpression(QString val);

	Standart::WaitOperation GetOperationType() const;
	void SetOperationType(Standart::WaitOperation val);

private:
	QString FinalValue, UnsavedValue, LastJoined, BackEndExpression;
	Standart::WaitOperation LastOperation;
};

template <typename Enum>
Enum ConvertStringToEnum(const QString& enStr)
{
	QMetaEnum en = QMetaEnum::fromType<Enum>();
	if (enStr.isEmpty())
		return static_cast<Enum>(-1);
    return static_cast<Enum>(en.keyToValue(enStr.toUtf8()));
}

Q_DECLARE_OPERATORS_FOR_FLAGS(Standart::WaitOperations)