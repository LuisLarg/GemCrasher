#include "InGameUI.h"

bool InGameUI::init()
{
    if(!Layer::init()) return false;

    auto winOrigin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getWinSize();

    this->scoreHUD = ui::Text::create("", "fonts/mini_square.ttf", 20);
    this->scoreHUD->setAnchorPoint(Vec2(0, 1));
    this->scoreHUD->setPosition(Vec2(winOrigin.x + 20, winOrigin.y + winSize.height - 20));
    this->addChild(this->scoreHUD);

    this->lifeHUD = ui::Text::create("", "fonts/mini_square.ttf", 20);
    this->lifeHUD->setAnchorPoint(Vec2(1, 1));
    this->lifeHUD->setPosition(Vec2(winOrigin.x + winSize.width - 20, winOrigin.y + winSize.height - 20));
    this->addChild(this->lifeHUD);

    this->CreatePauseWindow();
    this->CreateGameOverWindow();

    return true;
}

void InGameUI::Pause()
{
    this->pause =! this->pause;

    this->ShowPauseWindow(this->pause);
}

void InGameUI::EndGame()
{
    this->gameOver = true;

    this->ShowGameOverWindow(true);
}

void InGameUI::CreatePauseWindow()
{
    auto winOrigin = Director::getInstance()->getVisibleOrigin();

    this->pauseWindow = ui::ImageView::create("buttonSelected.png", ui::Widget::TextureResType::PLIST);
    this->pauseWindow->setAnchorPoint(Vec2(0, 0));
    this->pauseWindow->setScale9Enabled(true);
    this->pauseWindow->setContentSize(Size(280, 300));
    this->pauseWindow->setPosition(Vec2(winOrigin.x + 47.5f, winOrigin.y + 150));
    this->pauseWindow->setColor(Color3B(150, 150, 150));
    this->pauseWindow->setVisible(false);
    this->addChild(this->pauseWindow);

    this->pauseWinLabel = ui::Text::create("Pause", "fonts/square.ttf", 50);
    this->pauseWinLabel->setAnchorPoint(Vec2(0, 0));
    this->pauseWinLabel->setPosition(Vec2(winOrigin.x + 96.8f, winOrigin.y + 377.1f));
    this->pauseWinLabel->setColor(Color3B::BLACK);
    this->pauseWinLabel->setVisible(false);
    this->addChild(this->pauseWinLabel);

    this->keepPlayingButton = ui::Button::create("buttonDefault.png", "buttonSelected.png", "", ui::Widget::TextureResType::PLIST);
    this->keepPlayingButton->setTouchEnabled(true);
    this->keepPlayingButton->setAnchorPoint(Vec2(0, 0));
    this->keepPlayingButton->setPosition(Vec2(winOrigin.x + 92.5f, winOrigin.y + 283.9f));
    this->keepPlayingButton->setTitleText("Keep Playing");
    this->keepPlayingButton->setTitleFontName("fonts/high_square.ttf");
    this->keepPlayingButton->setTitleFontSize(22);
    this->keepPlayingButton->setTitleColor(Color3B::BLACK);
    this->keepPlayingButton->addTouchEventListener([=](Ref *pRef, ui::Widget::TouchEventType pType)
    {
        if(pType == ui::Widget::TouchEventType::ENDED) Pause();
    });
    this->keepPlayingButton->setVisible(false);
    this->addChild(this->keepPlayingButton);

    this->giveUpButton = ui::Button::create("buttonDefault.png", "buttonSelected.png", "", ui::Widget::TextureResType::PLIST);
    this->giveUpButton->setTouchEnabled(true);
    this->giveUpButton->setAnchorPoint(Vec2(0, 0));
    this->giveUpButton->setPosition(Vec2(winOrigin.x + 92.5f, winOrigin.y + 191.6f));
    this->giveUpButton->setTitleText("Give Up");
    this->giveUpButton->setTitleFontName("fonts/high_square.ttf");
    this->giveUpButton->setTitleFontSize(22);
    this->giveUpButton->setTitleColor(Color3B::BLACK);
    this->giveUpButton->addTouchEventListener([=](Ref *pRef, ui::Widget::TouchEventType pType)
    {
        if(pType == ui::Widget::TouchEventType::ENDED) Director::getInstance()->popScene();
    });
    this->giveUpButton->setVisible(false);
    this->addChild(this->giveUpButton);
}

