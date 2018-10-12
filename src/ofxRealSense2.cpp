#include "ofxRealSense2.h"
#include "ofxRealSense2Utils.h"


ofxRealSense2::ofxRealSense2(){
}

ofxRealSense2::~ofxRealSense2(){
}

bool ofxRealSense2::setup(){
    pipe.start();
    colorImage.allocate(COLOR_WIDTH, COLOR_HEIGHT, OF_IMAGE_COLOR);
    depthImage.allocate(DEPTH_WIDTH, DEPTH_HEIGHT, OF_IMAGE_COLOR);
    
    return false; /////
}

void ofxRealSense2::update(){
    rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
    rs2::frame depth = data.get_depth_frame();
	rs2::frame coloredDepth = color_map.colorize(depth);  // Find and colorize the depth data
    rs2::frame color = data.get_color_frame();            // Find the color data
    
    colorImage.setFromPixels((unsigned char *)color.get_data(), COLOR_WIDTH, COLOR_HEIGHT, OF_IMAGE_COLOR);
    depthImage.setFromPixels((unsigned char *)coloedDepth.get_data(), DEPTH_WIDTH, DEPTH_HEIGHT, OF_IMAGE_COLOR);
    
    ///// https://github.com/IntelRealSense/librealsense/tree/master/examples/pointcloud
    points = pointcloud.calculate(depth);
    pointcloud.map_to(color);
    if (points.size()) {
        mesh.clear();
        mesh.enableColors();
        mesh.enableNormals();
        const rs2::vertex* vertices = points.get_vertices();
        const rs2::texture_coordinate* texture_coordinates = points.get_texture_coordinates();
        
        for (int32_t index = 0; index < points.size(); index++) {
            if (vertices[index].z) {
                const rs2::vertex vertex = vertices[index];

                mesh.addVertex(ofVec3f(vertex.x, vertex.y, vertex.z));
                mesh.addNormal(ofVec3f(0.f, 0.f, -1.f));

                const rs2::texture_coordinate texture_coordinate = texture_coordinates[index];
                const uint32_t x = static_cast<uint32_t>(texture_coordinate.u * static_cast<float>(COLOR_WIDTH));
                const uint32_t y = static_cast<uint32_t>(texture_coordinate.v * static_cast<float>(COLOR_HEIGHT));

                if ((0 <= x) && (x < COLOR_WIDTH) && (0 <= y) && (y < COLOR_HEIGHT)) {
                    ofColor color = colorImage.getColor(x, y);
                    mesh.addColor(color);
                }
                else {
                    mesh.addColor(ofColor::black);
                }
            }
        }
    }
}


//----------------------------------------------------------
void ofxRealSense2::draw(float _x, float _y, float _w, float _h) const{
    colorImage.draw(_x, _y, _w, _h);
}

//----------------------------------------------------------
void ofxRealSense2::draw(float _x, float _y) const{
    draw(_x, _y, (float)COLOR_WIDTH, (float)COLOR_HEIGHT);
}

//----------------------------------------------------------
void ofxRealSense2::draw(const ofPoint & point) const{
    draw(point.x, point.y);
}

//----------------------------------------------------------
void ofxRealSense2::draw(const ofRectangle & rect) const{
    draw(rect.x, rect.y, rect.width, rect.height);
}

//----------------------------------------------------------
void ofxRealSense2::drawDepth(float _x, float _y, float _w, float _h) const{
    depthImage.draw(_x, _y, _w, _h);
}

//---------------------------------------------------------------------------
void ofxRealSense2::drawDepth(float _x, float _y) const{
    drawDepth(_x, _y, (float)DEPTH_WIDTH, (float)DEPTH_HEIGHT);
}

//----------------------------------------------------------
void ofxRealSense2::drawDepth(const ofPoint & point) const{
    drawDepth(point.x, point.y);
}

//----------------------------------------------------------
void ofxRealSense2::drawDepth(const ofRectangle & rect) const{
    drawDepth(rect.x, rect.y, rect.width, rect.height);
}


ofPixels & ofxRealSense2::getPixels(){
    return colorImage.getPixels();
}

ofPixels & ofxRealSense2::getDepthPixels(){
    return depthImage.getPixels();
}
