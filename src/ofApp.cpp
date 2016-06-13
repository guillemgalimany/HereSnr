#include "ofApp.h"
#include "ofxNetwork.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    

    ofHideCursor();
    
    Light::getInstance().initialize();      // Els pars es posen tots a tope
    //Light::getInstance().fadePars(1, 'O', '0', warmingTime, 3);
    
    TCP.setup(8081);
    
    
    Cube tempCube1(1,1,1);
    cubes.push_back(tempCube1);
//    Cube tempCube2(2,1,2);
//    cubes.push_back(tempCube2);
//    Cube tempCube3(3,2,3);
//    cubes.push_back(tempCube3);
//    Cube tempCube4(4,3,4);
//    cubes.push_back(tempCube4);
//    Cube tempCube5(5,4,1);
//    cubes.push_back(tempCube5);



}

//--------------------------------------------------------------
void ofApp::update(){

    // LIGHT
    Light::getInstance().getInfo();
    
    //ofColor myPrevColor = myTestColor;
    
    
    //--------------------------------------------------------------

    //cout << ofGetElapsedTimeMillis() - requestDataTimer << endl;

    
    if (ofGetElapsedTimeMillis() - requestDataTimer > 5000)
    {
        requestDataServer();
        
        requestDataTimer = ofGetElapsedTimeMillis();
    
    }
    
    
//
//    ofHttpResponse resp = ofLoadURL("http://here.alquimia.io/backend/api/measurements-last/?format=json");
//    cout << resp.data << endl;
//    
//    //ofFile newFile(ofToDataPath("temp.txt")); //file doesn't exist yet
//    
////    ofFile file(ofToDataPath("fitxertemporal.txt"));
////    file << resp.data;
////    file.close();
//
//    
//    string str = resp.data;
//    ofBuffer msg(str.c_str(), str.length());
//    ofBufferToFile("out.txt", msg);
//    
////    cout << resp.data << endl;
//
//    if (str != "[]")
//    {
//        result.open("out.txt");
//        cout << result[0]["installationId"].asString() << endl;
//        //cout << result.type() << endl;
//        
//        
//        
//        
//        for(int i = 0; i < (int)result.type(); i++)
//        {
//            string intallationIdStr = result[i]["installationId"].asString();
//            
//            string swingIdStr =result[i]["swingId"].asString();
//            
//            std::string::size_type sz;   // alias of size_t
//            
//            int intallationId = std::stoi (intallationIdStr);
//            
//            int swingId = std::stoi (intallationIdStr,&sz);
//
//            int tempoValue = result[i]["tempoValue"].asInt();
//            
//            serverData[ intallationId ][ swingId ] = tempoValue;
//        }
//
//    }
    
    //ss << "firstName          = " << result["firstName"].asString() << std::endl;

    
    
    
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

                
                std::cout <<str<< endl;

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
    switch(key)
    {
        case 'f':
            Light::getInstance().setParsColor(ofColor(255,0,0));
            break;
        case 'j':
            Light::getInstance().setParsColor(ofColor(0,255,0));

            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(key)
    {
        case 'f':
            break;
        case 'j':
            break;
    }
    
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
    
    ofHttpResponse resp = ofLoadURL("http://here.alquimia.io/backend/api/measurements-last/?format=json");
    cout << resp.data << endl;
    
    
    string str = resp.data;
    ofBuffer msg(str.c_str(), str.length());
    ofBufferToFile("out.txt", msg);
    
    
    if (str != "[]")
    {
        result.open("out.txt");
        
        int numMissatges = (int)result.type();
        
        for(int i = 0; i < numMissatges; i++)
        {
            string intallationIdStr = result[i]["installationId"].asString();
            
            string swingIdStr =result[i]["swingId"].asString();
            
            if (intallationIdStr != "" && swingIdStr != "")
            {
                
                std::string::size_type sz;   // alias of size_t
                
                int intallationId = std::stoi (intallationIdStr);
                
                int swingId = std::stoi (swingIdStr,&sz);
                
                int tempoValue = result[i]["tempoValue"].asInt();
                
                serverData[ intallationId - 1 ][ swingId - 1 ] = tempoValue;
                
            }
        }
        
    }
    

    
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



