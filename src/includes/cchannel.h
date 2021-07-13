/**
 * @file        cchannel.h
 * @brief       Declaration of the class CChannel
 * @details     This class represent a channel
 * @author
 * @version     0.1
 * @date        2020
 * @copyright   GNU Public License.
 */


#ifndef CCHANNEL_H
#define CCHANNEL_H

//QT Includes
#include <QJsonObject>
#include <QUuid>

//Includes
#include "cclient.h"
#include "Client/includes/messagelist.h"
#include "crole.h"


//Class
class CMessage;
class CClient;
class MessageList;


class CChannel
{
    /**
     * @class       CChannel cchannel.h "cchannel.h"
     * @brief       Declaration of the class CChannel
     * @details     This class represent a channel
     * @author
     * @version     0.1
     * @date        2020
     * @note
     * @bug
     * @warning     Une mauvaise utilisation peut faire planter votre application (c'est votre faute)
     * @remark      Une remarque à faire ?
     * @copyright   GNU Public License.
     */

    public:

        //Constructor
        CChannel();
        CChannel(QString name, int id);
        CChannel(QString name, int id, int maxUsers);
        CChannel(QList<CClient*> clients, QString name, int id);
        CChannel(const CChannel & copy);
        ~CChannel() {};

        //Getters
        QList<CClient *> get_clients();
        QString get_name();
        CChannel* get_this();
        int get_id();
        int get_maxUsers();
        int get_nbClients();
        MessageList *getMessagesLists() const;
        QList<crole*> GetChannelRights();

        //Setters
        void set_clients(QList<CClient*> clients);
        void set_name(QString name);
        void set_id(int id);
        void set_maxUsers(int maxUsers);
        void set_nbClients(int nb);
        void set_all(CChannel * c);
        void setMessagesLists(MessageList *messagesLists);

        //Serialize | Deserialize
        QJsonObject serializeToObj();
        void deserialize(QJsonObject json_obj);

        //Action
        void addUser(CClient * c);
        void delUser(QUuid idUser);

        //Right related
        bool IsUserAllowed(CClient* p_client, int p_right);
    signals:


    private slots:


    private:

        QString m_name;                        //!< m_name is the name of the channel
        int m_nbClients;                       //!< m_nbClients is the current number of clients in the channel
        int m_maxUsers;                        //!< m_maxUsers is the maximum number of users in a channel
        int m_id;                              //!< m_id is the ID of the channel
        QList<CClient*> m_clients;             //!< m_clients is the list of clients in the channel
        MessageList * m_messagesLists;         //!< m_messagesLists is the list of messages associate to the channel
        QList<crole*> m_roles;
};

#endif // CCHANNEL_H
