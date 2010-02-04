// dll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "hook.h"
#include "ft.h"

extern "C" __declspec(dllexport) void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* InRemoteInfo) {}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		initialize_freetype();
		gdimm_hook::instance().hook();
		break;

	case DLL_PROCESS_DETACH:
		gdimm_hook::instance().unhook();
		destroy_freetype();
		break;
	}
	
	return TRUE;
}
