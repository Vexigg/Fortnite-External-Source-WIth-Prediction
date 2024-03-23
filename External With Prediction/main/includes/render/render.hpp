#include <D3DX11tex.h>
#include "fonts.h"
#include  "images.h"
#include <vector>
#include "../../../main/New  Shit/Color_draw.hpp"
#include "protect/crypt.h"
#include "../../dependencies/gui/imgui_internal.h"
#include "../../fonts.h"

#include "../../cusyto.hpp"

int cheatStatus = 2;
































// Dont sell this shit or I will find u and touch you :>
//                   Happy Pasting

// Change to your cheat name :>

std::string watermark = "asfnmware";


































enum RENDER_INFORMATION : int {
	RENDER_HIJACK_FAILED = 0,
	RENDER_IMGUI_FAILED = 1,
	RENDER_DRAW_FAILED = 2,
	RENDER_SETUP_SUCCESSFUL = 3
};

FVector PlayerFlyAddValue; //outside the loop
FVector PlayerFlySetLocation; //outside the loop

static int curtab;
static bool checkbox;
static float slider;
static float anti;
static float aim;
static int slider1;

//const char* weapon_selection[]{ "ASSAULT", "SHOTGUN", "SMG", "SNIPER" };
static int curWeapon = 0;
static int curTheme = 2;
static int combo;
static int selectedItem = 0;
static bool selected[4];
static std::string previewValue = "";

float r1;
float g1;
float b2;
float a1 = 0.5;
static int combo2;
float color_edit4[4] = { 1.00f, 0.00f, 0.20f, 0.80f };

float accent_color[4] = { 1.00f, 0.00f, 0.20f, 0.80f };

static int select_count = 0;
int tab_count = 0;
bool active = false;
float size_child = 0;

std::string FloatArrayToString(const float* array, int size) {
	std::ostringstream oss;
	for (int i = 0; i < size; ++i) {
		oss << array[i];
		if (i < size - 1) oss << ",";
	}
	return oss.str();
}

std::vector<float> StringToFloatArray(const std::string& str) {
	std::vector<float> result;
	std::istringstream iss(str);
	std::string token;

	while (std::getline(iss, token, ',')) {
		result.push_back(std::stof(token));
	}

	return result;
}

void ReadColorsFromIni(std::string file, std::string app, std::string key, float* colorArray, int colorArraySize) {
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), _xor_("NULL").c_str(), buf, 100, file.c_str());

	if (strcmp(buf, _xor_("NULL").c_str()) != 0) {
		std::vector<float> colors = StringToFloatArray(buf);
		if (colors.size() == colorArraySize) {
			// Apply the loaded colors to the colorArray
			for (int i = 0; i < colorArraySize; ++i) {
				colorArray[i] = colors[i];
			}
		}
		else {
			// Handle error: Incorrect number of color components in the loaded string
			system(_xor_("cls").c_str());
			std::cout << _xor_(" [").c_str() << _xor_("ERR - 15").c_str() << _xor_("] - Incorrect number of color components.").c_str();
			Sleep(5000);
			exit(0);
		}
	}
}

inline static int keystatus = 0;

inline static int realkey = 0;

inline static int realkey1 = 0;
inline static int keystatus1 = 0;
inline static int keystatus2 = 0;
inline static int keystatus3 = 0;
inline static int keystatus4 = 0;
char* name1;

inline int aimkey = 0;
inline bool GetKey(int key)
{
	realkey = key;
	return true;
}
inline void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetAsyncKeyState_Spoofed(i) & 0x8000)
			{
				globals->aimbot_key = i;
				keystatus = 0;
				return;
			}
		}
	}
}

inline bool GetKey1(int key)
{
	realkey1 = key;
	return true;
}
inline void ChangeKey1(void* blank)
{
	keystatus1 = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetAsyncKeyState_Spoofed(i) & 0x8000)
			{
				keystatus1 = 0;
				return;
			}
		}
	}
}

inline bool GetKey2(int key)
{
	realkey1 = key;
	return true;
}
inline void ChangeKey2(void* blank)
{
	keystatus2 = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetAsyncKeyState_Spoofed(i) & 0x8000)
			{
				keystatus2 = 0;
				return;
			}
		}
	}
}

inline void ChangeKey3(void* blank)
{
	keystatus3 = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetAsyncKeyState_Spoofed(i) & 0x8000)
			{
				keystatus3 = 0;
				return;
			}
		}
	}
}

inline void ChangeKey4(void* blank)
{
	keystatus4 = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetAsyncKeyState_Spoofed(i) & 0x8000)
			{
				keystatus4 = 0;
				return;
			}
		}
	}
}

inline void DrawBox(float X, float Y, float W, float H, const ImU32& color, int thickness)
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

static const char* keyNames[] =
{
	"Keybind",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

inline static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
inline void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);
	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = (("Select Key"));
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = (("Press the Key"));
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(200, 30)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}

ImFont* LexendDecaFont;
ImFont* IconFont;
//Infracted Fonts
ImFont* default_segu = nullptr;
ImFont* bold_segu = nullptr;
ImFont* ico = nullptr;
ImFont* ico_combo = nullptr;
ImFont* ico_button = nullptr;
ImFont* ico_grande = nullptr;

ImFont* IconFontLogs;
ImFont* InterMedium;
ImFont* TestFont;

ImFont* InterMediumone;
auto s = ImVec2{}, p = ImVec2{}, gs = ImVec2{ 662, 460 };

IDirect3DTexture9* bgs = nullptr;
ID3D11ShaderResourceView* logo = nullptr;
ID3D11ShaderResourceView* normal = nullptr;
ID3D11ShaderResourceView* skeleton = nullptr;
ID3D11ShaderResourceView* head = nullptr;
ID3D11ShaderResourceView* headskel = nullptr;

