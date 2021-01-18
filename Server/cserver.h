#ifndef CSERVER_H
#define CSERVER_H

#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>
#include <QRegExp>


#include "src/includes/AbstractServer.h"

#include "src/includes/cchannel.h"
#include "src/includes/cdatabase.h"

#include "src/includes/audioinput.h"
#include "src/includes/audiooutput.h"




class CClient;
class CChannel;

class CServer : public AbstractServer
{

    Q_OBJECT
    public:

    //Audio
    AudioInput * m_audio_in;
    AudioOutput * m_audio_out;




    CServer();


    //Getters
    CDatabase * get_database();

    //Setters
    void set_database(CDatabase * db);


    //Network
    void sendToChannel(const QString &message, int id_channel);         //Send message to a channel
    void sendToClient(const QString &message,CClient * client);         //Send message to a client
    void SendObjectsToClient();                                         //Send channels and clients objects
    void sendToAll(QByteArray out);                                     //Send packet to everyone


    //Server action - To develop
    void changeChannel(int id);
    void quitChannel(int id);
    void joinChannel(int id);
    int whichClient(QTcpSocket * soc);


        //Serialization | Deserialization
        QByteArray Serialize();                                             //Serialize client and channels on the same json document
        void Deserialize(QByteArray in);

        QByteArray SerializeChannels();                                     //Serialize channels into json document then byte array
        QByteArray SerializeClients();                                      //Serialize clients into json document then byte array

        void DeserializeChannels(QByteArray in);                            //Deserialize channels from byte array
        void DeserializeClient(QByteArray in);                              //Deserialize clients from byte array

        void deserializeChannel(QJsonArray & json_array);
        void deserializeClients(QJsonArray & json_array);

        CChannel * deserializeToChannel(QJsonObject json_obj);              //Deserialize channels from json object
        CClient * deserializeToClient(QJsonObject json_obj);                //Deserialize clients from json object


        //Création d'un channel grâce à un nouveau process -
        void create_process();
        void del_process();



    public slots:



    private slots:

        void onNewConnection();                                           //Add client to the server - default no channel           //get data
        void onDisconnectClient();                                        //Disconnecting client - del client from channel list - del client
        void onReceiveData();                                                //Server receive data

    private:

        //Server mode
        QTcpServer *serveur;

        //Database
        CDatabase * m_db;                                                   //Database




};

#endif // CSERVER_H


/*
// Get network interfaces list
QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();

// Interfaces iteration
for (int i = 0; i < ifaces.size(); i++)
{
    // Now get all IP addresses for the current interface
    QList<QNetworkAddressEntry> addrs = ifaces[i].addressEntries();

    // And for any IP address, if it is IPv4 and the interface is active, send the packet
    for (int j = 0; j < addrs.size(); j++)
        if ((addrs[j].ip().protocol() == QAbstractSocket::IPv4Protocol) && (addrs[j].broadcast().toString() != ""))
            udpManager.writeDatagram(packet->data(), packet->length(), addrs[j].broadcast(), 64501);
}*/

