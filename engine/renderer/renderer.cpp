#include "mzpch.h"
#include "renderer.h"
//#include "renderer2D.h"

namespace Man520 {

    Scope<Renderer::SceneData> Renderer::sSceneData = createScope<Renderer::SceneData>();

    void Renderer::init() {
        RenderCommand::init();
        //Renderer2D::Init();
    }

    void Renderer::shutdown() {
        //Renderer2D::shutdown();
    }

    void Renderer::onWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::setViewport(0, 0, width, height);
    }

    //void Renderer::beginScene(OrthographicCamera& camera)
    //{
    //    sSceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
    //}

    void Renderer::endScene() {
    }

    void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
        shader->bind();
        shader->setMat4("u_ViewProjection", sSceneData->viewProjectionMatrix);
        shader->setMat4("u_Transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}

