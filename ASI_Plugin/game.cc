#include "game.hh"

DWORD g_dwSAMP = 0x0;
stInputInfo* g_stInput = nullptr;

auto ToggleCursor( int mode ) -> void
{
	if( g_stInput->iInputEnabled ) return;

	void* obj = *( void** ) ( g_dwSAMP + SAMP_MISC_INFO ); // s0b
	( ( void( __thiscall* ) ( void* , int , bool ) ) ( g_dwSAMP + SAMP_TOGGLECURSOR ) )( obj , mode ? 3 : 0 , !mode );
	if( !mode )
		( ( void( __thiscall* ) ( void* ) ) ( g_dwSAMP + SAMP_CURSORUNLOCKACTORCAM ) )( obj );
}