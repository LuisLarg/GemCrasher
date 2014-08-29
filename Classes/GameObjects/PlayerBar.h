#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include "cocos2d.h"

USING_NS_CC;

class PlayerBar : public Sprite
{
public:
    CREATE_FUNC(PlayerBar);

    void Move(bool, bool);

    Rect UpperLeftCollider();
    Rect UpperRightCollider();
    Rect LeftCollider();
    Rect RightCollider();

protected:
    virtual bool init();

private:
    unsigned int speed;
};

#endif // PLAYERBAR_H
