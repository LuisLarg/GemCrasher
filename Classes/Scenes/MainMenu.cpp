#include "MainMenu.h"
#include "Credits.h"
#include "InGame.h"

MainMenu::~MainMenu()
{
    this->removeAllChildren();
}

bool MainMenu::init()
{
    if(!Scene::init()) return false;

    this->bgColor = LayerColor::create(Color4B(55, 72, 69, 255));
    this->addChild(this->bgColor);

    auto winOrigin = Director::getInstance()->getVisibleOrigin();

    auto title = ui::Text::create("Gem\nCrasher", "fonts/square.ttf", 65);
    title->setPosition(Vec2(20.9f + winOrigin.x, 418.9f - winOrigin.y));
    title->setAnchorPoint(Vec2(0, 0));
    title->setTextHorizontalAlignment(TextHAlignment::CENTER);
    title->setColor(Color3B::BLACK);
    this->addChild(title);

    auto playButton = ui::Button::create();
    playButton->loadTextures("buttonDefault.png", "buttonSelected.png", "", ui::Widget::TextureResType::PLIST);
    playButton->setPosition(Vec2(92.5f + winOrigin.x, 309.6f + winOrigin.y));
    playButton->setAnchorPoint(Vec2(0, 0));
    playButton->setTouchEnabled(true);
    playButton->setTitleText("Play");
    playButton->setTitleFontSize(30);
    playButton->setTitleColor(Color3B::BLACK);
    playButton->setTitleFontName("fonts/high_square.ttf");
    playButton->addTouchEventListener([](Ref *pRef, ui::Widget::TouchEventType pType)
    {
        if(pType == ui::Widget::TouchEventType::ENDED) Director::getInstance()->pushScene(InGame::create());
    });
    this->addChild(playButton);

    auto creditsButton = ui::Button::create("buttonDefault.png", "buttonSelected.png", "", ui::Widget::TextureResType::PLIST);
    creditsButton->setPosition(Vec2(92.5f + winOrigin.x, 197.2f + winOrigin.y));
    creditsButton->setAnchorPoint(Vec2(0, 0));
    creditsButton->setTouchEnabled(true);
    creditsButton->setTitleText("Credits");
    creditsButton->setTitleFontSize(30);
    creditsButton->setTitleColor(Color3B::BLACK);
    creditsButton->setTitleFontName("fonts/high_square.ttf");
    creditsButton->addTouchEventListener([=](Ref *pRef, ui::Widget::TouchEventType pType)
    {
        if(pType == ui::Widget::TouchEventType::ENDED) Director::getInstance()->pushScene(Credits::create());
    });
    this->addChild(creditsButton);

    auto exitButton = ui::Button::create("buttonDefault.png", "buttonSelected.png", "", ui::Widget::TextureResType::PLIST);
    exitButton->setPosition(Vec2(92.5f + winOrigin.x, 84.7f + winOrigin.y));
    exitButton->setAnchorPoint(Vec2(0, 0));
    exitButton->setTouchEnabled(true);
    exitButton->setTitleText("Exit");
    exitButton->setTitleFontSize(30);
    exitButton->setTitleColor(Color3B::BLACK);
    exitButton->setTitleFontName("fonts/high_square.ttf");
    exitButton->addTouchEventListener([=](Ref *pRef, ui::Widget::TouchEventType pType)
    {
        if(pType == ui::Widget::TouchEventType::ENDED) MainMenu::ExitApp();
    });
    this->addChild(exitButton);

    auto buildVersion = ui::Text::create("Alpha Build", "fonts/mini_square.ttf", 20);
    buildVersion->setPosition(Vec2(30 + winOrigin.x, 25 + winOrigin.y));
    buildVersion->setAnchorPoint(Vec2(0, 0));
    buildVersion->setColor(Color3B::BLACK);
    this->addChild(buildVersion);

    return true;
}

void MainMenu::ExitApp(void)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