ID3D11ShaderResourceView* circle = nullptr;

IDirect3DTexture9* foto = nullptr;
IDirect3DTexture9* merfthefurry = nullptr;
IDirect3DTexture9* ghoul = nullptr;
HWND window_handle;

ID3D11Device* d3d_device;
IDirect3DDevice9* d3d_device2;
ID3D11DeviceContext* d3d_device_ctx;
IDXGISwapChain* d3d_swap_chain;
ID3D11RenderTargetView* d3d_render_target;
D3DPRESENT_PARAMETERS d3d_present_params;
ID3D11ShaderResourceView* playermodel = nullptr;
ImDrawList* drawlist;
ImVec2 pos;
ImFont* descriptionfont;
ImFont* icons;
ImDrawList* tabdrawlist;
ImFont* comboarrow;
int tabs = 0;

namespace Variables {
	int ActiveTab = 1;
}
static const char* KeyNames1[] = {
	"Aimbot Bot Key",
	"VK_LBUTTON",
	"VK_RBUTTON",
	"VK_CANCEL",
	"VK_MBUTTON",
	"VK_XBUTTON1",
	"VK_XBUTTON2",
	"Unknown",
	"VK_BACK",
	"VK_TAB",
	"Unknown",
	"Unknown",
	"VK_CLEAR",
	"VK_RETURN",
	"Unknown",
	"Unknown",
	"VK_SHIFT",
	"VK_CONTROL",
	"VK_MENU",
	"VK_PAUSE",
	"VK_CAPITAL",
	"VK_KANA",
	"Unknown",
	"VK_JUNJA",
	"VK_FINAL",
	"VK_KANJI",
	"Unknown",
	"VK_ESCAPE",
	"VK_CONVERT",
	"VK_NONCONVERT",
	"VK_ACCEPT",
	"VK_MODECHANGE",
	"VK_SPACE",
	"VK_PRIOR",
	"VK_NEXT",
	"VK_END",
	"VK_HOME",
	"VK_LEFT",
	"VK_UP",
	"VK_RIGHT",
	"VK_DOWN",
	"VK_SELECT",
	"VK_PRINT",
	"VK_EXECUTE",
	"VK_SNAPSHOT",
	"VK_INSERT",
	"VK_DELETE",
	"VK_HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"VK_LWIN",
	"VK_RWIN",
	"VK_APPS",
	"Unknown",
	"VK_SLEEP",
	"VK_NUMPAD0",
	"VK_NUMPAD1",
	"VK_NUMPAD2",
	"VK_NUMPAD3",
	"VK_NUMPAD4",
	"VK_NUMPAD5",
	"VK_NUMPAD6",
	"VK_NUMPAD7",
	"VK_NUMPAD8",
	"VK_NUMPAD9",
	"VK_MULTIPLY",
	"VK_ADD",
	"VK_SEPARATOR",
	"VK_SUBTRACT",
	"VK_DECIMAL",
	"VK_DIVIDE",
	"VK_F1",
	"VK_F2",
	"VK_F3",
	"VK_F4",
	"VK_F5",
	"VK_F6",
	"VK_F7",
	"VK_F8",
	"VK_F9",
	"VK_F10",
	"VK_F11",
	"VK_F12",
	"VK_F13",
	"VK_F14",
	"VK_F15",
	"VK_F16",
	"VK_F17",
	"VK_F18",
	"VK_F19",
	"VK_F20",
	"VK_F21",
	"VK_F22",
	"VK_F23",
	"VK_F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_NUMLOCK",
	"VK_SCROLL",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_LSHIFT",
	"VK_RSHIFT",
	"VK_LCONTROL",
	"VK_RCONTROL",
	"VK_LMENU",
	"VK_RMENU"
};

std::string congratsmen = "Hus X Veru";

