#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <QObject>
#include <QCoreApplication>
#include "polynom.h"
#include "../common/communicator.h"
#include "../common/message.h"

class ServerApp : public QObject {
    Q_OBJECT

public:
    ServerApp(QObject* parent = nullptr);
    bool start(quint16 port = 10001);

private slots:
    void handleMessage(const Message& msg);

private:
    NetworkCommunicator* communicator;
    Polynom currentPolynom;

    void processCreatePolynom(const Message& msg);
    void processChangeLeadingCoeff(const Message& msg);
    void processChangeRoot(const Message& msg);
    void processEvaluate(const Message& msg);
    void processGetForm1(const Message& msg);
    void processGetForm2(const Message& msg);

    void sendResponse(const Message& response, const QHostAddress& address = QHostAddress::LocalHost, quint16 port = 10000);
};

#endif // SERVERAPP_H
