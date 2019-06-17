#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "imgui-master/imgui.h"
#include "imgui-master/imgui_impl_win32.h"
#include "imgui-master/imgui_impl_dx9.h"
#include "imgui-master/imgui_stdlib.h"
#include "imgui-master/imgui_internal.h"

#include "vmt.hh"

#include "game.hh"

extern VMTHookManager* vmtDevice;

typedef HRESULT( __stdcall* _EndScene )( IDirect3DDevice9* );
typedef HRESULT( __stdcall* _Reset )( IDirect3DDevice9* , D3DPRESENT_PARAMETERS* );

extern _EndScene oEndScene;
extern _Reset oReset;
extern HWND m_pGameWindow;
extern WNDPROC m_pWindowProc;

extern HRESULT __stdcall hooked_EndScene( IDirect3DDevice9* );
extern HRESULT __stdcall hooked_Reset( IDirect3DDevice9* , D3DPRESENT_PARAMETERS* );
extern LRESULT __stdcall WndProcHandler( HWND , UINT , WPARAM , LPARAM );

extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam );