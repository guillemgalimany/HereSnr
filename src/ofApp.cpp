#include "ofApp.h"
#include "ofxNetwork.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    

    ofHideCursor();
    
    Light::getInstance().initialize();
    
    TCP.setup(8081);
    
    Cube tempCube1(1,1,1);
    cubes.push_back(tempCube1);

}

//--------------------------------------------------------------
void ofApp::update(){

    // LIGHT
    Light::getInstance().getInfo();
    
    //--------------------------------------------------------------

    // TCP
    for(int i = 0; i < TCP.getLastID(); i++) // getLastID is UID of all clients
    {
     
        //std::cout <<TCP.getLastID();
        
        if( TCP.isClientConnected(i) ) { // check and see if it's still around
            // maybe the client is sending something
            std::string str = TCP.receive(i);
            
            //std::cout <<"received"<< endl;


            if (str != "")
            {
                
                //std::cout <<"RECEIVED"<< endl;

                
                //std::cout <<str<< endl;

                std::vector<int> vect;
                
                std::stringstream ss(str);
                
                int j;
                
                while (ss >> j)
                {
                    vect.push_back(j);
                    
                    if (ss.peek() == ',')
                        ss.ignore();
                }
                
                int id = vect.at(1);
                int tempo = vect.at(2);
                
                //std::cout <<tempo<< endl;
                
                swingsTempo[id-1][0] = tempo;


                setIntensityCube();

            }

        }
    }
    

    //myPrevColor.lerp(myTestColor,ofGetElapsedTimef());
    
    //Light::getInstance().setParsColor(myPrevColor);

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

    
}

//--------------------------------------------------------------
void ofApp::setIntensityCube()
{
    
    for (int i = 0; i < cubes.size(); i++)
    {
        
        int swing1 = cubes[i].swingLeft;
        
        int swing2 = cubes[i].swingRight;
        
        int tempIntensity = swingsTempo[swing1-1][0] + swingsTempo[swing2-1][0] ;
        
        cubes[i].setIntensityLevel(tempIntensity);
        
    }
}

//--------------------------------------------------------------
void ofApp::requestDataServer()
{
   

    
}


//--------------------------------------------------------------
void ofApp::draw()
{
    ofDrawBitmapString(swingsTempo[0][0],20, 20);
    
    ofDrawBitmapString(swingsTempo[1][0],50, 20);

    ofDrawBitmapString(swingsTempo[2][0],80, 20);

    ofDrawBitmapString(swingsTempo[3][0],110, 20);

    
}

void ofApp::exit()
{
    
    TCP.close();

}



