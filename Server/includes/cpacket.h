#ifndef CPACKET_H
#define CPACKET_H


#include "cclient.h"
#include "cchannel.h"
#include "cmessage.h"

#include <QString>
#include <QList>

#include "cserver.h"

class CServer;

struct register_info{
    QString email;
    QString password;
    QString password_confirm;
    QString name;

};

class CPacket
{
    public:
        CPacket();
        CPacket(QByteArray data, CClient * client);
        CPacket(QString type, QString action);

        //Getters
        QString GetType();
        QString GetAction();

        QJsonDocument GetData()
        {
            return m_data;
        }

        //Convert m_obj to a byte array
        QByteArray GetByteArray()
        {
            QJsonDocument doc(m_obj);
            //qDebug() << doc;
            m_ba = doc.toJson();
            return m_ba;
        }

        QUuid get_IdClient()
        {
            return id_client;
        }

        int get_IdChannel()
        {
            return id_channel;
        }

        struct register_info get_RegisterInfo()
        {
            return m_register;
        }

        //Setters
        void SetType(QString p_type);
        void SetAction(QString p_action);

        //Serialiaze
        void Serialize();                                            //Server mainObj - Type & Action
        void Serialize(CServer* c);                            //Serialize Object Server

        //Serialize specific object -
        void Serialize_newClient(CClient * client, bool sendPP);                  //Serialize Client object ( Pseudo & ID & isOnline & ...)
        void Serialize_newChannel(CChannel * channel);               //Serialize Channel object ( Name & ID & MaxUsers=
        void Serialize_myClient(CClient * client);

        void Serialize_auth(CClient* info, int code);
        void Serialize_ID(int chan, QUuid client);                     //Serialize ID Object (ID chan & ID client)
        void Serialize_regReq(QString username, QString mail, QString password,QString password_confirm);
        void Serialize_regAns(int code);
        void Serialize_MessageListInfo(int index);
        void Serialize_Message(CMessage msg);
        void Serialize_MessageList(QList<CMessage> list);
        void Serialize_MessageError(int code);
        void Serialize_ppAnswer(QImage pp,QUuid uuid);

        //Deserialize specific object
        CClient * Deserialize_myClient();
        CClient * Deserialize_newClient();
        CChannel * Deserialize_newChannel();

        QList<QString> Deserialize_auth();
        void Deserialize_ID();                                       //Deerialize ID Object (ID chan & ID client)
        void Deserialize_regReq();
        CMessage Deserialize_Message();
        QList<CMessage> Deserialize_MessageList();
        QList<QString> deserialize_messageRequest();
        QString deserialize_ppRequest();

        void Serialize_Register(struct register_info reg);           //Serialize Register
        struct register_info Deserialize_Register();                 //Deserialize Register

    private:
        void Deserialize();
        //Type & Action corresponding to the request
        QString m_type;
        QString m_action;

        //Client who send the request
        CClient * m_client;

        //If ID object exist - on call Deserialize_ID();
        QUuid id_client;
        int id_channel;

        //Use for serialization / Deserialization
        QJsonObject m_obj;                                           //regroup all of the object that has been serialize

        //From Object to Byte Array
        QJsonDocument m_data;
        QByteArray m_ba;

        struct register_info m_register;
};

#endif // CPACKET_H
