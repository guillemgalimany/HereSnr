//
//  Light.h
//  Corasonsitu
//
//  Created by Helena Bantulà i Fonts on 17/11/15.
//
//

#ifndef __Corasonsitu__light__
#define __Corasonsitu__light__

#include <iostream>
#include "ofxArtnet.h"
#include "Par.h"



class Light{
    
public:
    
    static Light &getInstance()
    {
        static Light instance;
        return instance;
        
    }
    
    
    // ARTNET & DMX
    ofxArtnet artnet;
    vector<unsigned char> packDMX;
    
    
    // PARS & COLORS
    vector<ofColor> colors;
    vector<Par> pars;
    int idxButtonPars[2];
    
    string currentColor;
    
    
    // PARS AND CUBES
    int maxPar = 10;
    int maxCubes = 5;
    int parXcube;
    vector<vector<int>> parCubeAssign;
  
    
    void initialize();
    void changeColor();
    
    void getInfo();
    void sendInfo();
    
    void fadePars(float topFade, char fadeType, int FItype, int fadeTime, int howMany); //tots els pars
    void fadeButtonPars(float topFade, char fadeType, int FItype, int fadeTime); //uns quants pars
    void switchColor(ofColor color);
    
    
    void setParsColor(ofColor color);
    void setParState(float topColor);
    
    
    string getCurrentColor();
    
    void randomPlay(bool state);
    
    void fade(int parId, ofColor color, float time);
    
    void update();
    
    void lightTheCube(int id, ofColor targetColor, float amplitude);
    
    
    long map(long x, long in_min, long in_max, long out_min, long out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
    

    
    bool isNodeConnected = false;




    
};

#endif /* defined(__Corasonsitu__light__) */