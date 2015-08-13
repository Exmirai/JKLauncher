#include "launcher.h"


QMap<QString, Profile*> profile_list;

Profile::Profile(const char *name, const char *password){
    this->name = name;
    this->password = password;

    profile_list[name] = this;
}


Profile::Profile(QString &name, QString &password){
    this->name = name;
    this->password = password;

     profile_list[name] = this;
}

Profile::~Profile(){
    profile_list[name] = nullptr;
}

void Profile::GetImage(void){

}

void Profile::UpdateAll(void){


}
