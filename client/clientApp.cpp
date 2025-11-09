#include "clientApp.h"
#include <QDebug>
#include <QCoreApplication>

ClientApp::ClientApp(QObject* parent) : QObject(parent), waitingForResponse(false) {
    communicator = new NetworkCommunicator(this);
    responseTimer = new QTimer(this);

    connect(communicator, &NetworkCommunicator::messageReceived,
            this, &ClientApp::handleServerResponse);
    connect(responseTimer, &QTimer::timeout,
            this, &ClientApp::checkForResponse);

    responseTimer->setSingleShot(true);
}

ClientApp::~ClientApp() {
    if (responseTimer->isActive()) {
        responseTimer->stop();
    }
}

bool ClientApp::start(quint16 clientPort, quint16 serverPort) {
    return communicator->startClient(clientPort, serverPort);
}

void ClientApp::createPolynom(int degree, const QString& leadingCoeff, const QVector<QString>& roots) {
    Message request = Message::createPolynom(degree, leadingCoeff, roots);
    sendRequest(request);
}

void ClientApp::changeLeadingCoeff(const QString& newCoeff) {
    Message request = Message::changeLeadingCoeff(newCoeff);
    sendRequest(request);
}

void ClientApp::changeRoot(int index, const QString& newRoot) {
    Message request = Message::changeRoot(index, newRoot);
    sendRequest(request);
}

void ClientApp::evaluate(const QString& point) {
    Message request = Message::evaluate(point);
    sendRequest(request);
}

void ClientApp::getForm1() {
    Message request = Message::getForm1();
    sendRequest(request);
}

void ClientApp::getForm2() {
    Message request = Message::getForm2();
    sendRequest(request);
}

void ClientApp::sendRequest(const Message& request) {
    if (waitingForResponse) {
        emit errorOccurred("Ожидается ответ на предыдущий запрос");
        return;
    }

    communicator->sendMessage(request);
    waitingForResponse = true;
    responseTimer->start(5000); // Таймаут 5 секунд

    qDebug() << "Запрос отправлен серверу, тип:" << static_cast<int>(request.type);
}

void ClientApp::handleServerResponse(const Message& msg) {
    if (!waitingForResponse) {
        qDebug() << "Получен неожиданный ответ от сервера";
        return;
    }

    responseTimer->stop();
    waitingForResponse = false;

    switch (msg.type) {
    case MessageType::SUCCESS_RESPONSE:
        processSuccessResponse(msg);
        break;
    case MessageType::ERROR_RESPONSE:
        processErrorResponse(msg);
        break;
    default:
        emit errorOccurred("Получен ответ неизвестного типа");
        break;
    }
}

void ClientApp::checkForResponse() {
    if (waitingForResponse) {
        waitingForResponse = false;
        emit errorOccurred("Таймаут ожидания ответа от сервера");
    }
}

void ClientApp::processSuccessResponse(const Message& msg) {
    qDebug() << "Получен успешный ответ от сервера";
    emit responseReceived(msg.data);
}

void ClientApp::processErrorResponse(const Message& msg) {
    qDebug() << "Получена ошибка от сервера:" << msg.data;
    emit errorOccurred(msg.data);
}
