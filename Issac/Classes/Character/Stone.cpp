#include"Stone.h"

Stone* Stone::createStone(int type_,Size stoneSize_) {
	Stone *pRet = new(std::nothrow)  Stone();
	if (pRet && pRet->init(type_, stoneSize_))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Stone::init(int stoneType,Size stoneSize) {
	if (!Sprite::init())
	{
		return false;
	}

	Texture2D * texture_stone = Director::getInstance()->getTextureCache()->addImage("res/gfx/grid/rocks_basement.png");
	Sprite * temp_stone;
	//stoneType=0͸���߽磬stoneType=1Сʯͷ��stoneType=2��ʯͷ
	switch (stoneType) {
	case(0):break;
	case(1):temp_stone = Sprite::createWithTexture(texture_stone, Rect(0, 0, 32, 32));
			break;
	case(2):temp_stone = Sprite::createWithTexture(texture_stone, Rect(0, 96, 64, 64));
			break;
	}
	if (stoneType>0) this->addChild(temp_stone);
	auto phyBody = PhysicsBody::createBox(stoneSize, PHYSICSBODY_MATERIAL_DEFAULT);
	//��̬  
	phyBody->setDynamic(false);
	//��������Ļָ���  
	phyBody->getShape(0)->setRestitution(0.0f);
	//���������Ħ����  
	phyBody->getShape(0)->setFriction(1.0f);
	//��ײɸѡ:���ж���ײ��ѡ���Լ���:��tear��ײ����
	phyBody->setCategoryBitmask(0x10);    // 0001_0000
	phyBody->setCollisionBitmask(0xFF);   // 1111_1111
	phyBody->setContactTestBitmask(0x04);	//0000_0100
	//�����������
	this->addComponent(phyBody);
	this->setTag(0); //tag=0ʯͷ
	return true;
}