static const char* KeyNames[] = {
	"Trigger Bot Key",
	"VK_LBUTTON",
	"VK_RBUTTON",
	"VK_CANCEL",
	"VK_MBUTTON",
	"VK_XBUTTON1",
	"VK_XBUTTON2",
	"Unknown",
	"VK_BACK",
	"VK_TAB",
	"Unknown",
	"Unknown",
	"VK_CLEAR",
	"VK_RETURN",
	"Unknown",
	"Unknown",
	"VK_SHIFT",
	"VK_CONTROL",
	"VK_MENU",
	"VK_PAUSE",
	"VK_CAPITAL",
	"VK_KANA",
	"Unknown",
	"VK_JUNJA",
	"VK_FINAL",
	"VK_KANJI",
	"Unknown",
	"VK_ESCAPE",
	"VK_CONVERT",
	"VK_NONCONVERT",
	"VK_ACCEPT",
	"VK_MODECHANGE",
	"VK_SPACE",
	"VK_PRIOR",
	"VK_NEXT",
	"VK_END",
	"VK_HOME",
	"VK_LEFT",
	"VK_UP",
	"VK_RIGHT",
	"VK_DOWN",
	"VK_SELECT",
	"VK_PRINT",
	"VK_EXECUTE",
	"VK_SNAPSHOT",
	"VK_INSERT",
	"VK_DELETE",
	"VK_HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"VK_LWIN",
	"VK_RWIN",
	"VK_APPS",
	"Unknown",
	"VK_SLEEP",
	"VK_NUMPAD0",
	"VK_NUMPAD1",
	"VK_NUMPAD2",
	"VK_NUMPAD3",
	"VK_NUMPAD4",
	"VK_NUMPAD5",
	"VK_NUMPAD6",
	"VK_NUMPAD7",
	"VK_NUMPAD8",
	"VK_NUMPAD9",
	"VK_MULTIPLY",
	"VK_ADD",
	"VK_SEPARATOR",
	"VK_SUBTRACT",
	"VK_DECIMAL",
	"VK_DIVIDE",
	"VK_F1",
	"VK_F2",
	"VK_F3",
	"VK_F4",
	"VK_F5",
	"VK_F6",
	"VK_F7",
	"VK_F8",
	"VK_F9",
	"VK_F10",
	"VK_F11",
	"VK_F12",
	"VK_F13",
	"VK_F14",
	"VK_F15",
	"VK_F16",
	"VK_F17",
	"VK_F18",
	"VK_F19",
	"VK_F20",
	"VK_F21",
	"VK_F22",
	"VK_F23",
	"VK_F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_NUMLOCK",
	"VK_SCROLL",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_LSHIFT",
	"VK_RSHIFT",
	"VK_LCONTROL",
	"VK_RCONTROL",
	"VK_LMENU",
	"VK_RMENU"
};
static const int KeyCodes[] = {
	0x0,  //Undefined
	0x01,
	0x02,
	0x03,
	0x04,
	0x05,
	0x06,
	0x07, //Undefined
	0x08,
	0x09,
	0x0A, //Reserved
	0x0B, //Reserved
	0x0C,
	0x0D,
	0x0E, //Undefined
	0x0F, //Undefined
	0x10,
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16, //IME On
	0x17,
	0x18,
	0x19,
	0x1A, //IME Off
	0x1B,
	0x1C,
	0x1D,
	0x1E,
	0x1F,
	0x20,
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,
	0x29,
	0x2A,
	0x2B,
	0x2C,
	0x2D,
	0x2E,
	0x2F,
	0x30,
	0x31,
	0x32,
	0x33,
	0x34,
	0x35,
	0x36,
	0x37,
	0x38,
	0x39,
	0x3A, //Undefined
	0x3B, //Undefined
	0x3C, //Undefined
	0x3D, //Undefined
	0x3E, //Undefined
	0x3F, //Undefined
	0x40, //Undefined
	0x41,
	0x42,
	0x43,
	0x44,
	0x45,
	0x46,
	0x47,
	0x48,
	0x49,
	0x4A,
	0x4B,
	0x4C,
	0x4B,
	0x4E,
	0x4F,
	0x50,
	0x51,
	0x52,
	0x53,
	0x54,
	0x55,
	0x56,
	0x57,
	0x58,
	0x59,
	0x5A,
	0x5B,
	0x5C,
	0x5D,
	0x5E, //Rservered
	0x5F,
	0x60, //Numpad1
	0x61, //Numpad2
	0x62, //Numpad3
	0x63, //Numpad4
	0x64, //Numpad5
	0x65, //Numpad6
	0x66, //Numpad7
	0x67, //Numpad8
	0x68, //Numpad8
	0x69, //Numpad9
	0x6A,
	0x6B,
	0x6C,
	0x6D,
	0x6E,
	0x6F,
	0x70, //F1
	0x71, //F2
	0x72, //F3
	0x73, //F4
	0x74, //F5
	0x75, //F6
	0x76, //F7
	0x77, //F8
	0x78, //F9
	0x79, //F10
	0x7A, //F11
	0x7B, //F12
	0x7C, //F13
	0x7D, //F14
	0x7E, //F15
	0x7F, //F16
	0x80, //F17
	0x81, //F18
	0x82, //F19
	0x83, //F20
	0x84, //F21
	0x85, //F22
	0x86, //F23
	0x87, //F24
	0x88, //Unkown
	0x89, //Unkown
	0x8A, //Unkown
	0x8B, //Unkown
	0x8C, //Unkown
	0x8D, //Unkown
	0x8E, //Unkown
	0x8F, //Unkown
	0x90,
	0x91,
	0x92, //OEM Specific
	0x93, //OEM Specific
	0x94, //OEM Specific
	0x95, //OEM Specific
	0x96, //OEM Specific
	0x97, //Unkown
	0x98, //Unkown
	0x99, //Unkown
	0x9A, //Unkown
	0x9B, //Unkown
	0x9C, //Unkown
	0x9D, //Unkown
	0x9E, //Unkown
	0x9F, //Unkown
	0xA0,
	0xA1,
	0xA2,
	0xA3,
	0xA4,
	0xA5
};

float BOG_TO_GRD(float BOG) {
	return (180 / M_PI) * BOG;
}

float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}
void HotKey(int* k, const ImVec2& size_arg = ImVec2(0, 0))
{
	static bool waitingforkey = false;
	if (waitingforkey == false) {
		if (ImGui::Button(KeyNames1[*(int*)k], size_arg))
			waitingforkey = true;
	}
	else if (waitingforkey == true) {
		ImGui::Button("...", size_arg);
		Sleep(50);
		for (auto& Key : KeyCodes)
		{
			if (GetAsyncKeyState_Spoofed(Key)) {
				*(int*)k = Key;
				waitingforkey = false;
			}
		}
	}
}

void HotKey2(int* k, const ImVec2& size_arg = ImVec2(0, 0))
{
	static bool waitingforkey = false;
	if (waitingforkey == false) {
		if (ImGui::Button(KeyNames[*(int*)k], size_arg))
			waitingforkey = true;
	}
	else if (waitingforkey == true) {
		ImGui::Button("...", size_arg);
		Sleep(50);
		for (auto& Key : KeyCodes)
		{
			if (GetAsyncKeyState_Spoofed(Key)) {
				*(int*)k = Key;
				waitingforkey = false;
			}
		}
	}
}

void HotKeytrig(int* k, const ImVec2& size_arg = ImVec2(0, 0))
{
	static bool waitingforkey = false;
	if (waitingforkey == false) {
		if (ImGui::Button(KeyNames[*(int*)k], size_arg))
			waitingforkey = true;
	}
	else if (waitingforkey == true) {
		ImGui::Button("...", size_arg);
		Sleep(50);
		for (auto& Key : KeyCodes)
		{
			if (GetAsyncKeyState_Spoofed(Key)) {
				*(int*)k = Key;
				waitingforkey = false;
			}
		}
	}
}

 


