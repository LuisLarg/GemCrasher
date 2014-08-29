#include "Credits.h"

bool Credits::init()
{
    if(!Scene::init()) return false;

    this->bgColor = LayerColor::create(Color4B(55, 72, 69, 255));
    this->addChild(this->bgColor);

    auto winOrigin = Director::getInstance()->getVisibleOrigin();

    auto title = ui::Text::create("Kudos To", "fonts/square.ttf", 60);
    title->setPosition(Vec2(26.2f + winOrigin.x, 495 + winOrigin.y));
    title->setAnchorPoint(Vec2(0, 0));
    title->setTextHorizontalAlignment(TextHAlignment::CENTER);
    title->setColor(Color3B::BLACK);
    this->addChild(title);

    auto programmerTitle = ui::Text::create("Programmer", "fonts/mini_square.ttf", 40);
    programmerTitle->setPosition(Vec2(60 + winOrigin.x, 369 + winOrigin.y));
    programmerTitle->setAnchorPoint(Vec2(0, 0));
    programmerTitle->setTextHorizontalAlignment(TextHAlignment::CENTER);
    programmerTitle->setColor(Color3B::BLACK);
    this->addChild(programmerTitle);

    auto programmerName = ui::Text::create("Luis Larghi", "fonts/high_square.ttf", 40);
    programmerName->setPosition(Vec2(121.2f + winOrigin.x, 322.2f + winOrigin.y));
    programmerName->setAnchorPoint(Vec2(0, 0));
    programmerName->setTextHorizontalAlignment(TextHAlignment::CENTER);
    programmerName->setColor(Color3B::BLACK);
    this->addChild(programmerName);

    auto assetsTitle = ui::Text::create("All Assets", "fonts/mini_square.ttf", 40);
    assetsTitle->setPosition(Vec2(80 + winOrigin.x, 250.9f + winOrigin.y));
    assetsTitle->setAnchorPoint(Vec2(0, 0));
    assetsTitle->setTextHorizontalAlignment(TextHAlignment::CENTER);
    assetsTitle->setColor(Color3B::BLACK);
    this->addChild(assetsTitle);

    auto assetsName = ui::Text::create("Kenney.nl", "fonts/high_square.ttf", 40);
    assetsName->setPosition(Vec2(126.2f + winOrigin.x, 204.2f + winOrigin.y));
    assetsName->setAnchorPoint(Vec2(0, 0));
    assetsName->setTextHorizontalAlignment(TextHAlignment::CENTER);
    assetsName->setColor(Color3B::BLACK);
    this->addChild(assetsName);

    auto MainMenuButton = ui::Button::create("buttonDefault.png", "buttonSelected.png", "", ui::Widget::TextureResType::PLIST);
    MainMenuButton->setPosition(Vec2(92.5f + winOrigin.x, 52.4f + winOrigin.y));
    MainMenuButton->setAnchorPoint(Vec2(0, 0));
    MainMenuButton->setTouchEnabled(true);
    MainMenuButton->setTitleText("Go Back");
    MainMenuButton->setTitleFontSize(30);
    MainMenuButton->setTitleColor(Color3B::BLACK);
    MainMenuButton->setTitleFontName("fonts/high_square.ttf");
    MainMenuButton->addTouchEventListener([=](Ref *pRef, ui::Widget::TouchEventType pType)
    {
        if(pType == ui::Widget::TouchEventType::ENDED) Director::getInstance()->popScene();
    });
    this->addChild(MainMenuButton);

    return true;
}
