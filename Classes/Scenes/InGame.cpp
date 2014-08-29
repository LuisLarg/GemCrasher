#include "InGame.h"

InGame::~InGame()
{
    this->gems.clear();
    this->removeAllChildren();
}

bool InGame::init()
{
    if(!Scene::init()) return false;

    this->bgColor = LayerColor::create(Color4B(55, 72, 69, 255));
    this->addChild(this->bgColor);

    InitGameObjects();

    InitEventListeners();

    this->scheduleUpdate();

    this->uiContainer = Layer::create();
    this->addChild(uiContainer, 1);

    this->GUI = InGameUI::create();
    this->uiContainer->addChild(this->GUI);

    this->Reset();

    return true;
}

void InGame::InitGameObjects()
{
    this->goContainer = Layer::create();
    this->addChild(goContainer, 0);

    auto sfCacher = SpriteFrameCache::getInstance();
    auto winSize = Director::getInstance()->getVisibleSize();
    auto winOrigin = Director::getInstance()->getVisibleOrigin();

    this->player = PlayerBar::create();
    this->player->setSpriteFrame(sfCacher->getSpriteFrameByName("paddleBlu.png"));
    this->player->setAnchorPoint(Vec2(0, 0));
    this->player->setPosition(Vec2(winSize.width / 2 - this->player->getContentSize().width / 2 + winOrigin.x,
                                   10 + winOrigin.y));
    this->goContainer->addChild(this->player);

    this->ball = Ball::create();
    this->ball->setSpriteFrame(sfCacher->getSpriteFrameByName("ballGrey.png"));
    this->ball->setAnchorPoint(Vec2(0, 0));
    this->goContainer->addChild(this->ball);

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            auto gem = Gem::create();
            gem->setSpriteFrame(sfCacher->getSpriteFrameByName("element_blue_square.png"));
            gem->setPosition(Vec2(59.5f + winOrigin.x + (gem->getContentSize().width * col), 499.4f + winOrigin.y - (gem->getContentSize().height * row)));
            gem->setAnchorPoint(Vec2(0, 0));
            gem->initColliders();

            this->goContainer->addChild(gem);
            this->gems.pushBack(gem);
        }
    }
}

void InGame::InitEventListeners()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Device::setAccelerometerEnabled(true);
    auto accListener = EventListenerAcceleration::create([=](Acceleration *pAcc, Event *pEvent)
    {
            if(pAcc->x > 0.1) { this->moveRight = true; this->moveLeft = false; }
            else if(pAcc->x < -0.1) { this->moveLeft = true; this->moveRight = false; }
            else { this->moveLeft = false; this->moveRight = false; }
    });

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(accListener, this);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [&](Touch* pTouch, Event* pEvent)
    {
        if(this->ball->isIdle)
        {
            this->ball->isIdle = false;
            return true;
        }

        return false;
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode pKeyCode, Event *pEvent)
    {
        if(pKeyCode == EventKeyboard::KeyCode::KEY_BACK) this->GUI->Pause();
    };


#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode pKeyCode, Event *pEvent)
    {
        if(pKeyCode == EventKeyboard::KeyCode::KEY_ESCAPE) this->GUI->Pause();
        if(pKeyCode == EventKeyboard::KeyCode::KEY_SPACE) if(this->ball->isIdle) this->ball->isIdle = false;

        if(pKeyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) this->moveLeft = false;
        else if(pKeyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) this->moveRight = false;
    };
    keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode pKeyCode, Event *pEvent)
    {
        if(pKeyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) this->moveLeft = true;
        else if(pKeyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) this->moveRight = true;
    };
#endif

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void InGame::update(float delta)
{
    if(!this->GUI->pause && !this->GUI->gameOver)
    {
        this->player->Move(this->moveLeft, this->moveRight);

        if(this->ball->isIdle)
            this->ball->SetDirX(this->moveLeft, this->moveRight);

        this->ball->Move(Vec2(this->player->getPositionX() + this->player->getBoundingBox().size.width / 2,
                              this->player->getPositionY() + this->player->getBoundingBox().size.height));

        if(!this->ball->isIdle) CheckCollision();

        if(this->nextLavel) this->ToNextLevel();
        if(this->ball->isDead)
        {
            this->GUI->lifeHUD->setString("Life = " + std::to_string(--this->life));
            this->ball->Reset();
        }

        if(this->life == 0)
        {
            this->GUI->EndGame();
            this->GUI->totalScore->setString(std::to_string(this->score));
        }
    }
    else if(this->GUI->resetGame)
        this->Reset();
}

void InGame::CheckCollision()
{
    auto ballCollider = this->ball->getBoundingBox();
    bool isBallCollisioning = false;

    if(ballCollider.intersectsRect(this->player->UpperLeftCollider()))
    {
        if(!this->ball->didCollideLastFrame)
        {
            if(this->ball->GetDirX() > 0) this->ball->Collide(-1, -1);
            else if(this->ball->GetDirX() < 0) this->ball->Collide(1, -1);
        }

        isBallCollisioning = true;
    }
    else if(ballCollider.intersectsRect(this->player->UpperRightCollider()))
    {
        if(!this->ball->didCollideLastFrame)
        {
            if(this->ball->GetDirX() > 0) this->ball->Collide(1, -1);
            else if(this->ball->GetDirX() < 0) this->ball->Collide(-1, -1);
        }

        isBallCollisioning = true;
    }

    if(ballCollider.intersectsRect(this->player->RightCollider()) ||
       ballCollider.intersectsRect(this->player->LeftCollider()))
    {
        if(!this->ball->didCollideLastFrame)
            this->ball->Collide(-1, 1);

        isBallCollisioning = true;
    }

    bool atLeastAGemActive = false;
    for(Gem* gem: this->gems)
    {
        if(!gem->active) continue;

        atLeastAGemActive = true;

        bool isGemCollisioning = false;

        if(ballCollider.intersectsRect(gem->upperCollider) ||
           ballCollider.intersectsRect(gem->lowerCollider))
        {
            ball->Collide(1, -1);

            gem->active = false;
            gem->setVisible(false);

            isGemCollisioning = true;
        }

        if(ballCollider.intersectsRect(gem->leftCollider) ||
                ballCollider.intersectsRect(gem->rightCollider))
        {
            ball->Collide(-1, 1);

            gem->active = false;
            gem->setVisible(false);

            isGemCollisioning = true;
        }

        if(isGemCollisioning)
        {
            this->GUI->scoreHUD->setString("Score = " + std::to_string((this->score += 10)));
            break;
        }
    }

    this->nextLavel =! atLeastAGemActive;

    this->ball->didCollideLastFrame = isBallCollisioning;
}

void InGame::Reset()
{
    this->ToNextLevel();

    this->score = 0;
    this->life = 3;

    this->GUI->scoreHUD->setString("Score = " + std::to_string(this->score));
    this->GUI->lifeHUD->setString("Life = " + std::to_string(this->life));
}

void InGame::ToNextLevel()
{
    this->GUI->Reset();

    this->ball->Reset();

    for(Gem* gem: this->gems)
        gem->Reset();

    this->nextLavel = false;
}
