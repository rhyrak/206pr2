#ifndef INGAME_H
#define INGAME_H

#include "../entities/player.h"
#include "state.h"
#include "../../main.h"

class InGame : public State
{
private:
    Player player;
    Camera2D camera;
    bool isCameraLocked;
public:
    InGame(Config *config);
    void update() override;
    void render() override;
    char signal() override;
    Player getPlayer();
};

#endif
