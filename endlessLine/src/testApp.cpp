#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(0,0,0);
    ofSetFrameRate(30);
    total.addVertex(0,0);
    angle = 0;
    angleSmooth = 0;
}

//--------------------------------------------------------------
void testApp::update(){

    
    
    if (angleDiffs.size() > 0){
        
        for (int i = 0; i < total.getVertices().size(); i++){
            total.getVertices()[i].z -= 0.5;
        }
        
        angle += angleDiffs[0];
        float dist = distances[0];
        ofPoint lastVertex = total.getVertices()[ total.getVertices().size() - 1 ];
        ofPoint newVeretx = lastVertex + ofPoint( cos(angle) * dist, sin(angle) * dist);
        angleDiffs.erase(angleDiffs.begin());
        total.addVertex(newVeretx.x, newVeretx.y);
        distances.erase(distances.begin());
        
        
        
    }
    
    
    
    catchPoint = 0.9f * catchPoint + 0.1f * total.getVertices()[total.getVertices().size()-1];
}

//--------------------------------------------------------------
void testApp::draw(){

    
    ofEnableAlphaBlending();
    
    //line.draw();
    if (ofGetMousePressed() == true){
        ofSetColor(255,255,255,100);
        line.draw();
    }
    
    if (total.getVertices().size() > 150){
        total.getVertices().erase(total.getVertices().begin());
    }
    
    if (total.getVertices().size() > 0){
        
    
        
    ofPushMatrix();
    ofTranslate(-catchPoint.x + ofGetWidth()/2, -catchPoint.y + ofGetHeight()/2);
    
    
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < total.getVertices().size(); i++){
        float pct = ofMap(i, 0, total.getVertices().size()-1, 0,1);
        ofSetColor(255,255,255,255*pct);
        glVertex3f(total.getVertices()[i].x, total.getVertices()[i].y, total.getVertices()[i].z);
    }
    glEnd();
    ofEndShape();
    
    //total.draw();
    ofPopMatrix();
    
    
    }
    
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

    line.addVertex(ofPoint(x,y));
       
    

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    line.clear();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    //line = line.getResampledByCount(100);
    
    
    oldLines.push_back(line);
    
    
    if (oldLines.size() > 8) oldLines.erase(oldLines.begin());
    angleLine.convertFrom(line);

    
    
    for (int i = 0; i < angleLine.angleDiffs.size(); i++){
        angleDiffs.push_back(angleLine.angleDiffs[i]);
        distances.push_back(angleLine.distances[i]);
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}