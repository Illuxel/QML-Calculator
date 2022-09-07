#include "Calculator.h"

#include <QQmlApplicationEngine>

Standart::Standart(QObject *parent)
    : QObject{parent}
    , m_jsEngine(new QJSEngine(this))
    , m_model(new QStringListModel)
{
    m_LastOperation = Undefined;
    m_AvaliableOperations = Value;
}
Standart::~Standart()
{
    delete m_jsEngine;
    delete m_model;
}

void Standart::processButton(const QString& type, const QString& func, const QString& placeHolder)
{
    QString capitalized = type;
    capitalized[0] = type[0].toUpper();

    WaitOperation t = ConvertStringToEnum<WaitOperation>(capitalized);

    switch (t)
    {
    case Standart::Cmd: executeCommand(func);
        break;
    case Standart::Function: AddFunction(func, placeHolder);
		break;
	case Standart::Operator: AddOperator(func);
        break;
	case Standart::Value: AddValue(func);
		break;
    }
}

void Standart::AddValue(const QString& value)
{
    if (!m_AvaliableOperations.testFlag(Value))
        return;
    if (value == '0' && (m_BackJoined.isEmpty() || m_FinalValue.isEmpty()))
        return;
    if (m_BackJoined.isEmpty() && value == '.')
        return;

	if (m_BackJoined.isEmpty())
	{
		m_BackJoined = value;
        m_FinalValue = value;
    }
	else
	{
        m_BackJoined += value;

		if (m_LastOperation == Value)
		{
            m_FinalValue += value;
		}
		if (m_LastOperation == Operator)
		{
            m_FinalValue = value;
		}
        if (m_LastOperation == Function)
        {
            m_FinalValue = value;
        }
	}

	emit finalValueChanged();

    m_LastOperation = Value;
    m_AvaliableOperations = Operator | Function | Value;
}
void Standart::AddFunction(const QString& func, const QString& placeHolder) // Math.pow(%1, 2)
{
	if (m_LastOperation == Undefined)
		return;
	if (m_LastOperation == Operator)
		return;

	// preview opeartion 
	if (int pos = placeHolder.indexOf("x") != -1) {
        QString templ = placeHolder;
        templ.replace('x', m_BackJoined);
		m_FrontJoined = templ;
	}
	else {
		m_FrontJoined = placeHolder + m_BackJoined;
	}

    // parsing function
	if (m_BackJoined.isEmpty())
	{
		if (!m_FinalValue.isEmpty())
		{
			m_BackJoined = func.arg(m_FinalValue);
		}
		else
		{
			return;
		}
	}
	else
	{
		m_BackJoined = func.arg(m_BackJoined);
	}

	m_FinalValue = GetCalculatedProduct();

    emit prevValueChanged();
	emit finalValueChanged();

	m_BackJoined.clear();

	m_LastOperation = Function;
	m_AvaliableOperations = Operator | Function | Value;
}
void Standart::AddOperator(const QString& op)
{
    if (m_LastOperation == Undefined)
        return;
    if (!m_AvaliableOperations.testFlag(Operator))
        return;

    if (m_BackJoined.isEmpty())
    {
        m_BackJoined = m_FinalValue + op;
        m_FrontJoined = m_BackJoined;
    }
    else
    {
        m_BackJoined += op;
        m_FrontJoined = m_BackJoined;
    }

    emit prevValueChanged();

    m_LastOperation = Operator;
    m_AvaliableOperations = Function | Value;
}

void Standart::ClearAll()
{
	ClearHistory();
	ClearCalculations();
}
void Standart::ClearCalculations()
{
	m_BackJoined.clear();

	m_FinalValue.clear();
	emit finalValueChanged();
	m_FrontJoined.clear();
    emit prevValueChanged();

	m_LastOperation = Undefined;
	m_AvaliableOperations = Value;
}

QList <Standart::MathElement> Standart::m_History{};

void Standart::AddHistory(const MathElement& el)
{
    m_History.push_back(el);
}
QStringListModel* Standart::GetOperationHistory()
{
    QStringList temp;

    for (const auto& el : m_History)
        temp.push_back(el.FrontOperation);

    return new QStringListModel(temp);
}
void Standart::ClearHistory()
{
    m_History.clear();
}

void Standart::executeCommand(const QString &cmd)
{
    Command c = ConvertStringToEnum<Command>(cmd);
    m_LastCommand = c;

    MathElement el;

	switch (c)
    {
    case Standart::del:
    {
        if (m_AvaliableOperations.testFlag(Value))
        {
            if (!m_BackJoined.isEmpty()) {

                bool is_number = m_BackJoined[m_BackJoined.size() - 1].isNumber();

                if (is_number)
                    m_BackJoined.erase(m_BackJoined.end() - 1, m_BackJoined.end());
                else
                {

                }
            }

            if (!m_FinalValue.isEmpty())
                m_FinalValue.erase(m_FinalValue.end() - 1, m_FinalValue.end());
        }
        emit finalValueChanged();

        break;
    }
    case Standart::clr: ClearCalculations();
        break;
    case Standart::clrall: ClearAll();
        break;
	case Standart::cnvrt: 
    {
        if (m_FinalValue.isEmpty() || m_BackJoined.isEmpty())
            return;

        if (int pos = m_FinalValue.indexOf('-') != -1)
            m_FinalValue.erase(m_FinalValue.begin(), m_FinalValue.begin() + pos);
        else
            m_FinalValue.insert(0, '-');

        m_BackJoined = m_FinalValue;

        emit finalValueChanged();

        break;
    }
	case Standart::equal: 
    {
        if (m_LastOperation == Function)
            m_BackJoined = m_FinalValue;
        if (m_LastOperation == Operator)
            m_BackJoined += m_FinalValue;

        el.BackOperation = m_BackJoined;

        el.LastOperation = m_LastOperation;
        el.LastAvailableOperations = m_AvaliableOperations;

        m_FinalValue = GetCalculatedProduct();
        el.FinalValue = m_FinalValue;
        emit finalValueChanged();

        m_FrontJoined = m_BackJoined + '=';
        el.FrontOperation = m_FrontJoined;
        emit prevValueChanged();

        // m_LastOperation = Undefined;

        AddHistory(el);

        break;
    }
    }
}

QString Standart::GetCalculatedProduct() const
{
    QJSValue val = m_jsEngine->evaluate(m_BackJoined);
    return val.toString();
}

const QString& Standart::GetPrevOperation() const
{
    return m_FrontJoined;
}
const QString& Standart::GetFinalValue() const
{
    return m_FinalValue;
}