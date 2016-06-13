//
//  par.h
//  Corasonsitu
//
//  Created by Helena Bantulà i Fonts on 27/11/15.
//
//

#ifndef __Corasonsitu__par__
#define __Corasonsitu__par__

#include <iostream>
#include "ofxArtnet.h"
#include "ofMain.h"

#endif

class Par {

public:
    

    // FEATURES
    
    ofColor color;
    ofColor colorI;            //color inicial, sempre el mateix
    int id;

    
    // FADES

    int stepFI = 200; //in milliseconds
    int stepFO = 200;
    bool isFadeIn = false;
    bool isFadeOut = false;
    float topFade = 0.3;
    int type=1;
    
    bool isFadeColor = false;
    ofColor myNewColor;


    // OTHERS
    
    int i;
    bool isRandom = false;
    int time;
    float timef;
    
    
    
    Par (ofColor,int);
    void fadeIn();
    void triggerFadeIn(int tipus, int step);
    void triggerFadeOut(int step);
    void fadeOut();
    void update();
    void randomMove();
    
    ofColor getColor(){return color;};
    
    void multiplyColor(int k){color = colorI*k;};
    void setColor(ofColor newColor){
        color = newColor;
        colorI = newColor;
    };
    
    void triggerFadeColor(ofColor newColor, float time);
    void fadeColor();
    float fadeTime;
    
    void draw();
    
    bool isSinusoidal = false;
    
    float myBrightness;
    ofColor cubeNewColor;
    float amplitude;
    float frequency;
    void sinusoidalMove();
    void triggerSinusoidalMove(float amplitude, float frequency);
    
    void triggerChangeCubeColor(ofColor newColor_,float amplitude_, float frequency_);

    void changeCubeColor();
    float cubeTime;
    float cubeCurrentTime;
    
    bool isChangeCubeColor = false;




    
};
