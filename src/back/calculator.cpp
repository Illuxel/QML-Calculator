#include "Calculator.h"

Standart::Standart(QObject *parent)
    : QObject{parent}
    , m_jsEngine(new QJSEngine(this))
{
    m_LastOperation = Undefined;
    m_AvaliableOperations = Value;
}
Standart::~Standart()
{
    delete m_jsEngine;
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

    MathElement el;

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
			//m_FinalValue = GetCalculatedProduct();
            m_BackJoined = m_FinalValue;
		}
        if (m_LastOperation == Function)
        {
            m_FinalValue = value;
        }
	}

	emit finalValueChanged();

    el.FinalValue = m_FinalValue;

    el.BackOperation = m_BackJoined;
    el.FrontOperation = value;

    m_LastOperation = Value;
    m_AvaliableOperations = Operator | Function | Value;

    el.LastOperation = m_LastOperation;
    el.LastAvailableOperations = m_AvaliableOperations;

    m_History.push_back(el);
}
void Standart::AddFunction(const QString& func, const QString& placeHolder) // Math.pow(%1, 2)
{
	if (m_LastOperation == Operator)
		return;

	MathElement el;

	if (m_BackJoined.isEmpty())
	{
		if (!m_FinalValue.isEmpty())
		{
			if (int pos = placeHolder.indexOf("x") != -1) {
				m_FrontJoined = placeHolder.left(pos) + m_BackJoined + placeHolder.right(pos);
			}
			else {
				m_FrontJoined = placeHolder + m_BackJoined;
			}
			emit prevValueChanged();

			m_BackJoined = func.arg(m_FinalValue);
		}
		else
		{
			return;
		}
	}
	else
	{
		m_FrontJoined = placeHolder + m_BackJoined;
		m_BackJoined = func.arg(m_BackJoined);
	}

	el.BackOperation = m_BackJoined;
	// el.FrontOperation =

	m_FinalValue = GetCalculatedProduct();
	emit finalValueChanged();
	el.FinalValue = m_FinalValue;

	m_BackJoined.clear();

	m_LastOperation = Function;
	m_AvaliableOperations = Operator | Function | Value;

	el.LastOperation = m_LastOperation;
	el.LastAvailableOperations = m_AvaliableOperations;

	m_History.push_back(el);
}
void Standart::AddOperator(const QString& op)
{
    if (!m_AvaliableOperations.testFlag(Operator))
        return;

    MathElement el;

    if (m_BackJoined.isEmpty())
    {
        m_BackJoined = m_FinalValue + op;
    }
    else
    {
        m_BackJoined += op;
    }

    el.BackOperation = m_BackJoined;

    m_LastOperation = Operator;
    m_AvaliableOperations = Function | Value;

    el.LastOperation = m_LastOperation;
    el.LastAvailableOperations = m_AvaliableOperations;

    m_History.push_back(el);
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
void Standart::ClearHistory()
{
    m_History.clear();
}

void Standart::executeCommand(const QString &cmd)
{
    Command c = ConvertStringToEnum<Command>(cmd);

    switch (c)
    {
    case Standart::del:

        m_FinalValue.erase(m_FinalValue.end(), m_FinalValue.end());
        emit finalValueChanged();

        break;
    case Standart::clr: ClearCalculations();
        break;
    case Standart::clrall: ClearAll();
        break;
	case Standart::equal: 

        m_FinalValue = GetCalculatedProduct();
        emit finalValueChanged();

		break;
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
