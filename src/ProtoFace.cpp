//
//  ProtoFace.cpp
//  animatingParticles
//
//  Created by Ira on 8/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <ProtoFace.h>

using namespace ijg;

ProtoFace::ProtoFace(ofVec3f* v0, ofVec3f* v1, ofVec3f* v2)
{
    p_vecs[0] = v0;
    p_vecs[1] = v1;
    p_vecs[2] = v2;
    
    calcNormal();
    calcCentroid();
}

ProtoFace::ProtoFace(const ofVec3f& v0, const ofVec3f& v1, const ofVec3f& v2):
v0(v0), v1(v1), v2(v2)
{
    
}

ProtoFace::ProtoFace(ofVec3f vs[3])
{
    vecs = vs;
    p_vecs[0] = &(vecs[0]);
    p_vecs[1] = &(vecs[1]);
    p_vecs[2] = &(vecs[2]);
    
    calcNormal();
    calcCentroid();
}

ProtoFace::ProtoFace(const ProtoEdge& e0, const ProtoEdge& e1, const ProtoEdge& e2):
e0(e0), e1(e1), e2(e2)
{
    
}

ProtoFace::ProtoFace(ProtoEdge* p_e0, ProtoEdge* p_e1, ProtoEdge* p_e2)
{
    p_edges[0] = p_e0;
    p_edges[1] = p_e1;
    p_edges[2] = p_e2;
    
    p_vecs[0] = p_edges[0]->getV0();
    p_vecs[1] = p_edges[1]->getV0();
    p_vecs[2] = p_edges[2]->getV0();
}



ofVec3f& ProtoFace::getNormal()
{
    return normal;
}

// Must be calcualted anytime vertex geometry is transformed.
// transformationa to the Graphics context don't require
// new normal calculation.
void ProtoFace::calcNormal()
{
    /*
     Face v0, v1, v2
     vector U = v1 - v0
     vector V = v2 - v0
     normal U X V
     Nx = UyVz - UzVy
     Ny = UzVx - UxVz
     Nz = UxVy - UyVx
     */
    
    ofVec3f U = *p_vecs[1]-*p_vecs[0];
    ofVec3f V = *p_vecs[2]-*p_vecs[0];
    
    normal.x = U.y*V.z - U.z*V.y;
    normal.y = U.z*V.x - U.x*V.z;
    normal.z = U.x*V.y - U.y*V.x;
    
    normal.normalize();
    
    //normal*=.04;
}

void ProtoFace::calcCentroid()
{
    centroid = ofVec3f((p_vecs[0]->x+p_vecs[1]->x+p_vecs[2]->x)/3,
                       (p_vecs[0]->y+p_vecs[1]->y+p_vecs[2]->y)/3,
                       (p_vecs[0]->z+p_vecs[1]->z+p_vecs[2]->z)/3
                       );
   // std::cout<< "centroid = " << centroid << std::endl;
}

void ProtoFace::display()
{
    
    ofBeginShape();

    //glNormal3fv(&n[i][0]);
    ofVertex(p_vecs[0]->x, p_vecs[0]->y, p_vecs[0]->z);
    ofVertex(p_vecs[1]->x, p_vecs[1]->y, p_vecs[1]->z);
    ofVertex(p_vecs[2]->x, p_vecs[2]->y, p_vecs[2]->z);
    ofEndShape(true);
}

void ProtoFace::displayNormal(float len)
{
    
    ofPushStyle();
    
    ofNoFill();
    ofSetColor(255, 255, 255);
    //ofBeginShape();
    glBegin(GL_LINES);
    glVertex3f(centroid.x, centroid.y, centroid.z);
    glVertex3f(centroid.x+normal.x*len, centroid.y+normal.y*len, centroid.z+normal.z*len);
    //ofEndShape();
    glEnd();
    
    ofPopStyle();
}







