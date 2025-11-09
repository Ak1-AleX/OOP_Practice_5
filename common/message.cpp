#include "message.h"
#include <QDataStream>

QByteArray Message::serialize() const {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << *this;
    return data;
}

Message Message::deserialize(const QByteArray& data) {
    Message msg;
    QDataStream stream(data);
    stream >> msg;
    return msg;
}

Message Message::createPolynom(int degree, const QString& leadingCoeff, const QVector<QString>& roots) {
    QVector<QString> params;
    params.append(QString::number(degree));
    params.append(leadingCoeff);
    for (const QString& root : roots) {
        params.append(root);
    }
    return Message(MessageType::CREATE_POLYNOM, "Create polynom", params);
}

Message Message::changeLeadingCoeff(const QString& newCoeff) {
    return Message(MessageType::CHANGE_LEADING_COEFF, "Change leading coefficient", {newCoeff});
}

Message Message::changeRoot(int index, const QString& newRoot) {
    return Message(MessageType::CHANGE_ROOT, "Change root", {QString::number(index), newRoot});
}

Message Message::evaluate(const QString& point) {
    return Message(MessageType::EVALUATE, "Evaluate polynom", {point});
}

Message Message::getForm1() {
    return Message(MessageType::GET_FORM1, "Get coefficients form");
}

Message Message::getForm2() {
    return Message(MessageType::GET_FORM2, "Get roots form");
}

Message Message::success(const QString& result) {
    return Message(MessageType::SUCCESS_RESPONSE, result);
}

Message Message::error(const QString& errorMessage) {
    return Message(MessageType::ERROR_RESPONSE, errorMessage);
}

QDataStream& operator<<(QDataStream& out, const Message& msg) {
    out << static_cast<qint32>(msg.type);
    out << msg.data;
    out << msg.params;
    return out;
}

QDataStream& operator>>(QDataStream& in, Message& msg) {
    qint32 type;
    in >> type;
    msg.type = static_cast<MessageType>(type);
    in >> msg.data;
    in >> msg.params;
    return in;
}
