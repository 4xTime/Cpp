#pragma once
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "misc/cpp/imgui_stdlib.h"
#include <d3d9.h>
#include <tchar.h>
#include "fileMenager.hpp"

static LPDIRECT3D9              g_pD3D = nullptr;
static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = nullptr; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

class modMenager : public fileMenager {
private:
    WNDCLASSEXW wc;
    HWND hwnd;
    ImGuiIO io;

    ImVec4 menuColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    MSG msg;

    std::string ck2ModFolder;
    std::vector<int> posVec;
    std::string modPackNameString;

    std::vector<int>modPosForModPack;
    std::vector<int>modPackPos;

    bool showModPackMenu = false;
    bool showModsMenu = false;
    bool selectModPackButtonClicked = false;
    bool showMenuForNameModPack = false;
    bool showModPacks = true;
public:
    modMenager(std::string ck2ModFolder) {
        this->ck2ModFolder = ck2ModFolder;
        wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ck2ModMenager", nullptr };
        ::RegisterClassExW(&wc);
        hwnd = ::CreateWindowW(wc.lpszClassName, L"ck2ModMenager", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

        if (!CreateDeviceD3D(hwnd))
        {
            CleanupDeviceD3D();
            ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
            exit(1);
        }

        ::ShowWindow(hwnd, SW_SHOWDEFAULT);
        ::UpdateWindow(hwnd);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX9_Init(g_pd3dDevice);

        file = serachForMod(ck2ModFolder);
        modState = (bool*)malloc(file.numberOfMods * sizeof(bool));
        modStateForModpack = (bool*)malloc(file.numberOfMods * sizeof(bool));
        modPackState = (bool*)malloc(100 * sizeof(bool));

        if (modState == NULL) {
            std::cout << "MODS IS NULL" << std::endl;
            exit(1);
        }
        if (modPackState == NULL) {
            std::cout << "MODPACK IS NULL" << std::endl;
            exit(1);
        }
        if (modPackState == NULL) {
            std::cout << "MOD STATE FOR MODPACK IS NULL" << std::endl;
            exit(1);
        }
        if (!checkIfDirExistOrCreate()) {
            std::cout << "Cannot create ck2m mod folder" << std::endl;
            exit(1);
        }

        if (!checkIfModDataFolderExistOrCreate()) {
            std::cout << "Cannot create config.ini" << std::endl;
            exit(1);
        }


        for (int i = 0; i < file.numberOfMods; i++) {
            modStateForModpack[i] = false;
            int pos = checkIfModIsInFile(ck2mConfigFile, file.mods[i].string(), LABLE::mod);

            if (pos != -1) {
                appedNewModInFile(ck2mConfigFile, file.mods[i].string(), LABLE::mod,pos);
            }
            //GET FILE LINE AND CHECK MOD STATE
            if (pos == -1) {
                int modPos = getModPosInFile(ck2mConfigFile, file.mods[i].string());
                if (modPos != -1) {
                    posVec.push_back(modPos);
                    char modStateChar = readStateOfMod(ck2mConfigFile, modPos);
                    if (modStateChar == '0') {
                        modState[i] = false;
                    }
                    if (modStateChar == '1') {
                        modState[i] = true;
                    }
                }
                else if(modPos == -1) { std::cout << "modPos unknown"; exit(1); }
            }
        }
        FileConfigPos modInfo = getModPackPosNameStatus(ck2mConfigFile);
        for (int i = 0; i < modInfo.modPos.size(); i++) {
            if (modInfo.status[i] == '1') {
                modPackState[i] = true;
            }
            else if (modInfo.status[i] == '0') {
                modPackState[i] = false;
            }
        }
        

    }

    void start() {

        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                exit(1);
        }
        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            g_d3dpp.BackBufferWidth = g_ResizeWidth;
            g_d3dpp.BackBufferHeight = g_ResizeHeight;
            g_ResizeWidth = g_ResizeHeight = 0;
            ResetDevice();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("ck2 mod menager");

        ImGui::Checkbox("show modPack menu", &showModPackMenu);
        ImGui::Checkbox("show Mods menu", &showModsMenu);

        if (showModPackMenu) {
            ImGui::Begin("modPacks");
            if (ImGui::Button("create new modPacks")) {
                if (selectModPackButtonClicked == true) {
                    selectModPackButtonClicked = false;
                }
                else if (selectModPackButtonClicked == false) {
                    selectModPackButtonClicked = true;
                }
            }
            //SHOW MODPACKS ALREDY CREATED
            if (showModPacks && !selectModPackButtonClicked) {
                FileConfigPos modInfo = getModPackPosNameStatus(ck2mConfigFile);
                for (int i = 0; i < modInfo.modPos.size(); ++i) {
                    if (ImGui::Checkbox(modInfo.name[i].c_str(), &modPackState[i])) {
                        chagneStateOfMod(ck2mConfigFile, modInfo.modPos[i], modPackState[i]);
                    }
                }
            }
        }
        if (selectModPackButtonClicked) {
            for (int i = 0; i < file.numberOfMods; ++i) {
                if (ImGui::Checkbox(file.mods[i].string().c_str(), &modStateForModpack[i])) {
                    modPosForModPack.push_back(posVec[i]);
                }
            }
            if (ImGui::Button("name Modpack")) {
                if (showMenuForNameModPack == true) {
                    showMenuForNameModPack = false;
                }
                else if (showMenuForNameModPack == false) {
                    showMenuForNameModPack = true;
                }
            }
            if (showMenuForNameModPack) {
                ImGui::InputText("", &modPackNameString, 256);
                if (ImGui::Button("create Modpack")) {
                    if (modPosForModPack.size() > 1) {
                        saveModPackInFile(ck2mConfigFile, modPackNameString, modPosForModPack);
                        modPosForModPack.clear();
                        ImGui::Text("modPack created!");

                        FileConfigPos modInfo = getModPackPosNameStatus(ck2mConfigFile);
                        modPosForModPack.clear();
                        modPackNameString.clear();
                        for (int i = 0; i < file.numberOfMods; i++) {
                            modStateForModpack[i] = false;
                        }
                    }
                }
            }
        }

        if (showModsMenu) {
            ImGui::Begin("mods");
            for (int i = 0; i < file.numberOfMods; ++i) {
                if (ImGui::Checkbox(file.mods[i].string().c_str(), &modState[i])) {
                    chagneStateOfMod(ck2mConfigFile, posVec[i], modState[i]);
                }
            }
        }


        ImGui::End();


        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(menuColor.x * menuColor.w * 255.0f), (int)(menuColor.y * menuColor.w * 255.0f), (int)(menuColor.z * menuColor.w * 255.0f), (int)(menuColor.w * 255.0f));
        g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }
    ~modMenager() {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        CleanupDeviceD3D();
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    }
};