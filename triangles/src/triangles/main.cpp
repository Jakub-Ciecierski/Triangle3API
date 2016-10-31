#include <triangles/renderers/opengl_renderer.h>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <cstring>

const char* OPENGL_ARG = "gl";
const char* DIRECTX_ARG = "dx";

void PrintUsage();

void PrintUsage(){
    std::cout << "Usage:" << std::endl;
    std::cout << "OpenGL:  gl" << std::endl;
    std::cout << "DirectX: dx" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc < 2){
        PrintUsage();
        return EXIT_FAILURE;
    }

    if(std::strcmp(argv[1], OPENGL_ARG) == 0){
        OpenGLRenderer renderer;
        renderer.Start();
    }else if(std::strcmp(argv[1], DIRECTX_ARG) == 0){
        std::cout << "Not implemented" << std::endl;
    }else{
        PrintUsage();
    }

}