int tab;
static int enemy_tab;

namespace Preview
{
	namespace box3d {
		float topleftfront_x = -72.f;
		float topleftfront_y = 82.f;

		float topleftback_x = -54.f;
		float topleftback_y = 61.f;

		float toprightfront_x = 61.f;
		float toprightfront_y = 82.f;

		float toprightback_x = 74.f;
		float toprightback_y = 61.f;

		float bottomleftfront_x = -85.f;
		float bottomleftfront_y = 335.f;

		float bottomleftback_x = -67.f;
		float bottomleftback_y = 305.f;

		float bottomrightfront_x = 49.f;
		float bottomrightfront_y = 342.f;

		float bottomrightback_x = 64.f;
		float bottomrightback_y = 312.f;
	}

	float head_bone_x = 0;
	float head_bone_y = 94;

	float neck_bone_x = 4;
	float neck_bone_y = 114;

	float chest_bone_x = 2;
	float chest_bone_y = 122;

	float left_shoulder_bone_x = -24;
	float left_shoulder_bone_y = 124;

	float left_elbow_bone_x = -37;
	float left_elbow_bone_y = 153;

	float left_hand_bone_x = -51;
	float left_hand_bone_y = 196;

	float right_hand_bone_x = 47;
	float right_hand_bone_y = 190;

	float right_elbow_bone_x = 43;
	float right_elbow_bone_y = 167;

	float right_shoulder_bone_x = 20;
	float right_shoulder_bone_y = 124;

	float pelvis_bone_x = -6;
	float pelvis_bone_y = 184;

	float left_thigh_bone_x = -22;
	float left_thigh_bone_y = 186;

	float right_thigh_bone_x = 12;
	float right_thigh_bone_y = 186;

	float right_knee_bone_x = 25;
	float right_knee_bone_y = 253;

	float left_knee_bone_x = -37;
	float left_knee_bone_y = 245;

	float right_foot_bone_x = 31;
	float right_foot_bone_y = 310;

	float left_foot_bone_x = -47;
	float left_foot_bone_y = 308;

	float right_footfinger_bone_x = 37;
	float right_footfinger_bone_y = 324;

	float left_footfinger_bone_x = -57;
	float left_footfinger_bone_y = 322;
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

inline void DrawFilledRect(int x, int y, int w, int h, ImU32 color, bool round = false)
{
	if (round)
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, ImDrawCornerFlags_All, 30);
	else
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

 

inline void DrawRect(int x, int y, int w, int h, ImU32 color, bool round = false)
{
	if (round)
		ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, ImDrawCornerFlags_All, 30);
	else
		ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

void RenderBox(bool ForeGround, float OffsetW, float OffsetH, int X, int Y, int W, int H, ImVec4 Color, int thickness, bool Filled, bool NoCorner) {
	float lineW = (W / OffsetW);
	float lineH = (H / OffsetH);
	ImDrawList* p = ImGui::GetBackgroundDrawList();
	if (ForeGround)
		p = ImGui::GetForegroundDrawList();

	if (Filled) {
		auto Converted = IM_COL32(Color.x * 255, Color.y * 255, Color.z * 255, 40);
		DrawFilledRect(ForeGround, X, Y, W, H, Converted);
	}
	if (NoCorner) {
		auto Converted = IM_COL32(Color.x * 255, Color.y * 255, Color.z * 255, Color.w * 255);
		DrawRect(ForeGround, X, Y, W, H, Converted);
	}
	else {
		//oben links nach unten
		p->AddLine(ImVec2(X, Y - 1), ImVec2(X, Y + lineH), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//oben links nach rechts (l-mittig)
		p->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//oben rechts (r-mittig) nach rechts
		p->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W + 2, Y), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//oben rechts nach vert-rechts (oberhalb)
		p->AddLine(ImVec2(X + W, Y - 1), ImVec2(X + W, Y + lineH), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten vert-links (unterhalb) nach unten links
		p->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten links nach rechts (mittig)
		p->AddLine(ImVec2(X - 1, Y + H), ImVec2(X + lineW + 1, Y + H), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten rechts (mittig) nach rechts
		p->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W + 2, Y + H), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten rechts nach vert-rechts (unterhalb)
		p->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);
	}
}

void RenderBox2(bool ForeGround, float OffsetW, float OffsetH, int X, int Y, int W, int H, ImVec4 Color, int thickness, bool Filled, bool NoCorner) {
	float lineW = (W / OffsetW);
	float lineH = (H / OffsetH);
	ImDrawList* p = ImGui::GetBackgroundDrawList();
	if (ForeGround)
		p = ImGui::GetForegroundDrawList();

	if (Filled) {
		auto Converted = IM_COL32(Color.x * 255, Color.y * 255, Color.z * 255, 40);
		DrawFilledRect(ForeGround, X, Y, W, H, Converted);
	}
	if (NoCorner) {
		auto Converted = IM_COL32(Color.x * 255, Color.y * 255, Color.z * 255, Color.w * 255);
		DrawRect(ForeGround, X, Y, W, H, Converted);
	}
	else {
		ImVec2 topLeft = ImVec2(X, Y);
		ImVec2 bottomRight = ImVec2(X + W, Y + H);

		// Calculate the radius for the rounded corners (adjust this value as needed)
		float cornerRadius = 5.0f;

		// Draw the rounded rectangle box
		p->AddRect(topLeft, bottomRight, ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), cornerRadius, ImDrawCornerFlags_All, thickness);
	}
}

