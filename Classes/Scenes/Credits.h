#ifndef CREDITS_H
#define CREDITS_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class Credits : public Scene
{
public:
    CREATE_FUNC(Credits);

protected:
    virtual bool init();

private:
    LayerColor *bgColor;
};

#endif // CREDITS_H
