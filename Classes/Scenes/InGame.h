#ifndef INGAME_H
#define INGAME_H

#include "cocos2d.h"

#include "../GameObjects/PlayerBar.h"
#include "../GameObjects/Ball.h"
#include "../GameObjects/Gem.h"

#include "InGameUI.h"

USING_NS_CC;

class InGame : public Scene
{
public:
    virtual ~InGame();

    CREATE_FUNC(InGame);

    virtual void update(float delta);

protected:
    virtual bool init();

private:
    LayerColor *bgColor;

    PlayerBar *player;
    Ball *ball;
    Vector<Gem*> gems;

    InGameUI *GUI;
    unsigned int score;
    unsigned int life;

    Layer *goContainer;
    Layer *uiContainer;

    bool moveLeft;
    bool moveRight;

    bool nextLavel;

    void InitGameObjects();
    void InitEventListeners();

    void CheckCollision();

    void Reset();
    void ToNextLevel();
};

#endif // INGAME_H
