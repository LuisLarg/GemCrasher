#include "PlayerBar.h"

bool PlayerBar::init()
{
    if(!Sprite::init()) return false;

    this->speed = 5;

    return true;
}

void PlayerBar::Move(bool left, bool right)
{
    auto winSize = Director::getInstance()->getVisibleSize();
    auto winOrigin = Director::getInstance()->getVisibleOrigin();

    if(left)
    {
        if((this->getPositionX() + this->getBoundingBox().size.width / 2) - this->speed > winOrigin.x)
            this->setPositionX(this->getPositionX() - this->speed);
    }
    else if(right)
    {
        if(this->getPositionX() + this->getBoundingBox().size.width / 2 + this->speed <
           winOrigin.x + winSize.width)
            this->setPositionX(this->getPositionX() + this->speed);
    }
}

Rect PlayerBar::UpperLeftCollider()
{
    Rect upperLeftCollider;

    upperLeftCollider.setRect(this->getPositionX(),
                              this->getPositionY() + this->getBoundingBox().size.height - 1,
                              this->getBoundingBox().size.width / 2,
                              1);

    return upperLeftCollider;
}

Rect PlayerBar::UpperRightCollider()
{
    Rect upperRightCollider;

    upperRightCollider.setRect(this->getPositionX() + this->getBoundingBox().size.width / 2,
                               this->getPositionY() + this->getBoundingBox().size.height - 1,
                               this->getBoundingBox().size.width / 2,
                               1);

    return upperRightCollider;
}

Rect PlayerBar::RightCollider()
{
    Rect rightCollider;

    rightCollider.setRect(this->getPositionX() + this->getBoundingBox().size.width - 1,
                          this->getPositionY(),
                          1,
                          this->getBoundingBox().size.height - 1);

    return rightCollider;
}

Rect PlayerBar::LeftCollider()
{
    Rect leftCollider;

    leftCollider.setRect(this->getPositionX(),
                         this->getPositionY(),
                         1,
                         this->getBoundingBox().size.height - 1);

    return leftCollider;
}
