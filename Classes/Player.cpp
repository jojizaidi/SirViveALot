//
//  Player.cpp
//  SirVivAlot
//
//  Created by Bilal Mirza on 20/04/2015.
//
//

#include "Player.h"


static Sprite3D *player = nullptr;

Sprite3D *Player::getInstance()
{
    if(!player)
    {
        player = Sprite3D::create("demon1.c3b");
        player->setScale(4);
        player->setTexture("demon_boss.png");
        player->setTexture("demon_boss.jpg");
        player->setCameraMask((unsigned int)CameraFlag::USER1);
        player->setRotation3D(Vec3(90,0,0));

    }
    
    return player;
    
}