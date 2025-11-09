#include "serverApp.h"
#include <QDebug>
#include <QHostAddress>

ServerApp::ServerApp(QObject* parent) : QObject(parent) {
    communicator = new NetworkCommunicator(this);
    connect(communicator, &NetworkCommunicator::messageReceived,
            this, &ServerApp::handleMessage);
}

bool ServerApp::start(quint16 port) {
    return communicator->startServer(port);
}

void ServerApp::handleMessage(const Message& msg) {
    qDebug() << "Получено сообщение типа:" << static_cast<int>(msg.type);

    switch (msg.type) {
    case MessageType::CREATE_POLYNOM:
        processCreatePolynom(msg);
        break;
    case MessageType::CHANGE_LEADING_COEFF:
        processChangeLeadingCoeff(msg);
        break;
    case MessageType::CHANGE_ROOT:
        processChangeRoot(msg);
        break;
    case MessageType::EVALUATE:
        processEvaluate(msg);
        break;
    case MessageType::GET_FORM1:
        processGetForm1(msg);
        break;
    case MessageType::GET_FORM2:
        processGetForm2(msg);
        break;
    default:
        qDebug() << "Неизвестный тип сообщения";
        break;
    }
}

void ServerApp::processCreatePolynom(const Message& msg) {
    try {
        if (msg.params.size() < 2) {
            sendResponse(Message::error("Недостаточно параметров для создания полинома"));
            return;
        }

        int degree = msg.params[0].toInt();
        QString leadingCoeffStr = msg.params[1];

        QVector<QString> roots;
        for (int i = 2; i < msg.params.size(); i++) {
            roots.append(msg.params[i]);
        }

        if (roots.size() != degree) {
            sendResponse(Message::error("Количество корней не соответствует степени полинома"));
            return;
        }

        QVector<number> numberRoots;
        for (const QString& rootStr : roots) {
            numberRoots.append(number::fromString(rootStr));
        }

        number leadingCoeff = number::fromString(leadingCoeffStr);
        currentPolynom.setFromRoots(degree, leadingCoeff, numberRoots);

        QString result = "Полином создан:\n\n" +
                         currentPolynom.toStringForm1() + "\n\n" +
                         currentPolynom.toStringForm2();

        sendResponse(Message::success(result));

    } catch (const std::exception& e) {
        sendResponse(Message::error("Ошибка создания полинома: " + QString(e.what())));
    }
}

void ServerApp::processChangeLeadingCoeff(const Message& msg) {
    if (currentPolynom.isEmpty()) {
        sendResponse(Message::error("Полином не задан"));
        return;
    }

    try {
        if (msg.params.isEmpty()) {
            sendResponse(Message::error("Не указан новый коэффициент"));
            return;
        }

        QString coeffStr = msg.params[0];
        number newCoeff = number::fromString(coeffStr);
        currentPolynom.setLeadingCoeff(newCoeff);

        QString result = "Коэффициент изменен:\n\n" + currentPolynom.toStringForm1();
        sendResponse(Message::success(result));

    } catch (const std::exception& e) {
        sendResponse(Message::error("Ошибка изменения коэффициента: " + QString(e.what())));
    }
}

void ServerApp::processChangeRoot(const Message& msg) {
    if (currentPolynom.isEmpty()) {
        sendResponse(Message::error("Полином не задан"));
        return;
    }

    try {
        if (msg.params.size() < 2) {
            sendResponse(Message::error("Недостаточно параметров для изменения корня"));
            return;
        }

        int index = msg.params[0].toInt();
        QString newRootStr = msg.params[1];
        number newRoot = number::fromString(newRootStr);

        if (index < 0 || index >= currentPolynom.getDegree()) {
            sendResponse(Message::error("Неверный индекс корня"));
            return;
        }

        currentPolynom.setRoot(index, newRoot);

        QString result = "Корень изменен:\n\n" + currentPolynom.toStringForm2();
        sendResponse(Message::success(result));

    } catch (const std::exception& e) {
        sendResponse(Message::error("Ошибка изменения корня: " + QString(e.what())));
    }
}

void ServerApp::processEvaluate(const Message& msg) {
    if (currentPolynom.isEmpty()) {
        sendResponse(Message::error("Полином не задан"));
        return;
    }

    try {
        if (msg.params.isEmpty()) {
            sendResponse(Message::error("Не указана точка вычисления"));
            return;
        }

        QString pointStr = msg.params[0];
        number x = number::fromString(pointStr);
        number result = currentPolynom.evaluate(x);

        sendResponse(Message::success("P(" + pointStr + ") = " + result.toString()));

    } catch (const std::exception& e) {
        sendResponse(Message::error("Ошибка вычисления: " + QString(e.what())));
    }
}

void ServerApp::processGetForm1(const Message& msg) {
    if (currentPolynom.isEmpty()) {
        sendResponse(Message::error("Полином не задан"));
        return;
    }

    QString result = currentPolynom.toStringForm1();
    sendResponse(Message::success(result));
}

void ServerApp::processGetForm2(const Message& msg) {
    if (currentPolynom.isEmpty()) {
        sendResponse(Message::error("Полином не задан"));
        return;
    }

    QString result = currentPolynom.toStringForm2();
    sendResponse(Message::success(result));
}

void ServerApp::sendResponse(const Message& response, const QHostAddress& address, quint16 port) {
    communicator->sendMessage(response, address, port);
}
