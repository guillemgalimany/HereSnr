//
//  par.cpp
//  Corasonsitu
//
//  Created by Helena Bantulà i Fonts on 27/11/15.
//
//

#include "Par.h"

Par::Par(ofColor colorC, int idC){
    
    color = colorC;
    colorI = colorC;
    id = idC;
}


void Par::update(){
    
    if (isFadeIn)
        fadeIn();
    
    if (isFadeOut)
        fadeOut();
    
    if (isRandom)
        randomMove();
    
    if (isFadeColor)
        fadeColor();
    
    if (isSinusoidal)
        sinusoidalMove();
    
    if (isChangeCubeColor)
        changeCubeColor();
    
    
    draw();
    
}



void Par::triggerFadeIn(int tipus, int step){ //trigger: ep, estic fent un fadein
    type = tipus;         //1: fadeIn+fadeOut,   2: fadeIn
    isFadeIn = true;
    stepFI = step;
    time = ofGetElapsedTimeMillis();
}


void Par::fadeIn(){
    
    color[0] = (ofGetElapsedTimeMillis()-time)*((float)colorI[0]*topFade/(float)stepFI);
    color[1] = (ofGetElapsedTimeMillis()-time)*((float)colorI[1]*topFade/(float)stepFI);
    color[2] = (ofGetElapsedTimeMillis()-time)*((float)colorI[2]*topFade/(float)stepFI);
    
    if ((ofGetElapsedTimeMillis()-time)>stepFI){

        color = colorI*topFade;
        isFadeIn=false;
        
        if (type == 1){
            stepFO = stepFI;
            triggerFadeOut(stepFO);
        }
    
    }
}


void Par::triggerFadeOut(int step){ //trigger: ep, estic fent un fadeOut
    if (color[0]!=0 || color[1]!=0 || color[2]!=0){
        isFadeOut = true;
        time = ofGetElapsedTimeMillis();
        stepFO = step;
    }
}


void Par::fadeOut(){
    color[0] = colorI[0]*topFade-(ofGetElapsedTimeMillis()-time)*((float)colorI[0]*topFade/(float)stepFO);
    color[1] = colorI[1]*topFade-(ofGetElapsedTimeMillis()-time)*((float)colorI[1]*topFade/(float)stepFO);
    color[2] = colorI[2]*topFade-(ofGetElapsedTimeMillis()-time)*((float)colorI[2]*topFade/(float)stepFO);
    

    if ((ofGetElapsedTimeMillis()-time)>stepFO) {         //sha esgotat el temps
        isFadeOut=false;
        color=0;
    }

}


void Par::randomMove(){
 
    topFade = ofNoise(ofGetElapsedTimef()/1.5+(300*id));             //300*id per a crear offset entre els pars
    topFade = ofMap(topFade, 0.2, 0.8, 0.3, 1, true);       //mapping dels valors del soroll a 0 i 1
    color = colorI*topFade;

}


void Par::triggerFadeColor(ofColor newColor, float time)
{
//    myNewColor = newColor;
//    timef = ofGetElapsedTimeMillis();
//    fadeTime = time;
//    isFadeColor = true;
    
    //setColor(myNewColor);

}


void Par::fadeColor()
{
    float currentTime = ofGetElapsedTimeMillis();
    
    float timeInSeconds = ((float)ofGetElapsedTimeMillis() - (float)timef)/(10000);
    
    color.lerp(myNewColor, timeInSeconds * fadeTime);
        
    if (timeInSeconds > fadeTime)
    {
        isFadeColor=false;
        
        myBrightness = color.getBrightness();
        
        isSinusoidal = true;
    }
}

void Par::triggerSinusoidalMove(float amplitude_, float frequency_) //modula el color actual reduint-ne la intensitat i tornant-la a augmentar de forma sinusoidal
{
    
    amplitude = amplitude_;
    frequency = frequency_;
    
    myBrightness = color.getBrightness();
    
    isSinusoidal = true;
    
    
}

void Par::sinusoidalMove() //modula el color actual reduint-ne la intensitat i tornant-la a augmentar de forma sinusoidal
{
    
    color.setBrightness(myBrightness + (sin ((float)ofGetElapsedTimeMillis()*0.001)) * amplitude );
    
    //color.setBrightness(200+ sin(ofGetElapsedTimeMillis()*0.001) * 50);
    
}

void Par::triggerChangeCubeColor(ofColor newColor_,float amplitude_, float frequency_)
{
    
    //actualitzo parametres oscilacio
    amplitude = amplitude_;
    frequency = frequency_;
    
    cubeNewColor = newColor_;
    
    //deixo de fer sinusoides
    isSinusoidal = false;
    
    //assigno el color al que em vull fadejar
    myNewColor = cubeNewColor;
    
    //guardo el moment en el que començo a canviar de color
    timef = ofGetElapsedTimeMillis();
    
    //temps que trigare a fadejar
    fadeTime = 0.5;
    
    //entro al loop de fer fade
    isFadeColor = true;
    
    //entro al loop de comprovar quan s'acaba el fade per començar a sinusoidar
    //isChangeCubeColor = true;
    
    //triggerSinusoidalMove(amplitude,frequency);
    

}

void Par::changeCubeColor()
{

    ofLog() << "timef" << " - " << timef;

    
    if (ofGetElapsedTimeMillis() - timef > fadeTime * 1000)
    {
        myBrightness = color.getBrightness();
        
        isSinusoidal = true;
        
        isChangeCubeColor = false;
    }
    

}

void Par::draw()
{



}