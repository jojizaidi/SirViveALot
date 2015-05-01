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
    InitLight();
    
    
    
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
    
    auto s = Director::getInstance()->getWinSize();
    
    Camera* hudCamera = Camera::createOrthographic(s.width, s.height, 1, 1000);
    this->addChild(hudCamera);
    hudCamera->setCameraFlag(CameraFlag::USER2);

    hudLayer = Layer::create();
    this->addChild(hudLayer);
    hudLayer->setCameraMask((unsigned int)CameraFlag::USER2);
    bgJoystick = Sprite::create("dpadbase.png");
    hudLayer->addChild(bgJoystick,5);
    bgJoystick->setPosition(50,50);
    
        
    bgJoystick->setScale(0.4);
    bgJoystick->setPosition(100,100);
    joystick = Sprite::create("dpadmid.png");
    hudLayer->addChild(joystick,6);
    joystick->setScale(0.3);

    

    return true;
}


void HelloWorld::InitIsland()
{
//    theIsland = Sprite3D::create("mountain1.c3b");
//    theIsland->setTexture("mountainsUV.png");
//    theIsland->setPosition3D((Vec3(winSize.width/2 , winSize.height/2, - 100)));
//    theIsland->setCameraMask((unsigned int)CameraFlag::USER1);
//    this->addChild(theIsland);
//    theIsland->setScale(5);
    
    terrainCamera = Camera::createPerspective(60, (GLfloat)winSize.width/winSize.height, 1, 2000);
    terrainCamera->setPosition3D(Vec3(0, 0, 200));
    terrainCamera->lookAt(Vec3(0, 200, 0), Vec3(0, 1, 0));
    terrainCamera->setCameraFlag(CameraFlag::USER2);//USER1 is the main camera
    this->addChild(terrainCamera);
    //terrainCamera->setPositionX(terrainCamera->getPositionX() + (Player::getInstance()->getPositionX()- mainCamera->getPositionX()));
    //terrainCamera->setPositionY(terrainCamera->getPositionY() + (Player::getInstance()->getPositionY() - 200- mainCamera->getPositionY()));
    
    
    Sprite *test = Sprite::create("HelloWorld.png");
    test->setPosition(Vec2(winSize.width/2 , winSize.height/2));
    test->setScale(10);
    test->setCameraMask((unsigned int)CameraFlag::USER2);
    this->addChild(test);
    //test->setPositionZ(-80);
    
}

void HelloWorld::InitLight()
{
    theLight = DirectionLight::create(Vec3(0, 0, 0), Color3B(200, 200, 200));
    theLight->retain();
    theLight->setEnabled(true);
    addChild(theLight);
    theLight->setCameraMask((unsigned int)CameraFlag::USER2);
}


void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    
       
    Point location = touches[0]->getLocation();
    
    touchLocation = location;
    allowMovement = true;
    
    if(touchLocation.x < winSize.width/2){
        joystick->setPosition(touchLocation);
        bgJoystick->setPosition(touchLocation.x+ 0.01,touchLocation.y + 0.01);
        
        joystick->setVisible(true);
        bgJoystick->setVisible(true);
        
        
        playerRotation =calcAngle(Player::getInstance()->getPosition(), touchLocation) - 90;
    }
}
void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    
    Point location = touches[0]->getLocation();
    touchLocation = location;
    joystick->setPosition(location);
    
    if(joystick->getPosition().distance(bgJoystick->getPosition()) > 30)
    {
        float angle = calcAngle(joystick->getPosition(), bgJoystick->getPosition());
        joystick->setPosition(Point(bgJoystick->getPosition().x  + 30*sin(CC_DEGREES_TO_RADIANS(angle- 90)), bgJoystick->getPosition().y + 30 *cos(CC_DEGREES_TO_RADIANS(angle - 90))));
    }
    
    touchLocation.x = touchLocation.x + Player::getInstance()->getPosition().x - winSize.width/2;
    touchLocation.y = touchLocation.y + Player::getInstance()->getPosition().y - winSize.height/2;
    
    
    playerRotation =calcAngle(bgJoystick->getPosition(), joystick->getPosition()) - 90;
    
    
}


void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    Point location = touches[0]->getLocation();
    locationToMove = location;

    allowMovement = false;
    
}


