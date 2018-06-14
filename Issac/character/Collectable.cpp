#include "Collectable.h"

Collectable *Collectable::createCollectable(int collectableType)
{
	Collectable *pRet = new (std::nothrow) Collectable();
	if (pRet && pRet->init(collectableType))
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

bool Collectable::init(int collectableType)
{
	if (!Sprite::init())
	{
		return false;
	}

	addmoveSpeed = 0;
	addradiusSize = 0;
	addtearSpeed = 0;
	addtearExistTime = 0;
	addhealth = 0;
	addattack = 0;
	enFly = false;

	Sprite* temp_collectableType;
	switch (collectableType)
	{
	case (0):
		break;
	case (1):
		break;
	case (2):
		break;
	}
	this->addChild(temp_collectableType);
	auto phyBody = PhysicsBody::createCircle(12, PHYSICSBODY_MATERIAL_DEFAULT);
	//��̬
	phyBody->setDynamic(false);
	//��������Ļָ���
	phyBody->getShape(0)->setRestitution(0.0f);
	//���������Ħ����
	phyBody->getShape(0)->setFriction(0.0f);
	//��ײ������ɸѡ
	phyBody->setCategoryBitmask(0x80);	// 1000_0000(80)
	phyBody->setCollisionBitmask(0xFF);   // 1111_1111(FF)
	phyBody->setContactTestBitmask(0x09); //0000_1001(09)
	//�����������
	this->addComponent(phyBody);

	this->setTag(9); 
	return true;
}