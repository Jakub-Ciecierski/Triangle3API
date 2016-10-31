//
// Created by jakub on 31.10.2016.
//

#ifndef PROJECT_OPENGL_RENDERER_H
#define PROJECT_OPENGL_RENDERER_H

#include <memory>

namespace ifx{
    class GameLoop;
}
class Mesh;
class Model;
class RenderObject;

class OpenGLRenderer {
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    void Start();
private:
    void InitScene();

    std::unique_ptr<Mesh> CreateTriangleMesh();
    std::shared_ptr<Model> CreateTriangleModel(std::unique_ptr<Mesh> mesh);
    std::shared_ptr<RenderObject> CreateTriangleRenderObject(std::shared_ptr<Model> model);

    std::unique_ptr<ifx::GameLoop> game_loop;

};


#endif //PROJECT_OPENGL_RENDERER_H
