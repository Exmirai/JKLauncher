#include "launcher.h"
#include "json/cJSON.h"
#include <QFileDialog>


namespace Settings
{
    const char settingsFileName[] = "settings.dat";

    QString JKFolder; // path to game
    QString LauncherPath;
    size_t memory = 1024; //
    bool autoconnect = false; // autoconnect to JKNet Hub [override serverlist]

    int resolutionX = 640;
    int resolutionY = 480;

    renderer_t renderer = RENDERER_VANILLA;

    static bool isFirstStart = false;

    static void FirstStart(void)
    {
        if (!isFirstStart)
            return;

        JKFolder = QFileDialog::getExistingDirectory(nullptr, QString("Select path to game"), Settings::LauncherPath);
    }


    void Save(void)
    {
        cJSON *json = cJSON_CreateObject(), *node, *temp;
        FILE *instance = fopen(settingsFileName, "w");

        if (!instance)
        {
            return;
        }

        //Actualy serializing
        node = cJSON_CreateObject();
        cJSON_AddStringToObject(node, "gamepath", QStringTChar(JKFolder));
        cJSON_AddIntegerToObject(node, "memory", memory);
        cJSON_AddIntegerToObject(node, "renderer", renderer);
        cJSON_AddIntegerToObject(node, "resolutionX", resolutionX);
        cJSON_AddIntegerToObject(node, "resolutionY", resolutionY);
        cJSON_AddBooleanToObject(node, "autoconnect", autoconnect);


        cJSON_AddItemToObject(json, "settings", node);

        node = cJSON_CreateArray();

        foreach(Profile *pro, profile_list)
        {
            temp = cJSON_CreateObject();
            cJSON_AddStringToObject(temp, "username", QStringTChar(pro->name));
            cJSON_AddStringToObject(temp, "password", QStringTChar(pro->password));

            cJSON_AddItemToArray(node, temp);
        }

        cJSON_AddItemToObject(json, "profiles", node);

        const char *buffer = cJSON_Serialize( json, 1 );
        if ( fwrite(buffer, strlen(buffer), 1, instance ) != strlen(buffer))
        {
            fclose(instance);
            return;
        }

        fclose(instance);
    }

    void Load(void)
    {
        long length;
        char *buffer;
        cJSON *json, *node, *temp;
        FILE *instance;
        // Open

        instance = fopen(settingsFileName, "r");
        if (instance == nullptr){
            isFirstStart = true;
            Settings::FirstStart();
            return;
        }

        instance = fopen(settingsFileName, "r"); // Reopen -.-

        // obtain file size:
        fseek(instance , 0 , SEEK_END);
        length = ftell(instance);
        rewind(instance);

        //Buffer
        buffer = (char *)calloc(length, sizeof(char));
        if ( fread(buffer, 1, length, instance) != length)
        {
            free(buffer);
            fclose(instance);
            return;
        }

        json = cJSON_Parse(buffer);
        free(buffer);
        fclose(instance);

        //Actually Parsing....
        node = cJSON_GetObjectItem(json, "settings");

        temp = cJSON_GetObjectItem(node, "memory");
        memory = cJSON_ToInteger(temp);

        temp = cJSON_GetObjectItem(node, "renderer");
        JKFolder = cJSON_ToString(temp);

        temp = cJSON_GetObjectItem(node, "resolutionX");
        resolutionX = cJSON_ToInteger(temp);

        temp = cJSON_GetObjectItem(node, "resolutionY");
        resolutionY = cJSON_ToInteger(temp);

        temp = cJSON_GetObjectItem(node, "autoconnect");
        autoconnect = cJSON_ToBoolean(temp);

        node = cJSON_GetObjectItem(json, "profiles");

        int numElements = cJSON_GetArraySize( node );
        for (int i = 0; i < numElements && i < MAX_PROFILES; i++ )
        {
            cJSON *element1, *element2;
            temp = cJSON_GetArrayItem(node, i);

            element1 = cJSON_GetObjectItem(temp, "username");
            element2 = cJSON_GetObjectItem(temp, "password");

            new Profile(cJSON_ToString(element1), cJSON_ToString(element2));
        }
    }
}
