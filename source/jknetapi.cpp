#include "launcher.h"

namespace JKNetAPI{
	QHostAddress jknethost("");
	bool		available;

	void Init(void){
		QFuture<void> data = QtConcurrent::run([]{
			/*Checking...connecting to main server etc... */
												 });
	}

	QString* Auth(QString &username, QString &password){

		return new QString;
	}

	bool CheckSession(QString &username, QString &session){

		return false;
	}

	bool ChangePassword(QString &username, QString &oldpassword, QString &newpassword){

		return false;
	}

	QString* GetServers(void){

		return new QString;
	}

	QString* DoRequest(QString &module, QString &request){

		return new QString;
	}

	QString* DoRequest(const char *module, const char *request){

		return new QString;
	}
}
