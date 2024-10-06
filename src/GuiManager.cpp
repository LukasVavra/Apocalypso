#include <GuiManager.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

GuiManager::GuiManager()
: _window(nullptr), _renderer(nullptr)
{
}

bool GuiManager::init(SDL_Window *window, SDL_Renderer *renderer)
{
    _window = window;
    _renderer = renderer;
    if(_window == nullptr || _renderer == nullptr) return false;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Conrols
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::StyleColorsLight();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
    return true;
}

void GuiManager::handle_event(SDL_Event *event)
{
    ImGui_ImplSDL2_ProcessEvent(event);
}

void GuiManager::update()
{
    bool close_btn = true;
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Hello, Dear ImGui with SDL2", &close_btn);
    ImGui::Text("This is just a basic Hello World!");
    ImGui::End();
    ImGui::Render();
}

void GuiManager::render()
{
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), _renderer);
}

void GuiManager::clean()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

GuiManager::~GuiManager()
{
}
