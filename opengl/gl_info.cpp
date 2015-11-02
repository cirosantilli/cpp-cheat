/*
glInfo.cpp
==========
get GL vendor, version, supported extensions and other states using glGet*
functions and store them glInfo struct variable

To get valid OpenGL infos, OpenGL rendering context (RC) must be opened
before calling glInfo::getInfo(). Otherwise it returns false.

 AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
CREATED: 2005-10-04
UPDATED: 2012-06-06

Copyright (c) 2005 Song Ho Ahn
*/

#include <GL/gl.h>

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// struct variable to store OpenGL info
struct glInfo
{
    std::string vendor;
    std::string renderer;
    std::string version;
    std::string glslVersion;
    std::vector <std::string> extensions;
    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;
    int depthBits;
    int stencilBits;
    int maxTextureSize;
    int maxLights;
    int maxAttribStacks;
    int maxModelViewStacks;
    int maxProjectionStacks;
    int maxClipPlanes;
    int maxTextureStacks;

    // ctor, init all members
    glInfo() : redBits(0), greenBits(0), blueBits(0), alphaBits(0), depthBits(0),
               stencilBits(0), maxTextureSize(0), maxLights(0), maxAttribStacks(0),
               maxModelViewStacks(0), maxClipPlanes(0), maxTextureStacks(0) {}

    bool getInfo(unsigned int param=0);         // extract info
    void printSelf();                           // print itself
    bool isExtensionSupported(const std::string& ext); // check if a extension is supported
};

// version 2.0 or greater
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C

/*
extract openGL info
This function must be called after GL rendering context opened.
*/
bool glInfo::getInfo(unsigned int param) {
    const char* str = 0;
    char* tok = 0;

    // get vendor string
    str = (const char*)glGetString(GL_VENDOR);
    if(str) this->vendor = str;                  // check NULL return value
    else return false;

    // get renderer string
    str = (const char*)glGetString(GL_RENDERER);
    if(str) this->renderer = str;                // check NULL return value
    else return false;

    // get version string
    str = (const char*)glGetString(GL_VERSION);
    if(str) this->version = str;                 // check NULL return value
    else return false;

    // get version string (v2.0+)
    str = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    if(str) this->glslVersion = str;            // check NULL return value
    else glslVersion = "";

    // get all extensions as a string
    str = (const char*)glGetString(GL_EXTENSIONS);

    // split extensions
    if (str) {
        tok = strtok((char*)str, " ");
        while (tok) {
            this->extensions.push_back(tok);    // put a extension into struct
            tok = strtok(0, " ");               // next token
        }
    }

    // sort extension by alphabetical order
    std::sort(this->extensions.begin(), this->extensions.end());

    // get number of color bits
    glGetIntegerv(GL_RED_BITS, &this->redBits);
    glGetIntegerv(GL_GREEN_BITS, &this->greenBits);
    glGetIntegerv(GL_BLUE_BITS, &this->blueBits);
    glGetIntegerv(GL_ALPHA_BITS, &this->alphaBits);

    // get depth bits
    glGetIntegerv(GL_DEPTH_BITS, &this->depthBits);

    // get stecil bits
    glGetIntegerv(GL_STENCIL_BITS, &this->stencilBits);

    // get max number of lights allowed
    glGetIntegerv(GL_MAX_LIGHTS, &this->maxLights);

    // get max texture resolution
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &this->maxTextureSize);

    // get max number of clipping planes
    glGetIntegerv(GL_MAX_CLIP_PLANES, &this->maxClipPlanes);

    // get max modelview and projection matrix stacks
    glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &this->maxModelViewStacks);
    glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &this->maxProjectionStacks);
    glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH, &this->maxAttribStacks);

    // get max texture stacks
    glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &this->maxTextureStacks);

    return true;
}

bool glInfo::isExtensionSupported(const std::string& ext) {
    std::vector<std::string>::const_iterator iter = this->extensions.begin();
    std::vector<std::string>::const_iterator endIter = this->extensions.end();
    while (iter != endIter) {
        if(ext == *iter)
            return true;
        else
            ++iter;
    }
    return false;
}

void glInfo::printSelf() {
    std::stringstream ss;
    ss << "Vendor: " << this->vendor << std::endl
    << "Version: " << this->version << std::endl
    << "GLSL Version: " << this->glslVersion << std::endl
    << "Renderer: " << this->renderer << std::endl
    << std::endl
    << "Color Bits(R,G,B,A): (" << this->redBits << ", " << this->greenBits
    << ", " << this->blueBits << ", " << this->alphaBits << ")\n" << "Depth Bits: " << this->depthBits << std::endl
    << "Stencil Bits: " << this->stencilBits << std::endl
    << std::endl
    << "Max Texture Size: " << this->maxTextureSize << "x" << this->maxTextureSize << std::endl
    << "Max Lights: " << this->maxLights << std::endl
    << "Max Clip Planes: " << this->maxClipPlanes << std::endl
    << "Max Modelview Matrix Stacks: " << this->maxModelViewStacks << std::endl
    << "Max Projection Matrix Stacks: " << this->maxProjectionStacks << std::endl
    << "Max Attribute Stacks: " << this->maxAttribStacks << std::endl
    << "Max Texture Stacks: " << this->maxTextureStacks << std::endl
    << std::endl
    << "Total Number of Extensions: " << this->extensions.size() << std::endl;
    for (unsigned int i = 0; i < this->extensions.size(); ++i)
        ss << this->extensions.at(i) << std::endl;
    std::cout << ss.str() << std::endl;
}

int main() {
    glInfo glInfo;
    glInfo.getInfo();
    glInfo.printSelf();
    return EXIT_SUCCESS;
}