void InGameUI::CreateGameOverWindow()
{
    auto winOrigin = Director::getInstance()->getVisibleOrigin();

    this->gameOverWindow = ui::ImageView::create("buttonSelected.png", ui::Widget::TextureResType::PLIST);
    this->gameOverWindow->setAnchorPoint(Vec2(0, 0));
    this->gameOverWindow->setScale9Enabled(true);
    this->gameOverWindow->setContentSize(Size(280, 397.8f));
    this->gameOverWindow->setPosition(Vec2(winOrigin.x + 47.5f, winOrigin.y + 105.6f));
    this->gameOverWindow->setColor(Color3B(150, 150, 150));
    this->gameOverWindow->setVisible(false);
    this->addChild(this->gameOverWindow);

    this->gameOverWinLabel = ui::Text::create("Game Over", "fonts/square.ttf", 37);
    this->gameOverWinLabel->setAnchorPoint(Vec2(0, 0));
    this->gameOverWinLabel->setPosition(Vec2(winOrigin.x + 69.5f, winOrigin.y + 438.1f));
    this->gameOverWinLabel->setColor(Color3B::BLACK);
    this->gameOverWinLabel->setVisible(false);
    this->addChild(this->gameOverWinLabel);

    this->finalScore = ui::Text::create("Final Score", "fonts/high_square.ttf", 45);
    this->finalScore->setAnchorPoint(Vec2(0, 0));
    this->finalScore->setPosition(Vec2(winOrigin.x + 101.7f, winOrigin.y + 376.9f));
    this->finalScore->setColor(Color3B::YELLOW);
    this->finalScore->setVisible(false);
    this->addChild(this->finalScore);

    this->totalScore = ui::Text::create("", "fonts/high_square.ttf", 40);
    this->totalScore->setAnchorPoint(Vec2(0, 0));
    this->totalScore->setPosition(Vec2(winOrigin.x + this->gameOverWindow->getBoundingBox().size.width / 2, winOrigin.y + 335.4f));
    this->totalScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->totalScore->setColor(Color3B::YELLOW);
    this->totalScore->setVisible(false);
    this->addChild(this->totalScore);

    this->replayButton = ui::Button::create("buttonDefault.png", "buttonSelected.png", "", ui::Widget::TextureResType::PLIST);
    this->replayButton->setTouchEnabled(true);
    this->replayButton->setAnchorPoint(Vec2(0, 0));
    this->replayButton->setPosition(Vec2(winOrigin.x + 92.5f, winOrigin.y + 248.9f));
    this->replayButton->setTitleText("Play Again");
    this->replayButton->setTitleFontName("fonts/high_square.ttf");
    this->replayButton->setTitleFontSize(22);
    this->replayButton->setTitleColor(Color3B::BLACK);
    this->replayButton->addTouchEventListener([=](Ref *pRef, ui::Widget::TouchEventType pType)
    {
        if(pType == ui::Widget::TouchEventType::ENDED) this->resetGame = true;
    });
    this->replayButton->setVisible(false);
    this->addChild(this->replayButton);

    this->ExitButton = ui::Button::create("buttonDefault.png", "buttonSelected.png", "", ui::Widget::TextureResType::PLIST);
    this->ExitButton->setTouchEnabled(true);
    this->ExitButton->setAnchorPoint(Vec2(0, 0));
    this->ExitButton->setPosition(Vec2(winOrigin.x + 92.5f, winOrigin.y + 156.6f));
    this->ExitButton->setTitleText("Exit");
    this->ExitButton->setTitleFontName("fonts/high_square.ttf");
    this->ExitButton->setTitleFontSize(22);
    this->ExitButton->setTitleColor(Color3B::BLACK);
    this->ExitButton->addTouchEventListener([=](Ref *pRef, ui::Widget::TouchEventType pType)
    {
        if(pType == ui::Widget::TouchEventType::ENDED) Director::getInstance()->popScene();
    });
    this->ExitButton->setVisible(false);
    this->addChild(this->ExitButton);
}

void InGameUI::ShowPauseWindow(bool visible)
{
    this->pauseWindow->setVisible(visible);
    this->pauseWinLabel->setVisible(visible);
    this->keepPlayingButton->setVisible(visible);
    this->giveUpButton->setVisible(visible);
}

void InGameUI::ShowGameOverWindow(bool visible)
{

    this->gameOverWindow->setVisible(visible);
    this->gameOverWinLabel->setVisible(visible);
    this->finalScore->setVisible(visible);
    this->totalScore->setVisible(visible);
    this->replayButton->setVisible(visible);
    this->ExitButton->setVisible(visible);
}

void InGameUI::Reset()
{
    this->pause = this->gameOver = this->resetGame = false;

    this->ShowPauseWindow(false);
    this->ShowGameOverWindow(false);
}
