#include "launcher.h"
#include <QRegExp>

#define SERVER_TIMEOUT 5000

ServerAPI::ServerAPI(QString &ip, quint16 port){
	this->ip = ip;
	this->port = port;

	if (this->ip.isNull() || this->port == 0) return;

	commsocket = new QUdpSocket();
	commsocket->bind();

	GetType(); // check server :d
}

ServerAPI::ServerAPI(QHostAddress &ip, quint16 port){
	this->ip = ip;
	this->port = port;

	if (this->ip.isNull() || this->port == 0) return;

	commsocket = new QUdpSocket();
	commsocket->bind();


	GetType(); // check server :d
}

ServerAPI::~ServerAPI(){
	delete commsocket;
}

ServerAPI::ServerType ServerAPI::GetType(void){ // JKNet Servers
	if (ip.isNull()) return SERVER_NULL;
	const char *str = "\xFF\xFF\xFF\xFFjknet gettype";

	commsocket->writeDatagram(str, ip, port);
	QTime sendtime = QTime::currentTime();
	sendtime.addMSecs(SERVER_TIMEOUT);

	while (!commsocket->hasPendingDatagrams()) {
		if (sendtime <= QTime::currentTime()) return SERVER_NULL;
	}
	while (commsocket->hasPendingDatagrams()){ // xddd
			int len = commsocket->pendingDatagramSize();
			char *response = (char *)malloc(len);
			memset(response, 0, len);

			QHostAddress sender;
			quint16 senderPort;
			commsocket->readDatagram(response, len, &sender, &senderPort);
			if (/*(sender != ip) ||*/ (senderPort != port)){
				continue;
			}

			QString data(response);
			DecodeMessage(data);
			/*
			
			
			
			*/
	}

	return SERVER_NORMAL;
}

QMap<QString, QString>* ServerAPI::GetStatus(void){
	if (ip.isNull()) return nullptr;

	QMap<QString, QString>* map;
	const char *str = "\xFF\xFF\xFF\xFFgetstatus";

	commsocket->writeDatagram(str, ip, port);

	QTime sendtime = QTime::currentTime();
	sendtime.addMSecs(SERVER_TIMEOUT);

	while (!commsocket->hasPendingDatagrams()) {
		if (sendtime <= QTime::currentTime()) return nullptr;
	}
	while (commsocket->hasPendingDatagrams()){ // xddd
		int len = commsocket->pendingDatagramSize();
		char *response = (char *)malloc(len);
		memset(response, 0, len);
		QHostAddress sender;
		quint16 senderPort;
		commsocket->readDatagram(response, len, &sender, &senderPort);
		if (/*(sender != ip) ||*/ (senderPort != port)){
			continue;
		}
		map = new QMap < QString, QString >;

		QString data(response);
		DecodeMessage(data);
		QChar delim('\\');
		QStringList list = data.split(delim);
		for (int i = 1; i < list.count(); i++ , i++){ // i++ tw0 times
			map->insert(list[i], list[i + 1]);
		}
	}
	return map; ///
}

QMap<QString, QString>* ServerAPI::GetInfo(void){
	if (ip.isNull()) return nullptr;

	QMap<QString, QString>* map;
	const char *str = "\xFF\xFF\xFF\xFFgetinfo";

	commsocket->writeDatagram(str, ip, port);

	QTime sendtime = QTime::currentTime();
	sendtime.addMSecs(SERVER_TIMEOUT);

	while (!commsocket->hasPendingDatagrams()) {
		if (sendtime <= QTime::currentTime()) return nullptr;
	}
	while (commsocket->hasPendingDatagrams()){ // xddd
		int len = commsocket->pendingDatagramSize();
		char *response = (char *)malloc(len);
		memset(response, 0, len);
		QHostAddress sender;
		quint16 senderPort;
		commsocket->readDatagram(response, len, &sender, &senderPort);
		if (/*(sender != ip) ||*/ (senderPort != port)){
			continue;
		}
		map = new QMap < QString, QString >;

		QString data(response);
		DecodeMessage(data);
		QChar delim('\\');
		QStringList list = data.split(delim);
		for (int i = 1; i < list.count(); i++, i++){ // i++ tw0 times
			map->insert(list[i], list[i + 1]);
		}
	}
	return map; ///
}

void ServerAPI::SendCommand(QString &command){
	if (ip.isNull()) return;
	EncodeMessage(command);
	commsocket->writeDatagram(command.toLocal8Bit(), ip, port);
}

int ServerAPI::Ping(void){
	if (ip.isNull()) return -1;

	const char *str = "\xFF\xFF\xFF\xFFjknet ping";

	commsocket->writeDatagram(str, ip, port);

	QTime sendtime = QTime::currentTime();
	int  receivetime = 0;
	sendtime.addMSecs(SERVER_TIMEOUT);
	sendtime.start();

	while (!commsocket->hasPendingDatagrams()) { 
		if (sendtime<= QTime::currentTime()) return -1;
	}
	while (commsocket->hasPendingDatagrams()){ // xddd
		int len = commsocket->pendingDatagramSize();
		receivetime = sendtime.elapsed();
		QHostAddress sender;
		quint16 senderPort;
		commsocket->readDatagram(NULL, len, &sender, &senderPort);
		if ((sender != ip) || (senderPort != port)){
			receivetime = 0; //still zero
			continue;
		}
	}
	return receivetime;
}

void ServerAPI::EncodeMessage(QString &message){
	message.insert(0, QString("\xFF\xFF\xFF\xFF"));
}

void ServerAPI::DecodeMessage(QString &message){
	message.replace(0, 4, "");
}