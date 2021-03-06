#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
    
    Sprite3D *theIsland;
    void InitIsland();
    void InitLight();
    Size winSize;
    Point touchLocation;
    float playerRotation;
    
    Layer *hudLayer;
    Sprite *bgJoystick;
    Sprite *joystick;
    
    Camera *terrainCamera;
    
    DirectionLight *theLight;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void update(float dt);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);

    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);//move to another class
    Point locationToMove;
    bool allowMovement;
    
    float modulus(float a, float b);
    float calcAngle(Point p1, Point p2);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
