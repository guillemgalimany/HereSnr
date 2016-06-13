//  light.cpp
//  Corasonsitu
//
//  Created by Helena Bantulà i Fonts on 17/11/15.
//
//

#include "Light.h"



void Light::initialize(){
    
//    while( isNodeConnected == false )
//    {
//    
//        try {

            #if TARGET_RASPBERRY_PI
                artnet.setup("192.168.1.138"); //IP de rPi
            #else
                artnet.setup("192.168.1.125"); //IP ordinador
            #endif 
            
//            isNodeConnected = true;
//
//        }
//        catch (...){
//            
//            isNodeConnected = false;
//            
//            ofLog() << "trying to connect";
//
//
//        }
//        
//        usleep(500);
//    }
//    
    //CUBE 1
    ofColor color(0,100,0);
    colors.push_back(color);
    
    //CUBE 2
    color.set(0, 0, 255);
    colors.push_back(color);
    
    //CUBE 3
    color.set(0, 255, 0);
    colors.push_back(color);
    
    //CUBE 4
    color.set(0, 100, 100);
    colors.push_back(color);
    
    //CUBE 5
    color.set(100, 0, 50);
    colors.push_back(color);

    
    for (int i = 0; i < maxPar; i++){
        Par temPar(colors[0],i);
        pars.push_back(temPar);
    }
    
    parXcube = maxPar / maxCubes;
    
    vector<vector<int>> tempMatrix(maxCubes, vector<int>(parXcube));
    parCubeAssign = tempMatrix;
    
    for (int i = 0; i < maxCubes; i++){
        for (int j = 0; j < (parXcube); j++)
            parCubeAssign[i][j] = i*(parXcube) +j;
    }

    //vector<unsigned char> tempPackDMX(maxPar*3);
    vector<unsigned char> tempPackDMX(512);
    packDMX = tempPackDMX;
    
    
    
    
    for (int id = 0; id < maxCubes+1; id++)
    {
        vector<int> parsToUseIndex = parCubeAssign [id-1];

        for (int i = 0 ; i < parsToUseIndex.size();i++)
        {
            pars[parsToUseIndex[i]].setColor(colors[id-1]);
        }
    }
    
    
    this->getInfo();
}



void Light::getInfo(){
    
    int j = 0;
    for (int i = 0; i < maxPar; i++){
        
        pars[i].update();
        
        packDMX[j] = pars[i].getColor().r;
        packDMX[j+1] = pars[i].getColor().g;
        packDMX[j+2] = pars[i].getColor().b;
        j = j+3;
    }
    
    this->sendInfo();
}


void Light::sendInfo(){
    
    //artnet.sendDmx("192.168.1.151",&packDMX[0], packDMX.size());
    
        try {
            
            artnet.sendDmx("192.168.1.151",&packDMX[0], packDMX.size());

        }
        catch (...){

            #if TARGET_RASPBERRY_PI
                        artnet.setup("192.168.1.138"); //IP de rPi
            #else
                        artnet.setup("192.168.1.125"); //IP ordinador
            #endif
            
            ofLog() << "trying to connect";


        }
}


void Light::fadePars(float topFade, char fadeType, int FItype, int fadeTime, int howMany){
    

    if (howMany == 2){
        
        for (int i = 0; i < maxPar; i++){
            
            pars[i].topFade = topFade;
            
            if (fadeType == 'I'){
                pars[i].triggerFadeIn(FItype, fadeTime);
            }
            else if (fadeType == 'O') {
                pars[i].triggerFadeOut(fadeTime);
            }
        }
    
    }
    
    else if (howMany == 1){
        
        
        for (int i = 0; i < sizeof(idxButtonPars); i++){
        
            int idx = idxButtonPars[i];
        
            pars[idx].topFade = topFade;
        
            if (fadeType == 'I'){
                    pars[idx].triggerFadeIn(FItype, fadeTime);
                }
            else if (fadeType == 'O') {
                    pars[idx].triggerFadeOut(fadeTime);
                }
                
            }
    
    }
    
    else if (howMany == 3){
        
        // CONSTRUCCIO VECTORS
        //vector<int> idxNoButtonPars(maxPar - sizeof(idxButtonPars));
        vector<int> idxNoButtonPars(maxPar - 2);  // non-user indexs
        
        int j = 0;
        for (int i = 0; i < maxPar; i++){
            if ((i != idxButtonPars[0]) && (i != idxButtonPars[1])) {
                idxNoButtonPars[j] = i;
                j++;
            }
        }
        
        for (int i = 0; i < idxNoButtonPars.size(); i++){
            
            int idx = idxNoButtonPars[i];
            
            pars[idx].topFade = topFade;
            
            if (fadeType == 'I'){
                pars[idx].triggerFadeIn(FItype, fadeTime);
            }
            else if (fadeType == 'O') {
                pars[idx].triggerFadeOut(fadeTime);
            }
            
        }
    }

}



void Light::changeColor(){
    
    
    float randIdx = ofRandomf();
    int idx;
    
    if (randIdx > 0)
    {
        idx = 1;
        currentColor = "blue";
    
    } else
    {
        idx = 0;
        currentColor = "red";
    }
    
    this->setParsColor(colors[idx]);
    

}


void Light::setParsColor(ofColor color){
    
    for (int i = 0; i < maxPar; i++){
        pars[i].setColor(color);
    }
    
}



void Light::setParState(float topColor){
    
    for (int i = 0; i < maxPar; i++){
        pars[i].setColor(topColor);
        
    }
    
}

string Light::getCurrentColor()
{
    return currentColor;
}



void Light::randomPlay(bool state)
{
    for (int i=0; i<maxPar; i++)
    {
        pars[i].isRandom = state;
    }
}


//funció que donat donat el id d'un par canvia el seu color actual per un color donat, en un temps donat
void Light::fade(int parId, ofColor newColor, float time)
{
    //assumim que el id dels pars sempre es el mateix que l'index en el vector de pars
    for (int i=0; i<maxPar; i++)
    {
        pars[i].triggerFadeColor(newColor, 1);
    }
    
}

void Light::lightTheCube(int id, ofColor targetColor, float amplitude)
{
    
    vector<int> parsToUseIndex = parCubeAssign [id-1];
    
    for (int i = 0 ; i < parsToUseIndex.size();i++)
    {
//        ofColor tempColor = ofColor(0,255,0);
//        //
//        tempColor.lerp(ofColor(0,0,255), lerpFactor);
//        
//        pars[parsToUseIndex[i]].triggerFadeColor(tempColor, 0.5);
            
//        pars[parsToUseIndex[i]].setColor(ofColor(0,0,255*(amplitude/6)));
//        
//        pars[parsToUseIndex[i]].triggerSinusoidalMove(50, 1);
        
        pars[parsToUseIndex[i]].triggerChangeCubeColor(ofColor(0,0,55+200*(amplitude/6)),30, 0.5);
    
        
    }
    
}


void Light::update()
{
    
    
}