void RenderBox1(bool ForeGround, float OffsetW, float OffsetH, int X, int Y, int W, int H, ImVec4 Color, int thickness, bool Filled, bool NoCorner) {
	float lineW = (W / OffsetW);
	float lineH = (H / OffsetH);
	ImDrawList* p = ImGui::GetBackgroundDrawList();
	if (ForeGround)
		p = ImGui::GetForegroundDrawList();

	if (Filled) {
		auto Converted = IM_COL32(Color.x * 255, Color.y * 255, Color.z * 255, 40);
		DrawFilledRect(ForeGround, X, Y, W, H, Converted);
	}
	if (NoCorner) {
		auto Converted = IM_COL32(Color.x * 255, Color.y * 255, Color.z * 255, Color.w * 255);
		DrawRect(ForeGround, X, Y, W, H, Converted);
	}
	else {
		ImVec2 topLeft = ImVec2(X, Y);
		ImVec2 topRight = ImVec2(X + W, Y);
		ImVec2 bottomLeft = ImVec2(X, Y + H);
		ImVec2 bottomRight = ImVec2(X + W, Y + H);

		// Draw the lines to create the box
		p->AddLine(topLeft, topRight, ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);
		p->AddLine(topRight, bottomRight, ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);
		p->AddLine(bottomRight, bottomLeft, ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);
		p->AddLine(bottomLeft, topLeft, ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);
	}
}

namespace render {
	class c_render {
	public:
		auto Setup() -> RENDER_INFORMATION {
			if (!render::c_render::hijack()) return RENDER_HIJACK_FAILED;

			if (!render::c_render::ImGui()) return RENDER_IMGUI_FAILED;

			return RENDER_SETUP_SUCCESSFUL;
		}



