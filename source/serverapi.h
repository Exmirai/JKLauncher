#pragma once


class ServerAPI : public QObject{
private:
	QUdpSocket *commsocket;

public:
	typedef enum{
		SERVER_NULL = 0,
		SERVER_NORMAL,
		SERVER_JKNET,
	}ServerType;

	QHostAddress ip;
	quint16 port;
	ServerType type;

	ServerAPI(QString &ip, quint16 port = 29070);
	ServerAPI(QHostAddress &ip, quint16 port = 29070);
	~ServerAPI();

	int Ping(void);
	void SendCommand(QString &command);
	QMap<QString, QString>* GetStatus(void);
	QMap<QString, QString>* GetInfo(void);
	ServerType GetType(void);

	static void EncodeMessage(QString &message);
	static void DecodeMessage(QString &message);
};
