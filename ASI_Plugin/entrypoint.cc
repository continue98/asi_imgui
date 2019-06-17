#include "hooks.hh"

VMTHookManager* vmtDevice = nullptr;
HWND m_pGameWindow = nullptr;
WNDPROC m_pWindowProc = nullptr;
_EndScene oEndScene = nullptr;
_Reset oReset = nullptr;

auto asi_tread( HINSTANCE DLL ) -> void
{
	while( !GetModuleHandleA( "samp.dll" ) || *( DWORD* ) SAMP_GAMESTATE != 9 )
		Sleep( 100 );

	g_dwSAMP = ( DWORD ) GetModuleHandleA( "samp.dll" );
	g_stInput = ( stInputInfo* ) ( g_dwSAMP + SAMP_CHAT_INPUT );

	m_pGameWindow = FindWindowA( 0 , "GTA:SA:MP" );
	m_pWindowProc = ( WNDPROC ) SetWindowLongPtr( m_pGameWindow , GWL_WNDPROC , ( LONG_PTR ) WndProcHandler );

	void** vTableDevice = *( void*** ) ( *( DWORD* ) SAMP_DEVICE );

	vmtDevice = new VMTHookManager( vTableDevice );
	oEndScene = ( _EndScene ) vmtDevice->Hook( DEVICE_ENDSCENE , ( void* ) hooked_EndScene );
	oReset = ( _Reset ) vmtDevice->Hook( DEVICE_RESET , ( void* ) hooked_Reset );

	while( !GetAsyncKeyState( VK_END ) )
		Sleep( 150 );

	SetWindowLongPtr( m_pGameWindow , GWLP_WNDPROC , LONG_PTR( m_pWindowProc ) );
	vmtDevice->UnhookAll( );

	FreeLibraryAndExitThread( static_cast< HMODULE >( DLL ) , EXIT_SUCCESS );
}

auto __stdcall DllMain( HINSTANCE hinst , DWORD reason , LPVOID reserved ) -> int
{
	if( reason == DLL_PROCESS_ATTACH )
		CreateThread( nullptr , 0 , ( LPTHREAD_START_ROUTINE ) asi_tread , hinst , 0 , nullptr );

	return TRUE;
}