		auto Render() -> bool {
			static RECT rect_og;
			MSG msg = { NULL };
			ZeroMemory(&msg, sizeof(MSG));

			while (msg.message != WM_QUIT)
			{
				UpdateWindow_Spoofed(window_handle);
				ShowWindow_Spoofed(window_handle, SW_SHOW);

				if ((PeekMessageA_Spoofed)(&msg, window_handle, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				ImGuiIO& io = ImGui::GetIO();
				io.ImeWindowHandle = window_handle;
				io.DeltaTime = 1.0f / 60.0f;

				POINT p_cursor;
				GetCursorPos(&p_cursor);
				io.MousePos.x = p_cursor.x;
				io.MousePos.y = p_cursor.y;

				if (GetAsyncKeyState_Spoofed(VK_LBUTTON)) {
					io.MouseDown[0] = true;
					io.MouseClicked[0] = true;
					io.MouseClickedPos[0].x = io.MousePos.x;
					io.MouseClickedPos[0].x = io.MousePos.y;
				}
				else
					io.MouseDown[0] = false;


				render::c_render::Draw();
			}
			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();

			(DestroyWindow)(window_handle);

			return true;
		}

		auto ImGui() -> bool {
			DXGI_SWAP_CHAIN_DESC swap_chain_description = {};
			swap_chain_description.BufferCount = 2;
			swap_chain_description.BufferDesc.Width = 0; // Set the appropriate width based on your requirements
			swap_chain_description.BufferDesc.Height = 0; // Set the appropriate height based on your requirements
			swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swap_chain_description.BufferDesc.RefreshRate.Numerator = 60;
			swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;
			swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swap_chain_description.OutputWindow = window_handle;
			swap_chain_description.SampleDesc.Count = 1;
			swap_chain_description.SampleDesc.Quality = 0;
			swap_chain_description.Windowed = TRUE;
			swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			D3D_FEATURE_LEVEL d3d_feature_lvl;

			const D3D_FEATURE_LEVEL d3d_feature_array[1] = { D3D_FEATURE_LEVEL_11_0 };

			D3D11CreateDeviceAndSwapChain(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				0,
				d3d_feature_array,
				1,
				D3D11_SDK_VERSION,
				&swap_chain_description,
				&d3d_swap_chain,
				&d3d_device,
				&d3d_feature_lvl,
				&d3d_device_ctx);

			ID3D11Texture2D* pBackBuffer;

			d3d_swap_chain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

			d3d_device->CreateRenderTargetView(pBackBuffer, NULL, &d3d_render_target);

			pBackBuffer->Release();

			IMGUI_CHECKVERSION();

			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO();

			io.IniFilename = NULL;

			(void)io;
			D3DX11_IMAGE_LOAD_INFO info;
			ID3DX11ThreadPump* pump{ nullptr };
			
			D3DX11CreateShaderResourceViewFromMemory(d3d_device, gingerbread, sizeof(gingerbread), &info, pump, &normal, 0);
			D3DX11CreateShaderResourceViewFromMemory(d3d_device, gingerskel, sizeof(gingerskel), &info, pump, &skeleton, 0);
			D3DX11CreateShaderResourceViewFromMemory(d3d_device, gingerhead, sizeof(gingerhead), &info, pump, &head, 0);
			D3DX11CreateShaderResourceViewFromMemory(d3d_device, headskels, sizeof(headskels), &info, pump, &headskel, 0);
			D3DX11CreateShaderResourceViewFromMemory(d3d_device, circles, sizeof(circles), &info, pump, &circle, 0);

			io.Fonts->AddFontFromMemoryTTF(kuwa, sizeof(kuwa), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
			default_segu = io.Fonts->AddFontFromMemoryTTF(kuwa, sizeof(kuwa), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
			ico = io.Fonts->AddFontFromMemoryTTF(icon, sizeof(icon), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
			bold_segu = io.Fonts->AddFontFromMemoryTTF(kuwa, sizeof(kuwa), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());




			IconFont = io.Fonts->AddFontFromMemoryTTF(Icons, sizeof(Icons), 23, NULL, io.Fonts->GetGlyphRangesCyrillic());
			IconFontLogs = io.Fonts->AddFontFromMemoryTTF(IconFontLog, sizeof(IconFontLog), 25, NULL, io.Fonts->GetGlyphRangesCyrillic());
			LexendDecaFont = io.Fonts->AddFontFromMemoryTTF(kuwa, sizeof(kuwa), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
			InterMedium = io.Fonts->AddFontFromMemoryTTF(kuwa, sizeof(kuwa), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
			TestFont = io.Fonts->AddFontFromMemoryTTF(kuwa, sizeof(kuwa), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());

			//InterMediumone = io.Fonts->AddFontFromMemoryTTF(Intermedium, sizeof(Intermedium), 14, NULL, io.Fonts->GetGlyphRangesCyrillic());

			ImGui_ImplWin32_Init(window_handle);

			ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);

			d3d_device->Release();

			return true;
		}



		DWORD FindProcessId(const char* ProcessName)
		{
			PROCESSENTRY32 processInfo;
			processInfo.dwSize = sizeof(processInfo);

			HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
			if (processesSnapshot == INVALID_HANDLE_VALUE)
				return 0;

			Process32First(processesSnapshot, &processInfo);
			if (!strcmp(processInfo.szExeFile, ProcessName))
			{
				CloseHandle_Spoofed(processesSnapshot);
				return processInfo.th32ProcessID;
			}

			while (Process32Next(processesSnapshot, &processInfo))
			{
				if (!strcmp(processInfo.szExeFile, ProcessName))
				{
					CloseHandle_Spoofed(processesSnapshot);
					return processInfo.th32ProcessID;
				}
			}

			CloseHandle_Spoofed(processesSnapshot);
			return 0;
		}

		static HWND get_gdi_window(int dwProcessID)
		{
			HWND hCurWnd = nullptr;
			while (true)
			{
				hCurWnd = FindWindowEx(nullptr, hCurWnd, nullptr, nullptr);
				DWORD checkProcessID;
				GetWindowThreadProcessId(hCurWnd, &checkProcessID);
				if (checkProcessID == dwProcessID)
				{
					char className[256];
					GetClassNameA(hCurWnd, className, 256);
					if (strstr(className, "GDI+ Hook Window Class"))
						return hCurWnd;
				}
			}
		}
		auto hijack() -> bool {
			window_handle = FindWindowA_Spoofed(E("MedalOverlayClass"), E("MedalOverlay")); 

			if (!window_handle)
			{
				MessageBoxA(0, skCrypt("{!} Overlay Failed. Contact Support with error {3}"), skCrypt(""), MB_ICONINFORMATION);
			}

			int WindowWidth = GetSystemMetrics(SM_CXSCREEN);
			int WindowHeight = GetSystemMetrics(SM_CYSCREEN);

		
			if (!SetWindowPos_Spoofed(window_handle, HWND_TOPMOST, 0, 0, WindowWidth, WindowHeight, SWP_SHOWWINDOW))
			{
				return false;
			}

			if (!SetLayeredWindowAttributes_Spoofed(window_handle, RGB(0, 0, 0), 255, LWA_ALPHA))
			{
				return false;
			}
			

			if (!SetWindowLongA_Spoofed(window_handle, GWL_EXSTYLE, GetWindowLong(window_handle, GWL_EXSTYLE) | WS_EX_TRANSPARENT))
			{
				return false;
			}

			MARGINS Margin = { -1 };
			if (FAILED(DwmExtendFrameIntoClientArea(window_handle, &Margin)))
			{
				return false;
			}

			ShowWindow_Spoofed(window_handle, SW_SHOW);

			UpdateWindow_Spoofed(window_handle);

			ShowWindow_Spoofed(window_handle, SW_HIDE);

			return true;
		}

		void ParticlesBG()
		{
			//ImDrawList* drawList = ImGui::GetBackgroundDrawList();			//draws like foreground does but behind the imgui stuff. Ideal


			const auto& pBackgroundDrawList = ImGui::GetWindowDrawList();

			//particle properties
			static const int numParticles = 45;
			static ImVec2 particlePositions[numParticles];
			static ImVec2 particleDistance;
			static ImVec2 particleVelocities[numParticles];

			static bool initialized = false;
			if (!initialized)
			{
				for (int i = 0; i < numParticles; ++i)
				{
					particlePositions[i] = ImVec2(
						ImGui::GetWindowPos().x + ImGui::GetWindowSize().x * static_cast<float>(rand()) / RAND_MAX,
						ImGui::GetWindowPos().y + ImGui::GetWindowSize().y * static_cast<float>(rand()) / RAND_MAX
					);



					particleVelocities[i] = ImVec2(
						static_cast<float>((rand() % 11) - 5),
						static_cast<float>((rand() % 11) - 5)
					);

				}

				initialized = true;
			}


			ImVec2 cursorPos = ImGui::GetIO().MousePos;
			for (int i = 0; i < numParticles; ++i)
			{
				//draw lines to particles
				for (int j = i + 1; j < numParticles; ++j)
				{
					float distance = std::hypotf(particlePositions[j].x - particlePositions[i].x, particlePositions[j].y - particlePositions[i].y);
					float opacity = 1.0f - (distance / 55.0f);  // opacity cahnge

					if (opacity > 0.0f)
					{
						ImU32 lineColor = ImGui::GetColorU32(ImVec4(0.7f, 0.7f, 0.7f, opacity));
						pBackgroundDrawList->AddLine(particlePositions[i], particlePositions[j], lineColor);
					}
				}

				//draw lines to cursor
				float distanceToCursor = std::hypotf(cursorPos.x - particlePositions[i].x, cursorPos.y - particlePositions[i].y);
				float opacityToCursor = 1.0f - (distanceToCursor / 52.0f);  // Adjust the divisor to control the opacity change

				if (opacityToCursor > 0.0f)
				{
					ImU32 lineColorToCursor = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, opacityToCursor));
					pBackgroundDrawList->AddLine(cursorPos, particlePositions[i], lineColorToCursor);
				}
			}

			//update and render particles
			float deltaTime = ImGui::GetIO().DeltaTime;
			for (int i = 0; i < numParticles; ++i)
			{
				particlePositions[i].x += particleVelocities[i].x * deltaTime;
				particlePositions[i].y += particleVelocities[i].y * deltaTime;

				// Stay in window
				if (particlePositions[i].x < ImGui::GetWindowPos().x)
					particlePositions[i].x = ImGui::GetWindowPos().x + ImGui::GetWindowSize().x;
				else if (particlePositions[i].x > ImGui::GetWindowPos().x + ImGui::GetWindowSize().x)
					particlePositions[i].x = ImGui::GetWindowPos().x;

				if (particlePositions[i].y < ImGui::GetWindowPos().y)
					particlePositions[i].y = ImGui::GetWindowPos().y + ImGui::GetWindowSize().y;
				else if (particlePositions[i].y > ImGui::GetWindowPos().y + ImGui::GetWindowSize().y)
					particlePositions[i].y = ImGui::GetWindowPos().y;

				ImU32 particleColour = ImGui::ColorConvertFloat4ToU32(ImVec4(0.5f, 0.f, 0.43f, 0.92f));

				//render particles behind components
				pBackgroundDrawList->AddCircleFilled(particlePositions[i], 1.5f, particleColour);
			}

		}

		void Particles()
		{
			ImVec2 screen_size = { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) };

			static ImVec2 partile_pos[100];
			static ImVec2 partile_target_pos[100];
			static float partile_speed[100];
			static float partile_radius[100];


			for (int i = 1; i < 89; i++)
			{
				if (partile_pos[i].x == 0 || partile_pos[i].y == 0)
				{
					partile_pos[i].x = rand() % (int)screen_size.x + 1;
					partile_pos[i].y = 15.f;
					partile_speed[i] = 1 + rand() % 25;
					partile_radius[i] = rand() % 4;

					partile_target_pos[i].x = rand() % (int)screen_size.x;
					partile_target_pos[i].y = screen_size.y * 2;
				}

				partile_pos[i] = ImLerp(partile_pos[i], partile_target_pos[i], ImGui::GetIO().DeltaTime * (partile_speed[i] / 90));

				if (partile_pos[i].y > screen_size.y)
				{
					partile_pos[i].x = 0;
					partile_pos[i].y = 0;
				}

				ImGui::GetWindowDrawList()->AddCircleFilled(partile_pos[i], partile_radius[i], ImColor(1.f, 1.f, 1.f, 0.97f)); //IImColor(1.f, 0.06f, 0.55f, 1.f)
			}

		}

		auto Menu() -> void {
			ImGui::SetNextWindowSize(ImVec2(560, 300));
			DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration;
			ImGui::Begin(skCrypt("ALlAH MENU"), (bool*)true, window_flags);
			{
				ImGui::StyleColorsDark();

				ImGuiIO& io = ImGui::GetIO();
				ImVec2 pos;
				ImGuiStyle& style = ImGui::GetStyle();
				ImGui::StyleColorsDark();

				style.WindowTitleAlign = ImVec2(0.5, 0.5);

				style.WindowPadding = ImVec2(0, 0);
				style.FramePadding = ImVec2(8, 8);

				style.ItemSpacing = ImVec2(8, 4);
				style.ItemInnerSpacing = ImVec2(4, 4);
				style.IndentSpacing = 0.0f;

				style.ScrollbarSize = 0.0f;

				style.ScrollbarRounding = 0.0f;
				style.GrabRounding = 16.0f;
				style.FrameRounding = 5.3f;
				style.WindowRounding = 3.0f;
				style.ChildRounding = 4.0f;

				ImVec4* colors = ImGui::GetStyle().Colors;

				colors[ImGuiCol_Text] = ImColor(190, 131, 194);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);

				colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
				colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0, 0);

				colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15);
				colors[ImGuiCol_ChildBg] = ImColor(19, 19, 19, 255);
				colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
				colors[ImGuiCol_FrameBg] = ImColor(26, 25, 26);
				colors[ImGuiCol_FrameBgHovered] = ImColor(50, 50, 50);
				colors[ImGuiCol_FrameBgActive] = ImColor(50, 50, 50);

				colors[ImGuiCol_TitleBg] = ImColor(26, 25, 26);
				colors[ImGuiCol_TitleBgActive] = ImColor(26, 25, 26);
				colors[ImGuiCol_TitleBgCollapsed] = ImColor(26, 25, 26);

				colors[ImGuiCol_ScrollbarBg] = ImColor(31, 30, 31, 255);
				colors[ImGuiCol_ScrollbarGrab] = ImColor(41, 40, 41, 255);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(31, 30, 31, 255);
				colors[ImGuiCol_ScrollbarGrabActive] = ImColor(41, 40, 41, 255);

				colors[ImGuiCol_Header] = ImColor(41, 40, 41, 255);
				colors[ImGuiCol_HeaderHovered] = ImColor(25, 25, 25, 255);
				colors[ImGuiCol_HeaderActive] = ImColor(31, 30, 31, 255);

				colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);

				colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

				colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
				colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);

				colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
				colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

				colors[ImGuiCol_Button] = ImColor(26, 25, 26);
				colors[ImGuiCol_ButtonHovered] = ImColor(40, 40, 40);
				colors[ImGuiCol_ButtonActive] = ImColor(30, 30, 30);

				static int tab = NULL;


				auto window_current = ImGui::GetWindowSize();
				auto window_pos = ImGui::GetWindowPos();

				//ImGui::GetWindowDrawList()->AddRectFilled(window_pos, { window_pos.x + window_current.x - 305, window_pos.y + 190 }, ImColor(25, 25, 25), 5.f, ImDrawCornerFlags_Top);

				ImGui::BeginGroup();
				{
					ImGui::SetCursorPos({ 0, 30 });

					ImGui::Text("", ImVec2(100, 160)); // CHANGE TO YOUR NAME
					ImGui::SameLine();
					if (Custom1337::tab2(skCrypt("Aimbot"), tab == 0)) tab = 0;
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::SameLine();
					if (Custom1337::tab2(skCrypt("Visuals"), tab == 2)) tab = 2;
					ImGui::PopStyleVar();
				}
				ImGui::EndGroup();

				ImGui::SameLine();

				static int hitboxpos = 0;

				if (tab == 0)
				{
					ImGui::BeginChild(("Aimbot"), { 450 / 2 - 20, 290 });
					{
						ImGui::BeginGroup();
						{
							ImGui::SetCursorPos({ 0, 5 });
							ImGui::Spacing();
							ImGui::SameLine();
							ImGui::Text("Aimbot");
							Custom1337::Checkbox(("Aimbot"), &globals->aimbot);
							Custom1337::Checkbox(("Prediction"), &globals->prediction);
							Custom1337::Checkbox(("Draw FOV"), &globals->normal_fov);
							Custom1337::Checkbox(("Visible Check"), &globals->DoVisibleCheck);
						
						}
						ImGui::EndGroup();
					}
					ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild(("Settings"), { 450 / 2 - 20, 290 });
					{
						ImGui::SetCursorPos({ 0, 5 });
						ImGui::BeginGroup();
						{
							ImGui::Spacing();
							ImGui::SameLine();
							ImGui::Text("Settings");
							ImGui::SliderInt(("Smoothing"), &globals->smooth, 2, 25);
							ImGui::SliderInt(("FOV Size"), &globals->field_of_view, 10, 200);
							HotkeyButton(globals->aimbot_key, ChangeKey, keystatus);
							ImGui::Spacing();

							static const char* hitboxOptions[] = { ("Head"), ("Chest") };
							ImGui::Combo(("Hitbox"), &hitboxpos, hitboxOptions, IM_ARRAYSIZE(hitboxOptions));

							if (hitboxpos == 0) {
								globals->head = true;
								globals->ChestBone = false;
							}
							if (hitboxpos == 1) {
								globals->head = false;
								globals->ChestBone = false;
							}
							if (hitboxpos == 2) {
								globals->head = false;
								globals->ChestBone = true;
							}
						}
						ImGui::EndGroup();
					}
					ImGui::EndChild();
				}

