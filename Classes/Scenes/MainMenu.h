#ifndef MAINMENU_H
#define MAINMENU_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class MainMenu : public Scene
{
public:
    virtual ~MainMenu();

    CREATE_FUNC(MainMenu);

protected:
    virtual bool init();

private:
    LayerColor *bgColor;

    void ExitApp(void);
};

#endif // MAINMENU_H
