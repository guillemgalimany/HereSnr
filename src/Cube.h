//
//  Cube.h
//  HereCollec
//
//  Created by Guillem Galimany on 6/6/16.
//
//

#ifndef Cube_h
#define Cube_h

#include <stdio.h>
#include <iostream>

#include "Light.h"


#endif /* Cube_h */


class Cube {
    
public:
    
    int id;
    int swingLeft;
    int swingRight;
    
    int intensityLevel;
    
    void setIntensityLevel(int);

    Cube (int, int, int);
    
    void update();
    
    void sendToLight();
    
    int prevIntensityLevel;

    
};
