#include "imguiLayer.h"
#include "mzpch.h"

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include "core/application.h"

namespace Man520 {

    ImguiLayer::ImguiLayer() : Layer("ImguiLayer") {
    
    }

    void ImguiLayer::onAttach() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        //TODO:
        /*ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;*/
        ImGui::StyleColorsDark();
        auto& window = Application::get().getWindow();
        ImGui_ImplSDL2_InitForOpenGL(window.getSDLWindow(), &(window.getGraphicsContext()));
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImguiLayer::onDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    bool ImguiLayer::onEvent(SDL_Event& event) {
        if (mBlockEvents) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            return true;
        }
        return false;
    }

    void ImguiLayer::begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(Application::get().getWindow().getSDLWindow());
        ImGui::NewFrame();
	//	ImGuizmo::BeginFrame();
    }

    void ImguiLayer::end() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}
