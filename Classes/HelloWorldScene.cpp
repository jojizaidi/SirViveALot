#include "HelloWorldScene.h"
#include "Player.h"
#include "CameraController.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
  
    
    allowMovement = false;
    locationToMove = Point::ZERO;
    
    
    winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    InitIsland();
    
    //need to be moved in a seperate class
    this->addChild(Player::getInstance(),5);
    Player::getInstance()->setPosition(winSize.width/2, winSize.height/2);
    
    this->addChild(CameraController::getMainCamera());
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
    listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
    
    
    
    Sprite *test = Sprite::create("HelloWorld.png");
    this->addChild(test);
    test->setPositionZ(-80);
    test->setCameraMask((unsigned int)CameraFlag::USER1);
    return true;
}


void HelloWorld::InitIsland()
{
    theIsland = Sprite3D::create("mountain1.c3b");
    theIsland->setTexture("mountainsUV.png");
    theIsland->setPosition(Vec2(winSize.width/2 , winSize.height/2));
    theIsland->setCameraMask((unsigned int)CameraFlag::USER1);
    this->addChild(theIsland);
    theIsland->setScale(5);
}

void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    Point location = touches[0]->getLocation();
    locationToMove = location;

    allowMovement = true;
    
}


void HelloWorld::update(float dt)
{
    //need to be moved in a seperate class// for test only!

    CameraController::getMainCamera()->setPositionX(CameraController::getMainCamera()->getPositionX() + (Player::getInstance()->getPositionX()- CameraController::getMainCamera()->getPositionX())* dt * 3);
    CameraController::getMainCamera()->setPositionY(CameraController::getMainCamera()->getPositionY() + (Player::getInstance()->getPositionY() - 200- CameraController::getMainCamera()->getPositionY())* dt * 3);
    CameraController::getMainCamera()->setPositionZ(CameraController::getMainCamera()->getPositionZ() + (400 - CameraController::getMainCamera()->getPositionZ())* dt);
    CameraController::getMainCamera()->lookAt(Vec3(CameraController::getMainCamera()->getPositionX() ,  CameraController::getMainCamera()->getPositionY() +200 ,0 ), Vec3(0, 1, 0));

    
    if(Player::getInstance()->getPosition().distance(locationToMove) > 100)
    {
        if(allowMovement)
        {
            Player::getInstance()->setPosition(Player::getInstance()->getPosition().x + 40/25*sinf(CC_DEGREES_TO_RADIANS(Player::getInstance()->getRotation()+180)) , Player::getInstance()->getPosition().y + 40/25 *cosf(CC_DEGREES_TO_RADIANS(Player::getInstance()->getRotation()+180)));
        
            
            
            Player::getInstance()->setRotation(modulus(Player::getInstance()->getRotation()+360, 360));
            
            
            float playerRotation = calcAngle(Player::getInstance()->getPosition(), locationToMove);
           
            if(playerRotation -Player::getInstance()->getRotation() > 200)
            {
                int i = (int)(playerRotation - Player::getInstance()->getRotation())/360;
                playerRotation = playerRotation - (360*(i+1));
                
                
            }
            if(playerRotation - Player::getInstance()->getRotation() < -200)
            {
                int i = (int)(playerRotation - Player::getInstance()->getRotation())/360;
                
                playerRotation = playerRotation + (360*(i+1));
                
            }

            
            float rotationSpeed = 200;
            
            float angleDiffence = -Player::getInstance()->getRotation()+ playerRotation;

            if ( fabs(angleDiffence) < rotationSpeed*dt ) // finished rotation
            {
                Player::getInstance()->setRotation(playerRotation);
            }
            
            else if(angleDiffence  > 0){
                Player::getInstance()->setRotation(Player::getInstance()->getRotation()+ rotationSpeed*dt );
                
            }
            else{
                Player::getInstance()->setRotation(Player::getInstance()->getRotation()- rotationSpeed*dt );
                
            }
        }
    }
    else{
        allowMovement = false;
    }

}


float HelloWorld::modulus(float a, float b)
{
    int result = static_cast<int>( a / b );
    return a - static_cast<float>( result ) * b;
}


float HelloWorld::calcAngle(Point p1, Point p2)
{
    //return CC_RADIANS_TO_DEGREES(atan(fabsf(laser.y - block.y) / fabsf(laser.x - block.x) )) ;
    
    
    Point diff = p2 - p1;
    float rads = atan2f( diff.y, diff.x);
    float degs = CC_RADIANS_TO_DEGREES(rads);
    
    
    //    degs = degs + 360;
    //    degs = modulus(degs, 360);
    //
    degs = 360 - degs;
    
    
    return (degs );
    
    
    //return CC_RADIANS_TO_DEGREES(ccpAngle( block,ccp(240 , 160)));
}
