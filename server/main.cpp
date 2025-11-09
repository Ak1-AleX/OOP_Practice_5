#include <QCoreApplication>
#include <QDebug>
#include "serverApp.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    ServerApp server;
    if (!server.start(10001)) {
        qCritical() << "Не удалось запустить сервер";
        return -1;
    }

    qInfo() << "=========================================";
    qInfo() << "Сервер полиномов запущен";
    qInfo() << "Порт: 10001";
    qInfo() << "Ожидание запросов от клиента...";
    qInfo() << "=========================================";

    return a.exec();
}
