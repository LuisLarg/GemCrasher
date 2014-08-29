#include "Gem.h"

void Gem::initColliders()
{
    this->upperCollider.setRect(
                this->getPositionX() + 1,
                this->getPositionY() + this->getBoundingBox().size.height - 1,
                this->getBoundingBox().size.width - 2,
                1);

    this->leftCollider.setRect(
                this->getPositionX(),
                this->getPositionY(),
                1,
                this->getBoundingBox().size.height);

    this->rightCollider.setRect(
                this->getPositionX() + this->getBoundingBox().size.width - 1,
                this->getPositionY(),
                1,
                this->getBoundingBox().size.height);

    this->lowerCollider.setRect(
                this->getPositionX() + 1,
                this->getPositionY(),
                this->getBoundingBox().size.width - 2,
                1);
}

void Gem::Reset()
{
    this->active = true;
    this->setVisible(true);
}
