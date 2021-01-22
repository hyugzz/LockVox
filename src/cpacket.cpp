#include "src/includes/cpacket.h"

CPacket::CPacket()
{

}

CPacket::CPacket(QString type, QString action) :
m_type(type),m_action(action)
{
    m_client = NULL;
    Serialize();
}



CPacket::CPacket(QByteArray data, CClient * client){
    m_client = client;                                  //Client

    m_data = QJsonDocument::fromJson(data);             //JSON Doc
    m_obj = m_data.object();

    //Set type & action from m_data
    Deserialize();
}

//Getters

QString CPacket::GetType()
{
    return m_type;
}

QString CPacket::GetAction()
{
    return m_action;
}

//Setters

void CPacket::SetType(QString p_type)
{
    m_type = p_type;
}

void CPacket::SetAction(QString p_action)
{
    m_action = p_action;
}

//Text<-->Code

QString CPacket::TypeDecode(QString p_type)
{
    switch (p_type.toInt()) {

    case 0: return "Server";
    case 1: return "Channel";
    case 2: return "User";
    default: return "Invalid code";
    }
}

QString CPacket::ServerDecode(QString p_action)
{
    switch(p_action.toInt()) {
    case 0: return "Connexion";
    case 1: return "Deconnexion";
    case 2: return "Nick";
    case 3: return "Description";
    case 4: return "Ban";
    case 5: return "IPBan";
    case 6: return "Kick";
    default: return "Invalid action";
    }
}

QString CPacket::ChannelDecode(QString p_action)
{
    switch (p_action.toInt()) {
    case 0: return "Connexion";
    case 1: return "Deconnexion";
    case 2: return "text_send";
    case 3: return "text_modif";
    case 4: return "text_del";
    case 5: return "chanv_create";
    case 6: return "chanv_del";
    case 7: return "chanv_rename";
    case 8: return "chanv_setmax";
    case 9: return "chanv_kick";
    case 10: return "chanv_mute";
    case 11: return "chant_create";
    case 12: return "chant_delete";
    case 13: return "chant_rename";
    default: return "Invalid action";
    }
}

QString CPacket::UserDecode(QString p_action)
{
    switch(p_action.toInt()){
    case 0: return "Mute";
    case 1: return "add_friend";
    case 2: return "del_friend";
    case 3: return "msg_friend";
    case 4: return "nick_mod";
    case 5: return "right_mod";
    default: return "Invalid action";
    }
}

char CPacket::TypeEncode(QString p_type)
{
    if(p_type == "Server")
        return 0;
    if(p_type == "Channel")
        return 1;
    if(p_type == "User")
        return 2;
    return 0xFF;
}

char CPacket::ServerEncode(QString p_action)
{
    if(p_action == "Connexion")
        return 0;
    if(p_action == "Deconnexion")
        return 1;
    if(p_action == "Nick")
        return 2;
    if(p_action == "Description")
        return 3;
    if(p_action == "Ban")
        return 4;
    if(p_action == "IPBan")
        return 5;
    if(p_action == "Kick")
        return 6;
    return 0xFF;
}

char CPacket::ChannelEncode(QString p_action)
{
    if(p_action == "Connexion")
        return 0;
    if(p_action == "Deconnexion")
        return 1;
    if(p_action == "text_send")
        return 2;
    if(p_action == "text_modif")
        return 3;
    if(p_action == "text_del")
        return 4;
    if(p_action == "chanv_create")
        return 5;
    if(p_action == "chanv_del")
        return 6;
    if(p_action == "chanv_rename")
        return 7;
    if(p_action == "chanv_setmax")
        return 8;
    if(p_action == "chanv_kick")
        return 9;
    if(p_action == "chanv_mute")
        return 10;
    if(p_action == "chant_create")
        return 11;
    if(p_action == "chant_delete")
        return 12;
    if(p_action == "chant_rename")
        return 13;
    return 0xFF;
}

char CPacket::UserEncode(QString p_action)
{
    if(p_action == "Mute")
        return 0;
    if(p_action == "add_friend")
        return 1;
    if(p_action == "del_friend")
        return 2;
    if(p_action == "msg_friend")
        return 3;
    if(p_action == "nick_mod")
        return 4;
    if(p_action == "right_mod")
        return 5;
    return 0xFF;
}

void CPacket::Serialize(){
    QJsonObject mainObj;

    mainObj.insert("type", m_type);
    mainObj.insert("action", m_action);

    m_obj["mainObj"] = mainObj;
}

QByteArray CPacket::Serialize(CServer* c){
      m_ba = c->Serialize();
      return m_ba;
}


//Answer to a client request
QByteArray CPacket::Serialize(bool isActionValid){
   //Create a JSON Document with m_type & m_action
   QJsonObject obj;

   obj.insert("type", m_type);
   obj.insert("action", m_action);
   obj.insert("isActionValid", isActionValid);

   QJsonDocument jsonDoc(obj);
   qDebug() << jsonDoc;

   m_ba = jsonDoc.toJson();
   return m_ba;
}


