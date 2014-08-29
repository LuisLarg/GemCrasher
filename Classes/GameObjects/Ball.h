#ifndef BALL_H
#define BALL_H

#include "cocos2d.h"

USING_NS_CC;

class Ball : public Sprite
{
public:
    CREATE_FUNC(Ball);

    void Move(const Vec2&);
    void Collide(int, int);

    int GetDirX();
    void SetDirX(bool, bool);

    void Reset();

    bool isIdle;
    bool isDead;
    bool didCollideLastFrame;

private:
    int dirX;
    int dirY;
    float speed;
};

#endif // BALL_H
