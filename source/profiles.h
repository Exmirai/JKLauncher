#pragma once

#define MAX_PROFILES 3

class Profile{
public:
    QString name;
    QString password;
    QImage  image;

    Profile(QString &name, QString &password);
    Profile(const char *name, const char *password);
    ~Profile();
    void GetImage(void);

    static void UpdateAll(void); // update data(images etc)
};
extern QMap<QString, Profile*> profile_list;
