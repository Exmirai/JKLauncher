#pragma once


namespace JKNetAPI{
	extern QHostAddress jknethost;
	extern bool		available;
	
	void Init(void);
	QString* Auth(QString &username, QString &password);
	bool CheckSession(QString &username, QString &session);
	bool ChangePassword(QString &username, QString &oldpassword, QString &newpassword);
	QString* GetServers(void);
	
	QString* DoRequest(QString &module, QString &request);
	QString* DoRequest(const char *module, const char *request);
}