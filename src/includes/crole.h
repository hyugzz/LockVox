#ifndef CROLE_H
#define CROLE_H

#include <QString>
#include <QList>
#include <QDebug>

class crole
{
public:
    crole();
    crole(crole* p_father);

    ~crole(){};

    //Parent+enfants
    void AddFather(crole* p_father);
    void AddChild(crole* p_child);
    void DelChild(QString p_name);
    void DelChild(int p_id);

    //Getter+Setter
    void SetWrite(bool v);
    void SetSpeak(bool v);
    void SetKick(bool v);
    void SetDelete(bool v);
    void SetSee(bool v);
    void SetMute(bool v);

    void SetId(int p_id);
    void SetName(QString p_name);

    int GetId();
    QString GetName();
    bool GetWrite();
    bool GetSpeak();
    bool GetKick();
    bool GetDelete();
    bool GetSee();
    bool GetMute();

    //Util functions
    bool IsAllowed(int right);

    enum{
        Write,
        Speak,
        Kick,
        Delete,
        See,
        Mute
    };
private:
    int m_id;                   //ID du role
    QString m_name;             //Nom du role
    crole* m_father;            //Le parent du role
    QList<crole*> m_childrens;  //Les enfants du role
    /*Chaque bool correspond à un droit associé au groupe*/
    bool m_write;
    bool m_speak;
    bool m_kick;
    bool m_delete;
    bool m_see;
    bool m_mute;

};

#endif // CROLE_H
