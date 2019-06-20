#include "hooks.hh"

bool Menu = false;

auto __stdcall hooked_EndScene( IDirect3DDevice9* pDevice ) -> HRESULT
{
	static bool im_init = false;
	if( !im_init )
	{
		ImGui::CreateContext( );
		ImGui_ImplWin32_Init( m_pGameWindow );
		ImGui_ImplDX9_Init( pDevice );
		im_init = true;
	}
	if( Menu )
	{
		ImGui::CreateContext( );
		ImGui_ImplDX9_NewFrame( );
		ImGui_ImplWin32_NewFrame( );
		ImGui::NewFrame( );
		
		ImGui::EndFrame( );
		ImGui::Render( );
		ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
	}
	return oEndScene( pDevice );
}

auto __stdcall hooked_Reset( IDirect3DDevice9* m_pDevice , D3DPRESENT_PARAMETERS* pPresentationParameters ) -> HRESULT
{
	ImGui_ImplDX9_InvalidateDeviceObjects( );
	return oReset( m_pDevice , pPresentationParameters );
}

auto __stdcall WndProcHandler( HWND hwd , UINT msg , WPARAM wParam , LPARAM lParam ) -> LRESULT
{
	static bool popen = false;

	if( msg == WM_KEYDOWN )
	{
		if( wParam == VK_F2 )
		{
			bool ret = Menu;
			Menu = !Menu;
			return ret;
		}
		if( wParam == VK_ESCAPE && Menu )
		{
			Menu = false;
			return true;
		}
	}

	if( Menu )
	{
		if( !popen )
			ToggleCursor( 1 );
		popen = true;
		ImGui_ImplWin32_WndProcHandler( hwd , msg , wParam , lParam );
		return true;
	}
	else
	{
		if( popen )
		{
			popen = false;
			ToggleCursor( 0 );
		}
	}
	return CallWindowProcA( m_pWindowProc , hwd , msg , wParam , lParam );
}