#pragma once
typedef enum {
    RENDERER_VANILLA = 0,
    RENDERER_REND2,
} renderer_t;

namespace Settings{
    extern QString JKFolder; // path to game
    extern QString LauncherPath;
    extern size_t memory; //
    extern bool autoconnect;

    extern int resolutionX;
    extern int resolutionY;
    extern renderer_t render;

    void Save(void);
    void Load(void);

}
