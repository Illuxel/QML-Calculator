#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QIcon>

#include "Calculator.h"
#include "Converter.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Calculator QML");
#endif

    QGuiApplication app(argc, argv);
    QGuiApplication::setWindowIcon(QIcon("qrc:/app/assets/images/calculator.png"));

    // history is static object
    QScopedPointer <History> history(new History());
    qmlRegisterSingletonInstance("Calculator.History", 1, 0, "History", history.get());

    qmlRegisterType <Standart>("Calculator.Standart", 1, 0, "Standart");

    // converter handler is static object
	QScopedPointer <ConverterHandler> cnvtHandler(new ConverterHandler());
    qmlRegisterSingletonInstance("Calculator.ConverterHandler", 1, 0, "ConverterHandler", cnvtHandler.get());

    qmlRegisterType <Converter>("Calculator.Converter", 1, 0, "Converter");
    
    QQmlApplicationEngine engine;
	engine.load(QUrl("qrc:/app/qml/main.qml"));
	if (engine.rootObjects().isEmpty())
		return -1;
	return app.exec();
}