				ImGui::SameLine();

				if (tab == 2)
				{
					ImGui::BeginChild(("Visuals"), { 450 / 2 - 20, 290 });
					{
						ImGui::BeginGroup();
						{
							ImGui::SetCursorPos({ 0, 5 });
							ImGui::Spacing();
							ImGui::SameLine();
							ImGui::Text("Visuals");
							Custom1337::Checkbox(("Boxes"), &globals->bounding_box);

							Custom1337::Checkbox(("Snaplines"), &globals->snaplin);

							Custom1337::Checkbox(("Distance"), &globals->distance);

							Custom1337::Checkbox(("Name Esp"), &globals->playername);

						}
						ImGui::EndGroup();
					}
					ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild(("Settings"), { 450 / 2 - 20, 290 });
					{
						ImGui::SetCursorPos({ 0, 5 });
						ImGui::BeginGroup();
						{
							ImGui::Spacing();
							ImGui::SameLine();
							ImGui::Text("Settings");
							Custom1337::Checkbox(("Outlines"), &globals->outlinebox);
							Custom1337::Checkbox(("Text Outline"), &globals->text_outline);
							ImGui::SliderFloat(("Box Thickness"), &globals->box_thick, 1, 4);
							ImGui::ColorEdit3(("Box Color Vis"), PlayerColor::BoxVisible);
							ImGui::ColorEdit3(("Box Color Inv"), PlayerColor::BoxNotVisible);
							
						}
						ImGui::EndGroup();
					}
					ImGui::EndChild();
				}
			}
			ImGui::End();

			ImGui::Render();
		}



		auto Draw() -> void {			
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.f);

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
			float target_dist = FLT_MAX;
			uintptr_t target_entity = 0;

			if (GetAsyncKeyState_Spoofed(VK_INSERT) & 1)
			{
				globals->render_menu = !globals->render_menu;
				globals->crsm = !globals->crsm;
			}

			if (globals->render_field_of_view) {
				if (globals->normal_fov)
				{
					// Small anti paster thing LOL
					ImGui::GetForegroundDrawList()->AddCircle(ImVec2(globals->width / 2 , globals->height / 2 ), globals->field_of_view, ImColor(255, 255, 255), 64, 1);



				}
			}

			Game->ActorLoop();

			ImColor Watermarko = ImColor(1.f, 1.f, 1.f);

			if (globals->render_menu)
			{
				Watermarko = ImColor(0.2f, 0.62f, 0.04f, 0.89f);
				Menu();
			}

			float fps = ImGui::GetIO().Framerate;


			ImGui::GetBackgroundDrawList()->AddText(ImVec2(5, 5), Watermarko, (watermark + "| fps: " + std::to_string(static_cast<int>(fps))).c_str());

			ImGui::Render();
			const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
			d3d_device_ctx->OMSetRenderTargets(1, &d3d_render_target, nullptr);
			d3d_device_ctx->ClearRenderTargetView(d3d_render_target, clear_color_with_alpha);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			d3d_swap_chain->Present(1, 0);
		}
	};
} static render::c_render* Render = new render::c_render();