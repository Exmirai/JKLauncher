#include "launcher.h"
#include "json/cJSON.h"

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
	QDir basedir;
	basedir.setPath(Settings::JKFolder + "base/");
	QStringList modlist = basedir.entryList(QDir::Filter::Readable, QDir::SortFlag::Name);
	if (modlist.size() < 4){
		/* ERROR*/
	}/*assets0-3.pk3*/
	Q_FOREACH(QString name, modlist){
		if (name.contains(QRegExp("assets[0-4].pk3"))) continue;
		name.chop(3); //purge extension
		QFile *file = new QFile(Settings::JKFolder + "base" + name + ".json");
		QByteArray data = file->readAll();

		cJSON *root = cJSON_Parse(data.toStdString().c_str()), *temp;
		if (!root) continue; /* WARNING*/

		temp = cJSON_GetObjectItem(root, "id");
		Modification *mod = new Modification(cJSON_ToInteger(temp));

		temp = cJSON_GetObjectItem(root, "author");
		mod->author = cJSON_ToString(temp);

		temp = cJSON_GetObjectItem(root, "description");
		mod->description = cJSON_ToString(temp);

		temp = cJSON_GetObjectItem(root, "notcompatiblewith");
		QStringList list = QString(cJSON_ToString(temp)).split(QChar(','));
		Q_FOREACH(QString num, list){
			mod->notcompatiblewith.push_back(num.toInt());
		}

		temp = cJSON_GetObjectItem(root, "name");
		mod->name = cJSON_ToString(temp);

		temp = cJSON_GetObjectItem(root, "version");
		mod->version = cJSON_ToInteger(temp);

		cJSON_Delete(root);
		delete file;
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

void Modification::GetModificationsList(Type type){


}