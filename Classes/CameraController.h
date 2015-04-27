//
//  CameraController.h
//  SirVivAlot
//
//  Created by Bilal Mirza on 20/04/2015.
//
//

#ifndef __SirVivAlot__CameraController__
#define __SirVivAlot__CameraController__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class CameraController :public Layer
{
    
    
public:
    
    static Camera* getMainCamera();
    virtual bool init();
};



#endif /* defined(__SirVivAlot__CameraController__) */