//When a new client connected
void CPacket::Serialize_newClient(CClient* client){

   QJsonObject clientObj;
   clientObj.insert("id", client->get_id());
   clientObj.insert("pseudo", client->get_pseudo());
   clientObj.insert("isOnline", client->get_isOnline());
    clientObj.insert("description", client->get_description());
   m_obj["newClient"] = clientObj;
}


//When a new channel is created
void CPacket::Serialize_newChannel(CChannel* channel){

    QJsonObject channelObj;
    channelObj.insert("id", channel->get_id());
    channelObj.insert("name", channel->get_name());
    channelObj.insert("maxUsers", channel->get_maxUsers());

    m_obj["newChannel"] = channelObj;
}

void CPacket::Deserialize(){
    try{

        if(m_obj.contains("mainObj")){
            QJsonObject mainObj = m_obj.value("mainObj").toObject();
            QJsonValue type = mainObj.value("type");
            QJsonValue action = mainObj.value("action");
            m_type = type.toString();
            m_action = action.toString();
        }
    }
    catch(char* e)
    {
        qDebug() << "Error in deserialize : " << e;
    }
}

CClient * CPacket::Deserialize_newClient(){
    try{
        QString name;
        int id;
        bool isOnline;
        QString description;

        if(m_obj.contains("newClient")){
            QJsonObject newClient = m_obj.value("newClient").toObject();
            id = newClient.value("id").toInt();
            name = newClient.value("pseudo").toString();
            isOnline = newClient.value("isOnline").toBool();
            description = newClient.value("description").toString();

            CClient * client = new CClient(id,name,NULL, -1,isOnline, description);
            qDebug() << "Name " << name << "   ID " << id;
            return client;
        }
      }
    catch(char* e)
    {
        qDebug() << "Error in deserialize newClient : " << e;
    }
}

CChannel * CPacket::Deserialize_newChannel(){
    try{
        QString name;
        int id, maxUsers;

        if(m_obj.contains("newChannel")){
            QJsonObject newClient = m_obj.value("newChannel").toObject();
            if(!m_obj.contains("id"))
                throw("eing id");
            id = newClient.value("id").toInt();
            if(!m_obj.contains("name"))
                throw("eing name");
            name = newClient.value("name").toString();
            if(!m_obj.contains("maxUsers"))
                throw("eing maxUsers");
            maxUsers = newClient.value("maxUsers").toInt();

            CChannel * channel = new CChannel(name,id,maxUsers);
            return channel;
        }
        else{
            throw("eing newChannel");
        }
    }
    catch(char* e)
    {
        qDebug() << "Error in deserialize newChannel : " << e;
        return NULL;
    }
}


QList<QString> CPacket::Deserialize_auth()
{
    try {
        QList<QString> info;
        if(m_obj.contains("newAuth"))
        {
            QJsonObject newAuth = m_obj.value("newAuth").toObject();
            info.push_back(newAuth.value("email").toString());
            info.push_back(newAuth.value("pass").toString());
        }
        return info;
    }
    catch(char* e)
    {
        qDebug() << "Error in Deserialize_auth :" << e;
    }
}

void CPacket::Serialize_ID(int chan, int client){

    QJsonObject channelObj;
    channelObj.insert("id_channel", chan);
    channelObj.insert("id_client", client);

    m_obj["id"] = channelObj;

}

void CPacket::Deserialize_ID(){
    try{
        QJsonObject id = m_obj.value("id").toObject();
        id_channel = id.value("id_channel").toInt();
        id_client = id.value("id_client").toInt();
    }
    catch(char* e)
    {
        qDebug() << "Error in deserializeID : " << e;
    }
}


void CPacket::Serialize_auth(CClient* info, int code)
{
    QJsonObject authObj;
    switch(code)
    {
    case 0:{
        authObj.insert("code", code);
        Serialize_newClient(info);
        break;
        }
    case 1:{
        authObj.insert("code", code);
        authObj.insert("reason", "user does not exist");
        break;
        }
    case 2:{
        authObj.insert("code", code);
        authObj.insert("reason", "user already connected");
        break;
        }
    case 3:{
        authObj.insert("code", code);
        authObj.insert("reason", "bad password");
        break;
        }
    }
    m_obj["newAuth"] = authObj;
}

void CPacket::Serialize_authReq(QString email, QString pass)
{
    QJsonObject credsObj;
    credsObj.insert("email", email);
    credsObj.insert("pass", pass);
    m_obj["newAuth"] = credsObj;
}

CClient* CPacket::Deserialize_authAns()     //Retourne NULL ou un client vide avec erreur en description
{
    try{
        int code;
        CClient* tmp;
        QString err;
        if(m_obj.contains("newAuth"))
        {
            QJsonObject newAuth = m_obj.value("newAuth").toObject();
            code = newAuth.value("code").toInt();
            switch(code){
            case 0:{
                tmp = Deserialize_newClient();
                return tmp;         //On renvoie les infos client
            }
            case 1:
            case 2:
            case 3:
            {
                err = newAuth.value("reason").toString();
                tmp = new CClient(-1, "NULL", NULL, -1, false, err);    //On renvoie l'erreur par la description
            }
            default:
                return NULL;    //bad packet
            }
        }
    }
    catch(char* e)
    {
        qDebug() << "Error in Deserialize_authAns : " << e;
        return NULL;
    }
}

//UI
