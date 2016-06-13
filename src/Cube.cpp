//
//  Cube.cpp
//  HereCollec
//
//  Created by Guillem Galimany on 6/6/16.
//
//

#include "Cube.h"
#include "ofLog.h"



Cube::Cube(int id_, int swingLeft_, int swingRight_)
{
    
    id = id_;
    swingLeft = swingLeft_;
    swingRight = swingRight_;
    
    intensityLevel = 0;
    
}


void Cube::update(){
    
    
//    std::cout <<id  ;
//    std::cout << " - " ;
//    std::cout << intensityLevel << std::endl ;


}

void Cube::setIntensityLevel(int intensityLevel_){

    //intensityLevel = intensityLevel_;
    
    //ofLog() << id << " - " << intensityLevel;
    
    if (prevIntensityLevel != intensityLevel_)
    {
        sendToLight();
    }
    
    prevIntensityLevel = intensityLevel_;
    

    
}

void Cube::sendToLight()
{
    
    Light::getInstance().lightTheCube(id, ofColor(1), intensityLevel);

}


