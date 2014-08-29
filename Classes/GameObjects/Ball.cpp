#include "Ball.h"

void Ball::Move(const Vec2& playerPos)
{
    if(!this->isIdle)
    {
        auto winSize = Director::getInstance()->getVisibleSize();
        auto winOrigin = Director::getInstance()->getVisibleOrigin();

        this->setPositionX(this->getPositionX() + speed * dirX);
        this->setPositionY(this->getPositionY() + speed * dirY);

        if(this->getPositionX() < winOrigin.x)
            this->dirX = 1;
        else if(this->getPositionX() + this->getBoundingBox().size.width > winOrigin.x + winSize.width)
            this->dirX = -1;

        if(this->getPositionY() + this->getBoundingBox().size.height > winSize.height + winOrigin.y)
            this->dirY = -1;

        if(this->getPositionY() + this->getBoundingBox().size.height < winOrigin.y) this->isDead = true;
    }
    else
    {
        this->setPositionX(playerPos.x - this->getBoundingBox().size.width / 2);
        this->setPositionY(playerPos.y);
    }
}

void Ball::Collide(int x, int y)
{
    this->dirX *= x;
    this->dirY *= y;
    this->speed += 0.03f;
    this->didCollideLastFrame = true;
}

void Ball::Reset()
{
    this->speed = 3;
    this->dirX = this->dirY = 1;
    this->isIdle = true;
    this->isDead = false;
    this->didCollideLastFrame = false;
}

int Ball::GetDirX() { return this->dirX; }
void Ball::SetDirX(bool left, bool right)
{
    if(left) this->dirX = -1;
    else if(right) this->dirX = 1;
}
