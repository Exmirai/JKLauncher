#include "launcher.h"

QMap<int, Modification*> modlist;

QString Modification::currentmod;
QString Modification::currentrender;

Modification::Modification(int id){

	modlist[id] = this;
}

Modification::~Modification(){


}

void Modification::Enable(){
	this->enabled = true;

	QFile *file = new QFile(Settings::JKFolder + "base" + this->filename + ".pk3");
	if (!file->exists) return; /// 0.0
	file->rename(this->filename + ".pk3_disabled");
}

void Modification::Disable(){
	this->enabled = false;

	QFile *file = new QFile(Settings::JKFolder + "base" + this->filename + ".pk3_disabled");
	if (!file->exists) return; /// 0.0
	file->rename(this->filename + ".pk3");
}

bool Modification::Compatible(int id){
	if (this->notcompatiblewith.contains(id)){
		return false;
	}
	return true;
}

Modification* Modification::GetMod(int id){
	return modlist[id];
}

void Modification::Init(void){
	if (JKNetAPI::available){
		QString *data = JKNetAPI::DoRequest("workshop", "get");

	}

}

void Modification::CheckForUpdate(void){
	if (JKNetAPI::available){
		QString data;
		Q_FOREACH(Modification *mod, modlist){
			data.append(mod->id + ",");
		}
		QString *answer = JKNetAPI::DoRequest("workshop", "update");
		QStringList list = answer->split(QChar(','));
		Q_FOREACH(QString id, list){
			Modification *mod = GetMod(id.toInt());
			if (mod != nullptr){
				mod->updateavailable = true;
			}
		}
	}

}