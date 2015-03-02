#include "GameScene.h"

USING_NS_CC;

int GameScene::scorePoints = 0;
float GameScene::speedBullet = 0.001f;
float GameScene::speedMeteor = 0.005f;
float GameScene::speedBackground = -0.01f;
float GameScene::frequencyMeteor = 0.001f;
float GameScene::frequencyBullet = 0.0005f;

GameScene::~GameScene()
{
	delete ship;
	delete meteor;
	delete star;
}

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();

	layer->setPhysicsWorld(scene->getPhysicsWorld());
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	ship = new Ship(this);
	meteor = new Meteor(this);
	star = new Star(this);

	timerMeteor = 0;
	GameScene::setDefaultValue();

	scoreLabel = Label::createWithTTF(std::to_string(GameScene::scorePoints), "Fonts/kenvector_future_thin.ttf", visibleSize.height / 15);
	scoreLabel->setAlignment(TextHAlignment::CENTER);
	scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height - visibleSize.height / 15 + origin.y));

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->addChild(scoreLabel, 1);
	this->setParallaxBackground();
	this->scheduleUpdate();
	return true;
}

void GameScene::setPhysicsWorld(PhysicsWorld *world)
{
	this->sceneWorld = world;
}

void GameScene::setParallaxBackground()
{
	std::srand(time(NULL));
	int backgroundIndex = rand() % 4 + 1;

	__String *backgroundString = __String::createWithFormat("Backgrounds/background%i.png", backgroundIndex);
	auto bg1 = Sprite::create(backgroundString->getCString());
	auto bg2 = Sprite::create(backgroundString->getCString());

	bg1->getTexture()->setTexParameters({ GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT });
	bg1->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
	bg2->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));

	parallaxBg = CCParallaxScrollNode::create();
	parallaxBg->addInfiniteScrollYWithZ(-1, Point(1, 1), Point(0, 0), bg1, bg2, NULL);
	this->addChild(parallaxBg);
}

bool GameScene::onContactBegin(PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	Sprite *aSprite = (Sprite *)a->getNode();
	Sprite *bSprite = (Sprite *)b->getNode();
	Point aPos;
	Point bPos;

	if (aSprite && bSprite)
	{
		aPos = aSprite->getPosition();
		bPos = bSprite->getPosition();
	}

	if ((a->getCollisionBitmask() == COLLISION_SHIP && b->getCollisionBitmask() == COLLISION_METEOR) ||
		(b->getCollisionBitmask() == COLLISION_SHIP && a->getCollisionBitmask() == COLLISION_METEOR))
	{
		auto scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(TransitionMoveInT::create(DELAY_TRANSITION, scene));
	}
	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_METEOR && b->getCollisionBitmask() == COLLISION_BULLET)
	{
		GameScene::incrementScore(1);
		aSprite->removeFromParentAndCleanup(true);
		bSprite->removeFromParentAndCleanup(true);
		meteor->removeMeteor(aSprite);
		ship->getBullet()->removeBullet(bSprite);
		this->star->spawnStarGold(aPos);
	}
	else if (aSprite && bSprite && b->getCollisionBitmask() == COLLISION_METEOR && a->getCollisionBitmask() == COLLISION_BULLET)
	{
		GameScene::incrementScore(1);
		aSprite->removeFromParentAndCleanup(true);
		bSprite->removeFromParentAndCleanup(true);
		meteor->removeMeteor(bSprite);
		ship->getBullet()->removeBullet(aSprite);
		this->star->spawnStarGold(bPos);
	}
	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_SHIP && b->getCollisionBitmask() == COLLISION_STAR_BRONZE)
	{
		GameScene::incrementScore(10);
		bSprite->removeFromParentAndCleanup(true);
		star->removeStar(bSprite);
	}
	else if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_STAR_BRONZE && b->getCollisionBitmask() == COLLISION_SHIP)
	{
		GameScene::incrementScore(10);
		aSprite->removeFromParentAndCleanup(true);
		star->removeStar(aSprite);
	}
	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_SHIP && b->getCollisionBitmask() == COLLISION_STAR_SILVER)
	{
		GameScene::incrementScore(50);
		bSprite->removeFromParentAndCleanup(true);
		star->removeStar(bSprite);
	}
	else if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_STAR_SILVER && b->getCollisionBitmask() == COLLISION_SHIP)
	{
		GameScene::incrementScore(50);
		aSprite->removeFromParentAndCleanup(true);
		star->removeStar(aSprite);
	}
	if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_SHIP && b->getCollisionBitmask() == COLLISION_STAR_GOLD)
	{
		GameScene::incrementScore(100);
		bSprite->removeFromParentAndCleanup(true);
		star->removeStar(bSprite);
	}
	else if (aSprite && bSprite && a->getCollisionBitmask() == COLLISION_STAR_GOLD && b->getCollisionBitmask() == COLLISION_SHIP)
	{
		GameScene::incrementScore(100);
		aSprite->removeFromParentAndCleanup(true);
		star->removeStar(aSprite);
	}

	return true;
}

void GameScene::update(float delta)
{
	this->timerMeteor += delta;
	if (this->timerMeteor > GameScene::frequencyMeteor * this->visibleSize.width)
	{
		this->timerMeteor = 0;
		this->meteor->spawnMeteor();
	}
	this->meteor->update(delta);
	this->star->update(delta);
	this->ship->update(delta);
	this->scoreLabel->setString(std::to_string(GameScene::scorePoints));
	this->parallaxBg->updateWithVelocity(Point(0, GameScene::speedBackground * visibleSize.height), delta);
	GameScene::setDifficulty();
}

void GameScene::incrementScore(int value)
{
	scorePoints += value;
}

void GameScene::setDifficulty()
{
	if (GameScene::scorePoints > 100 && GameScene::scorePoints < 500)
	{
		GameScene::speedMeteor = 0.004f;
		GameScene::speedBackground = -0.02f;
		GameScene::frequencyMeteor = 0.0009f;
		CCLOG("MACH 1");
	} 
	else if (GameScene::scorePoints > 500 && GameScene::scorePoints < 1000)
	{
		GameScene::speedMeteor = 0.003f;
		GameScene::speedBackground = -0.03f;
		GameScene::frequencyMeteor = 0.0008f;
		CCLOG("MACH 2");
	}
	else if (GameScene::scorePoints > 1000 && GameScene::scorePoints < 2000)
	{
		GameScene::speedMeteor = 0.002f;
		GameScene::speedBackground = -0.04f;
		GameScene::frequencyMeteor = 0.0007f;
		CCLOG("MACH 3");
	}
	else if (GameScene::scorePoints > 2000)
	{
		GameScene::speedMeteor = 0.001f;
		GameScene::speedBackground = -0.05f;
		GameScene::frequencyMeteor = 0.0006f;
		CCLOG("MACH 4");
	}
}

void GameScene::setDefaultValue()
{
	GameScene::scorePoints = 0;
	GameScene::speedBullet = 0.001f;
	GameScene::speedMeteor = 0.005f;
	GameScene::speedBackground = -0.01f;
	GameScene::frequencyMeteor = 0.001f;
	GameScene::frequencyBullet = 0.0005f;
}