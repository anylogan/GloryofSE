#include "Core/Sprite/Skill.h"

USING_NS_CC;

Skill *  Skill::createWithSpriteFrameName(const char* spriteFrameName)
{
	Skill *skill = new Skill();
	if (skill && skill->create(spriteFrameName)) {
		skill->autorelease();
		skill->setVisible(false);

		auto body = PhysicsBody::createBox(skill->getContentSize());

		body->setCategoryBitmask(0x01);			//0001
		body->setCollisionBitmask(0x02);		//0010
		body->setContactTestBitmask(0x01);

		skill->setPhysicsBody(body);

		return skill;
	}
	CC_SAFE_DELETE(skill);
	return nullptr;
}

void  Skill::releaseSkillFromHero(Hero* hero)
{
	this->setPosition(hero->getPosition() + Vec2(0, hero->getContentSize().height / 2));
	this->setVisible(true);
	this->unscheduleUpdate();
	this->scheduleUpdate();

}

void Skill::update(float dt)
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(this->getPosition() + velocity * dt));
	if (this->getPosition().y > screenSize.height) {
		//log("isVisible = %d",this->isVisible());
		this->setVisible(false);
		this->unscheduleUpdate();
		this->removeFromParent();
	}
}