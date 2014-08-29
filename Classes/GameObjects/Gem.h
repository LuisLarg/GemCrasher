#ifndef GEM_H
#define GEM_H

#include "cocos2d.h"

USING_NS_CC;

class Gem : public Sprite
{
public:
    CREATE_FUNC(Gem);

    Rect upperCollider;
    Rect leftCollider;
    Rect rightCollider;
    Rect lowerCollider;

    void initColliders();
    void Reset();

    bool active;
};

#endif // GEM_H
