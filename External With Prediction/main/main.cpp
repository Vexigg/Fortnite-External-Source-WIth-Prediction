#include "includes/includes.hpp"
#include <iostream>
#include <stdio.h>

#include <Windows.h>
#include <string>
#include <urlmon.h>
#include <tchar.h>

#include "general.h"
#include <random>
#include "auth.hpp"
#include <thread>
#include <cstring>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>
#include <shellapi.h>
#include "protect/SkCrypt.h"
#include "protect/xorst.h"



// Dont sell this shit or I will find u and touch you :>
//                   Happy Pasting



using namespace KeyAuth;

auto name = skCrypt("ExecutrixTemp"); // application name. right above the blurred text aka the secret on the licenses tab among other tabs
auto ownerid = skCrypt("mo4lfTExuJ"); // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
auto secret = skCrypt("32c7812a960bf90e65a7bc6a5e43157ef098663e22e7f25f47f88839800bef80"); // app secret, the blurred text on licenses tab and other tabs
auto version = skCrypt("1.0"); // leave alone unless you've changed version on website
auto url = skCrypt("https://keyauth.win/api/1.2/"); // change if you're self-hosting

api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());

void Print(const std::string& text) {
		std::cout << text;
}

std::thread titleThread;

HWND windowid = NULL;

auto main() -> int
{
	mem::find_driver();
	mouse_interface();
	KeyAuthApp.init();
	std::cout << (skCrypt("\n     [+] Waiting For Game")) << std::flush;


	while (windowid == NULL)
	{
		XorS(wind, "Fortnite  ");
		windowid = FindWindowA_Spoofed(0, wind.decrypt());
	}
	globals->hwnd = FindWindowA_Spoofed(NULL, "Fortnite  ");
	LI_FN(Sleep)(200);
	std::cout << (skCrypt("\n     [+] Found Game")) << std::flush;
	LI_FN(Sleep)(1000);
	mem::find_process("FortniteClient-Win64-Shipping.exe");
	base_address = mem::find_image();
	if (!base_address)
	{
		std::cout << (skCrypt("load the fucking driver niger !!!")) << std::flush;
	}
	globals->width = GetSystemMetrics_Spoofed(SM_CXSCREEN); globals->height = GetSystemMetrics_Spoofed(SM_CYSCREEN);

	if (Render->Setup() != RENDER_INFORMATION::RENDER_SETUP_SUCCESSFUL) ExitProcess(0);

	if (Hook->Setup() != HOOK_INFORMATION::HOOKS_SUCCESSFUL) ExitProcess(0);

	if (Game->Setup() != GAME_INFORMATION::GAME_SETUP_SUCCESSFUL) ExitProcess(0);

	Render->Render();

}

