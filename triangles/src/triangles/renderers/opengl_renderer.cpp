//
// Created by jakub on 31.10.2016.
//

#include "triangles/renderers/opengl_renderer.h"

#include <math/math_ifx.h>
#include <model/model.h>
#include <factory/texture_factory.h>
#include <factory/program_factory.h>
#include <factory/render_object_factory.h>
#include <game_loop/game_loop.h>
#include <object/render_object.h>
#include <shaders/data/shader_data.h>
#include <rendering/renderer.h>

OpenGLRenderer::OpenGLRenderer() {
    InitScene();
}

OpenGLRenderer::~OpenGLRenderer() {
}

void OpenGLRenderer::Start(){
    game_loop->Start();
}

void OpenGLRenderer::InitScene(){
    game_loop.reset(new ifx::GameLoop(std::move(ifx::RenderObjectFactory().CreateRenderer())));

    auto mesh = CreateTriangleMesh();
    auto model = CreateTriangleModel(std::move(mesh));
    std::shared_ptr<RenderObject> render_object = CreateTriangleRenderObject(model);

    game_loop->renderer()->scene()->AddRenderObject(render_object);
    game_loop->renderer()->scene()->camera()->rotate(glm::vec3(-90,-22.3,0));
}


std::unique_ptr<Mesh> OpenGLRenderer::CreateTriangleMesh(){
    // Position, Normal, TexCoord
    std::vector <Vertex> vertices = {
            // Front
            Vertex{glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(1.0f, 0.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(0.0f, 0.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)}
    };

    std::vector <GLuint> indices = {0, 1, 2};
    ifx::TextureFactory textureLoader;
    Texture textureDiffuse = textureLoader.LoadContainerDiffuse();
    Texture textureSpecular = textureLoader.LoadContainerSpecular();
    std::vector <Texture> textures = {textureDiffuse, textureSpecular};

    std::unique_ptr<Mesh> mesh(new Mesh(vertices, indices,
                                        GL_TRIANGLES));

    Material material;
    material.shininess = 32.0f;
    mesh->setMaterial(material);

    return mesh;
}

std::shared_ptr<Model> OpenGLRenderer::CreateTriangleModel(std::unique_ptr<Mesh> mesh){
    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh));

    return Model::MakeModel("Triangle", std::move(meshes));
}

std::shared_ptr<RenderObject> OpenGLRenderer::CreateTriangleRenderObject(std::shared_ptr<Model> model){
    ifx::ProgramFactory program_factory;

    std::shared_ptr<Program> program = program_factory.LoadMainProgram();

    auto render_object = std::shared_ptr<RenderObject>(new RenderObject(ObjectID(0), model));
    render_object->addProgram(program);

    return render_object;
}