#ifndef INGAMEUI_H
#define INGAMEUI_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class InGameUI : public Layer
{
public:
    CREATE_FUNC(InGameUI);

    void Pause();
    void EndGame();

    void Reset();

    ui::Text *scoreHUD;
    ui::Text *lifeHUD;
    ui::Text *totalScore;

    bool pause;
    bool gameOver;
    bool resetGame;

protected:
    virtual bool init();

private:
    ui::ImageView *pauseWindow;
    ui::Text *pauseWinLabel;
    ui::Button *keepPlayingButton;
    ui::Button *giveUpButton;

    ui::ImageView *gameOverWindow;
    ui::Text *gameOverWinLabel;
    ui::Text *finalScore;
    ui::Button *replayButton;
    ui::Button *ExitButton;

    void CreatePauseWindow();
    void CreateGameOverWindow();
    void ShowPauseWindow(bool);
    void ShowGameOverWindow(bool);
};

#endif // INGAMEUI_H
