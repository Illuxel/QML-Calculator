#pragma once

#include <QObject>

#include <QStringListModel>
#include <QmlTypeAndRevisionsRegistration>

class HistoryElement
{
	Q_GADGET

public:
	HistoryElement() = default;
	HistoryElement(const QString& placeHolder)
		: m_PlaceHolderText(placeHolder) {}
	virtual ~HistoryElement() {}

    virtual QString placeHolderText() const;

protected:
	QString m_PlaceHolderText;
};

class History
	: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList list READ GetHistoryList NOTIFY historyListChanged)
    Q_PROPERTY(QString currentItem READ GetCurrentItem WRITE SetCurrentItem NOTIFY currentItemChanged)

public:
    explicit History(QObject* parent = nullptr);

    Q_INVOKABLE QString placeHolderAt(int index);
    Q_INVOKABLE void clearHistory();

    QStringList GetHistoryList() const;

    Q_INVOKABLE QString GetCurrentItem();
    Q_INVOKABLE void SetCurrentItem(const QString& el);

    ~History() override;

public slots:
    Q_INVOKABLE void pushElement(HistoryElement* el);
    Q_INVOKABLE void popElement();

signals:
    void historyListChanged();
    void currentItemChanged();

private:
    QList <HistoryElement*> m_Elements;
    HistoryElement* m_CurrentItem = nullptr;
};
