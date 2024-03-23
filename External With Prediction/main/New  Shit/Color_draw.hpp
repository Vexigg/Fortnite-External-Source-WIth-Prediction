//#include <minwindef.h>
//#include "../dependencies/gui/imgui.h"
//#include <sysinfoapi.h>
//#include <corecrt_math.h>
//#include <cstdint>
//#include "../includes/globals.hpp"

float cross_r = 255;
float cross_g = 0;
bool GameUI_color = true;
float cross_b = 0;
float cross_a = 255;

bool color_random = true;
float crosshair_r = 255;
float crosshair_g = 0;
float crosshair_b = 0;
float crosshair_a = 255;
bool color_crosshair = true;
float title_r = 255;
float title_g = 0;
float title_b = 0;
float title_a = 255;
bool title_color = true;
float box_r = 255;
float box_g = 0;
float box_b = 0;
float box_a = 255;


void ColorChange()
{
	if (color_random)
	{
		static float Color[3];
		static DWORD Tickcount = 0;
		static DWORD Tickcheck = 0;
		ImGui::ColorConvertRGBtoHSV(cross_r, cross_g, cross_b, Color[0], Color[1], Color[2]);
		if (GetTickCount64() - Tickcount >= 1)
		{
			if (Tickcheck != Tickcount)
			{
				Color[0] += 0.001f * -4;
				Tickcheck = Tickcount;
			}
			Tickcount = GetTickCount64();
		}
		if (Color[0] < 0.0f) Color[0] += 1.0f;
		ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], cross_r, cross_g, cross_b);
	}
}

void ColorChangeCrosshair()
{
	if (color_crosshair)
	{
		static float Color[3];
		static DWORD Tickcount = 0;
		static DWORD Tickcheck = 0;
		ImGui::ColorConvertRGBtoHSV(crosshair_r, crosshair_g, crosshair_b, Color[0], Color[1], Color[2]);
		if (GetTickCount64() - Tickcount >= 1)
		{
			if (Tickcheck != Tickcount)
			{
				Color[0] += 0.001f * -4;
				Tickcheck = Tickcount;
			}
			Tickcount = GetTickCount64();
		}
		if (Color[0] < 0.0f) Color[0] += 1.0f;
		ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], crosshair_r, crosshair_g, crosshair_b);
	}
}

void TitleRainbow()
{
	if (title_color)
	{
		static float Color[3];
		static DWORD Tickcount = 0;
		static DWORD Tickcheck = 0;
		ImGui::ColorConvertRGBtoHSV(title_r, title_g, title_b, Color[0], Color[1], Color[2]);
		if (GetTickCount64() - Tickcount >= 1)
		{
			if (Tickcheck != Tickcount)
			{
				Color[0] += 0.001f * -4;
				Tickcheck = Tickcount;
			}
			Tickcount = GetTickCount64();
		}
		if (Color[0] < 0.0f) Color[0] += 1.0f;
		ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], title_r, title_g, title_b);
	}
}

void BoxRainbow()
{
	if (globals->box_color)
	{
		static float Color[3];
		static DWORD Tickcount = 0;
		static DWORD Tickcheck = 0;
		ImGui::ColorConvertRGBtoHSV(box_r, box_g, box_b, Color[0], Color[1], Color[2]);
		if (GetTickCount64() - Tickcount >= 1)
		{
			if (Tickcheck != Tickcount)
			{
				Color[0] += 0.001f * -4;
				Tickcheck = Tickcount;
			}
			Tickcount = GetTickCount64();
		}
		if (Color[0] < 0.0f) Color[0] += 1.0f;
		ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], box_r, box_g, box_b);
	}
}
void HSVtoRGB(float h, float s, float v, float& r, float& g, float& b)
{
	if (s == 0.0f)
	{
		// Si la saturation est nulle, la couleur est un gris nuancé par la valeur (luminosité)
		r = v;
		g = v;
		b = v;
	}
	else
	{
		h *= 6.0f; // Convertir la teinte en une valeur entre 0 et 6

		int i = static_cast<int>(floor(h));
		float f = h - i;

		float p = v * (1.0f - s);
		float q = v * (1.0f - s * f);
		float t = v * (1.0f - s * (1.0f - f));

		switch (i)
		{
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		case 5:
		default:
			r = v;
			g = p;
			b = q;
			break;
		}
	}
}
float GameUI_r = 3.0f;
float GameUI_g = 0.0f;
float GameUI_b = 0.0f;



// Conversion en entiers avec échelle
int scaledGameUI_r = static_cast<int>(GameUI_r * 1000);
int scaledGameUI_g = static_cast<int>(GameUI_g * 1000);
int scaledGameUI_b = static_cast<int>(GameUI_b * 1000);
void GameRainbow()
{
	if (GameUI_color)
	{
		static float Color[3];
		static DWORD Tickcount = 0;
		static DWORD Tickcheck = 0;

		// Conversion HSV vers RGB
		ImGui::ColorConvertRGBtoHSV(GameUI_r, GameUI_g, GameUI_b, Color[0], Color[1], Color[2]);

		if (GetTickCount64() - Tickcount >= 1)
		{
			if (Tickcheck != Tickcount)
			{
				Color[0] += 0.001f * -4;
				Tickcheck = Tickcount;
			}
			Tickcount = GetTickCount64();
		}
		if (Color[0] < 0.0f) Color[0] += 1.0f;

		// Conversion RGB vers HSV
		ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], GameUI_r, GameUI_g, GameUI_b);
	}
}



constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b)
	{
		return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
	};

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

class Color
{
public:
	RGBA red = { 255,0,0,255 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 144,0,255,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };
	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 0, 0, 0, 255 };
	RGBA gray = { 128,128,128,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 100,000, 000, 000 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255,0,255,200 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,200 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };

	RGBA glassblack = { 0, 0, 0, 160 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };

	RGBA filled = { 0, 0, 0, 150 };

	RGBA Plum = { 221,160,221,160 };

	RGBA VisibleColor = { 255 / 255, 0, 0 };
	RGBA InvisibleColor = { 0, 255 / 255, 0 };

	RGBA rainbow() {

		static float x = 0, y = 0;
		static float r = 0, g = 0, b = 0;

		if (y >= 0.0f && y < 255.0f) {
			r = 255.0f;
			g = 0.0f;
			b = x;
		}
		else if (y >= 255.0f && y < 510.0f) {
			r = 255.0f - x;
			g = 0.0f;
			b = 255.0f;
		}
		else if (y >= 510.0f && y < 765.0f) {
			r = 0.0f;
			g = x;
			b = 255.0f;
		}
		else if (y >= 765.0f && y < 1020.0f) {
			r = 0.0f;
			g = 255.0f;
			b = 255.0f - x;
		}
		else if (y >= 1020.0f && y < 1275.0f) {
			r = x;
			g = 255.0f;
			b = 0.0f;
		}
		else if (y >= 1275.0f && y < 1530.0f) {
			r = 255.0f;
			g = 255.0f - x;
			b = 0.0f;
		}

		float rainbow_speed = 0.25f;

		x += rainbow_speed; //increase this value to switch colors faster
		if (x >= 255.0f)
			x = 0.0f;

		y += rainbow_speed; //increase this value to switch colors faster
		if (y > 1530.0f)
			y = 0.0f;


		return RGBA{ (DWORD)r, (DWORD)g, (DWORD)b, 255 };
	}


};
static Color Col;
