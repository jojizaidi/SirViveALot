//
//  CameraController.cpp
//  SirVivAlot
//
//  Created by Bilal Mirza on 20/04/2015.
//
//

#include "CameraController.h"

#include "Player.h"

static Camera* mainCamera = nullptr;

Camera* CameraController::getMainCamera()
{
    if(!mainCamera)
    {
        auto s = Director::getInstance()->getWinSize();
        mainCamera = Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 2000);
        mainCamera->setPosition3D(Vec3(0, 0, 200));
        mainCamera->lookAt(Vec3(0, 200, 0), Vec3(0, 1, 0));
        mainCamera->setCameraFlag(CameraFlag::USER8);//USER8 is the main camera
        mainCamera->setPositionX(mainCamera->getPositionX() + (Player::getInstance()->getPositionX()- mainCamera->getPositionX()));
        mainCamera->setPositionY(mainCamera->getPositionY() + (Player::getInstance()->getPositionY() - 200- mainCamera->getPositionY()));
    }
    return mainCamera;
}


bool CameraController::init()
{
 
    if(!Layer::init())
    {
        return false;
    }
    
    
    return true;
}