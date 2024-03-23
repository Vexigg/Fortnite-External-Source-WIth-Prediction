#include <Windows.h>
#include <mutex>
#include <memory>

namespace PlayerColor {
	float BoxVisible[3] = { 87 / 255.0f, 173 / 255.0f, 17 / 255.0f };
	float BoxNotVisible[3] = { 173 / 255.0f, 17 / 255.0f, 17 / 255.0f };
	float targetcol[4] = { 1.f, 0, 0, 1.0f };
	
	float accentcolor[4] = { 1.f, 1.f, 1.f, 1.0f };

	float SnaplineVisible[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float SnaplineNotVisible[4] = { 1.f, 0.0f, 0.0f, 1.0f };

	float TopTextVisible[4] = { 1.f, 1.0f, 1.0f, 1.0f };
	float TopTextNotVisible[4] = { 1.f, 1.0f, 1.0f, 1.0f };

	float BottomTextVisible[4] = { 1.f, 1.0f, 1.0f, 1.0f };
	float BottomTextNotVisible[4] = { 1.f, 1.0f, 1.0f, 1.0f };
}

class c_globals {
public:
	int width, height;
	bool render_menu = 0;
	bool crsm = 0;
	HWND hwnd = 0;

	bool bounding_box = 0;

	bool outlinebox = 1;

	bool distance = 0;
	bool outline = 1;
	bool text_outline = 0;

	float font_size = 16;
	int add = 3;
	bool head = 0;
	int Smoothing = 1;
	bool aimbot = 1;

	bool HeadBone = 1;
	bool target_line = 0;
	bool target_text = 0;
	bool player_info = 0;

	bool ChestBone = 0;
	bool chests = 0;
	bool playername = 0;
	bool weaponesp = 0;
	bool weaponrar = 0;


	bool snaplin = 0;

	bool vehicle = 0;
	bool Lamma = 0;
	int max_distance = 100;
	int max_distance1 = 100;
	int max_distance2 = 250;
	int max_distance3 = 500;
	int max_distance4 = 100;

	int smooth = 3.0f;
	int field_of_view = 100.0f;
	bool render_field_of_view = 1;
	bool rendercrosshair = 0;
	bool rendercrosshairefk = 0;


	bool normal_fov = 1;
	bool weapon_cfg = 1;
	int aimbot_bone = 0;
	bool prediction = 1;

	bool color_crosshair = 1;
	bool box_color = 1;
	
	int aimbot_key = VK_LMENU;
	//int triggerbot_key;
	bool showSelectKeyModal;
	bool DoVisibleCheck = 1;
	bool keyselected;
	bool triggerbot = 1;
	int custom_delay = 1;
	int maximum_distance = 20;
	bool has_clicked;
	std::chrono::steady_clock::time_point tb_begin;
	std::chrono::steady_clock::time_point tb_end;
	int tb_time_since;

	int Linethick = 2.f;

	float box_thick = 1.f, skeleton_thick = 2.f;
}; static c_globals* globals = new c_globals();