void HelloWorld::update(float dt)
{
    
    if (theLight->getRotation3D().x == 250)
    {
        theLight->setRotation3D(Vec3( 91 , theLight->getRotation3D().y, theLight->getRotation3D().z ));
    }
    
    theLight->setRotation3D(Vec3(theLight->getRotation3D().x + 1, theLight->getRotation3D().y, theLight->getRotation3D().z));
    
    
    terrainCamera->setPosition(CameraController::getMainCamera()->getPosition());
    
 //   theIsland->setRotation3D(Vec3(theIsland->getRotation3D().x+1, theIsland->getRotation3D().y +1 , theIsland->getRotation3D().z +1));
    //need to be moved in a seperate class// for test only!

    CameraController::getMainCamera()->setPositionX(CameraController::getMainCamera()->getPositionX() + (Player::getInstance()->getPositionX()- CameraController::getMainCamera()->getPositionX())* dt * 3);
    CameraController::getMainCamera()->setPositionY(CameraController::getMainCamera()->getPositionY() + (Player::getInstance()->getPositionY() - 200- CameraController::getMainCamera()->getPositionY())* dt * 3);
    CameraController::getMainCamera()->setPositionZ(CameraController::getMainCamera()->getPositionZ() + (400 - CameraController::getMainCamera()->getPositionZ())* dt);
    CameraController::getMainCamera()->lookAt(Vec3(CameraController::getMainCamera()->getPositionX() ,  CameraController::getMainCamera()->getPositionY() +200 ,0 ), Vec3(0, 1, 0));

//    
//    if(Player::getInstance()->getPosition().distance(locationToMove) > 100)
//    {
//        if(allowMovement)
//        {
//            Player::getInstance()->setPosition(Player::getInstance()->getPosition().x + 40/25*sinf(CC_DEGREES_TO_RADIANS(Player::getInstance()->getRotation()+180)) , Player::getInstance()->getPosition().y + 40/25 *cosf(CC_DEGREES_TO_RADIANS(Player::getInstance()->getRotation()+180)));
//        
//            
//            
//            Player::getInstance()->setRotation(modulus(Player::getInstance()->getRotation()+360, 360));
//            
//            
//            float playerRotation = calcAngle(Player::getInstance()->getPosition(), locationToMove);
//           
//            if(playerRotation -Player::getInstance()->getRotation() > 200)
//            {
//                int i = (int)(playerRotation - Player::getInstance()->getRotation())/360;
//                playerRotation = playerRotation - (360*(i+1));
//                
//                
//            }
//            if(playerRotation - Player::getInstance()->getRotation() < -200)
//            {
//                int i = (int)(playerRotation - Player::getInstance()->getRotation())/360;
//                
//                playerRotation = playerRotation + (360*(i+1));
//                
//            }
//
//            
//            float rotationSpeed = 200;
//            
//            float angleDiffence = -Player::getInstance()->getRotation()+ playerRotation;
//
//            if ( fabs(angleDiffence) < rotationSpeed*dt ) // finished rotation
//            {
//                Player::getInstance()->setRotation(playerRotation);
//            }
//            
//            else if(angleDiffence  > 0){
//                Player::getInstance()->setRotation(Player::getInstance()->getRotation()+ rotationSpeed*dt );
//                
//            }
//            else{
//                Player::getInstance()->setRotation(Player::getInstance()->getRotation()- rotationSpeed*dt );
//                
//            }
//        }
//    }
//    else{
//        allowMovement = false;
//    }
    
    
    
    float x = 2.76*(-bgJoystick->getPosition().x + joystick->getPosition().x)/bgJoystick->getPosition().distance(joystick->getPosition());
    float y = 2.76*(-bgJoystick->getPosition().y + joystick->getPosition().y)/bgJoystick->getPosition().distance(joystick->getPosition());
    if(allowMovement){
    Player::getInstance()->setPosition(Vec2(Player::getInstance()->getPosition().x + x ,Player::getInstance()->getPosition().y + y));
    }

    
    Player::getInstance()->setRotation3D(Vec3(Player::getInstance()->getRotation3D().x,Player::getInstance()->getRotation3D().y,modulus(Player::getInstance()->getRotation3D().z,360)));
    
    Point playerPosition = Player::getInstance()->getPosition();
    if(playerRotation -Player::getInstance()->getRotation3D().z > 200)
    {
        int i = (int)(playerRotation - Player::getInstance()->getRotation3D().z)/360;
        playerRotation = playerRotation - (360*(i+1));
        
        
    }
    if(playerRotation - Player::getInstance()->getRotation3D().z < -200)
    {
        int i = (int)(playerRotation - Player::getInstance()->getRotation3D().z)/360;
        
        playerRotation = playerRotation + (360*(i+1));
        
    }
    
    
    
    Player::getInstance()->setRotation3D(Vec3(Player::getInstance()->getRotation3D().x,0,Player::getInstance()->getRotation3D().z + (playerRotation- Player::getInstance()->getRotation3D().z)* dt*8));
    


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
