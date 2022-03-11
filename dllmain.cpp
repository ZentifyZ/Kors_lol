#pragma warning(disable : 4530)
#define StrA
#define StrW

#include "pch.h"

#ifndef _DEBUG
#include "..\P402.Cryptograhpy\Auth.h"
#endif

#include "Bypass\Header\AAnticheat.h"
#include "RustInternal.h"
#include "Protector\nt_.hpp"
#include "Protector\Processes.h"

// Place detach codes, such as unhooks and unpatching things
// tho generally useless unless you are just testing using loadlib
// other than that, since we will be manualmapping, these things go out the windows
//
auto Detach() -> bool
{
	return true;
}

auto Initialize() -> bool
{
	// This prevent us from crashing the client, use SEH religiously
	//
	__try
	{
		return Rust::InitializeRust();
	}

	__except ([](unsigned int code, struct _EXCEPTION_POINTERS* ep) -> int
		{
			Ulog("Exception happened in (%s) with code %lx - at RIP %p | %p ", __FUNCTION__,
				code, ep->ExceptionRecord->ExceptionAddress, Globals::g_Module);

			return EXCEPTION_EXECUTE_HANDLER;
		}(GetExceptionCode(), GetExceptionInformation()))
	{
	}

		return false;
}

// Initializtion logics goes in here
auto P402K(LPVOID k_credential) -> bool
{
#ifndef P402DISTRIBUTE
	// Dashed out due to creating debug log in IMGUI
	//FILE* fp; AllocConsole();
//	freopen_s(&fp, "CONOUT$", "w", stdout);
#endif // !P402DISTRIBUTE

	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		/* Must run this before everything because we need it to resolve the APIs that we use */
		//
		if (!Internal::DynamicImportWinAPIs())
		{
			Ulog("%s - Failed to resolve dynamic winapis.", __FUNCTION__);
			return true;
		}

#ifdef P402DISTRIBUTE
		if (ARE_BAD_TOOLS_RUNNING())
		{
			return true;
		}

		CHAR imageName[MAX_PATH] = { 0 };
		GetModuleBaseNameA(GetCurrentProcess(), NULL, imageName, MAX_PATH);

		// Check if we have license for our current game.
		//
		if (strcmp(imageName, xorstr_("RustClient.exe")) == 0)
#endif
		{
#ifndef _DEBUG
			PCredential pCredential = reinterpret_cast<PCredential>(k_credential);

			if (!k_credential)
			{
				return true;
			}

			G::EAC_UM_BASE = pCredential->EacUsermodeBaseAddress;
			G::EAC_UM_SIZE = pCredential->EacUsermodeSize;
			G::EAC_UM_DllEntry = pCredential->EacUsermodeDllEntry;
			G::g_ModuleSize = pCredential->ImageSize;

			// Will also copy the cpy_credential into local_credential
			// wont run if you are under debugging
			//
			auto auth = Auth::AuthenticateGame(pCredential);

			memset((PVOID)pCredential->DllMainStartAddress, 0, 0x1000);

			if (!auth || auth->Status_Code != 1 || !auth->license_status || auth->license_status != local_credential.Gameid)
			{
				if (auth)
				{
					switch (auth->Status_Code)
					{
					case 0:
						MessageBoxW(NULL, xorstr_(L"Authentication failure due to server or network issue."), xorstr_(L"Authentication failure"), 0x40000); break;
					case 2:
						MessageBoxW(NULL, xorstr_(L"Authentication failure due to incorrect username / password."), xorstr_(L"Authentication failure"), 0x40000); break;
					case 3:
#ifdef _RESELLER
						MessageBoxW(NULL, xorstr_(L"HWID Change detected. Please use https://licensing.pw to reset your HWID.."), xorstr_(L"Authentication failure"), 0x40000); break;
#else
						MessageBoxW(NULL, xorstr_(L"This tool is linked to your Hardware ID. A Hardware ID change has been detected. Please message @LastBot on discord to reset your Hardware ID."), xorstr_(L"Authentication failure"), 0x40000); break;
#endif
					case 4:
						MessageBoxW(NULL, xorstr_(L"Authentication failure due to expired license."), xorstr_(L"Authentication failure"), 0x40000); break;
					default:
						break;
					}
				}
				else
				{
					MessageBoxW(NULL, xorstr_(L"Authentication failure due to connectivity to the server, check your network connection before trying again."), xorstr_(L"Authentication failure"), 0x40000);
				}

				Ulog("User not authorized");
				return true;
			}

			// free the auth struct
			//
			if (auth)
			{
				delete[] auth; auth = 0;
			}
#endif // !_DEBUG

#ifndef P402DISTRIBUTE
			Ulog("User is biggly authorized to talk to Hercules.");
#endif
		}

		if (Initialize())
		{
			Ulog("Welcome [ Last Cheat team ], to Project 402k. [%p]", Globals::g_Module);
			Ulog("**********************************************************************************\n");
			Globals::Ready = true;
		}
		else
		{
			Ulog("Failed to load P402K");

#ifdef P402DISTRIBUTE
			TerminateProcess(GetCurrentProcess(), 0);
#endif
		}
	}
	__except (
		ExceptionCode = GetExceptionCode(),
		ExceptionPointers = GetExceptionInformation(),
		EXCEPTION_EXECUTE_HANDLER
		) {
		if (ExceptionPointers)
		{
#ifdef P402DISTRIBUTE
			wchar_t ErrorMsg[200];
			swprintf_s(ErrorMsg, L"Could not initialized Rust cheat with code 0x%lx | %p | %p", ExceptionCode, Globals::g_Module, ExceptionPointers->ExceptionRecord->ExceptionAddress);
			MessageBox(NULL, ErrorMsg, NULL, MB_OK);
#else
			Ulog("Exception (%lx) caught in %s @ (%p)",
				ExceptionCode, __FUNCTION__,
				ExceptionPointers->ExceptionRecord->ExceptionAddress
			);
#endif
		}
	}

	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Globals::g_Module = hModule;
		return P402K(lpReserved);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		return Detach();
	case DLL_PROCESS_DETACH:
		break;
	}
	return true;
}