#pragma once

class Modification{
public:
    typedef enum{
        TYPE_ASSET = 0, //model saber sounds menus etc
        TYPE_GAMECODE,
        TYPE_CGAMECODE,
        TYPE_JAPPSCRIPT,
		TYPE_RENDER,
    }Type;
	int		id;
    QString name;
    QString description;
    QString author;

	QString filename;
    int orgver;
    QString version;

    Type type;

	QList<int> notcompatiblewith; /* mod||asset||render id   e.g 23232,33232,44345,1121, etc*/

    bool enabled;

	Modification(int id);
	~Modification();

	void Enable();
	void Disable();

	bool Compatible(int id);

	bool updateavailable;

	static void CheckForUpdate(void);

	static void Init(void);
	static Modification* GetMod(int id);
	static void GetModificationsList(Type type);

	static QString currentmod;
	static QString currentrender;
};
