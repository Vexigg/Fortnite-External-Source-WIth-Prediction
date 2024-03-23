#pragma once

class entity {
public:
	uintptr_t
		entity,
		actor,
		skeletal_mesh,
		root_component,
		player_state;
	int
		team_index;
};
std::vector<entity> entity_list;
std::vector<entity> temporary_entity_list;

struct WeaponInformation
{
	int32_t ammo_count;
	int32_t max_ammo;

	BYTE tier;
	std::string weapon_name;
	std::string buildplan;

};
std::string LocalPlayerWeapon;


WeaponInformation WeaponInfo;


class item {
public:
	uintptr_t
		Actor;

	std::string
		Name;
	bool
		isVehicle,
		isChest,
		isPickup,
		isAmmoBox;
	float
		distance;


};

int enemyID = 0;
int visennemy = 0;
int InFovEnemy = 0;
std::vector<item> item_pawns;


inline void Ud_Draw_line(FVector2d ScreenPositionA, FVector2d ScreenPositionB, float Thickness, ImColor RenderColor) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.x, ScreenPositionA.y), ImVec2(ScreenPositionB.x, ScreenPositionB.y), RenderColor, Thickness);
}
inline void Ud_Draw_line1(FVector2d ScreenPositionA, FVector2d ScreenPositionB, float Thickness, ImColor RenderColor) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.x, ScreenPositionA.y), ImVec2(ScreenPositionB.x + 1, ScreenPositionB.y + 1), RenderColor, Thickness);
}

inline std::wstring MBytesToWString(const char* lpcszString)
{


	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
inline std::string WStringToUTF8(const wchar_t* lpwcszWString)
{


	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}









inline float GetDistLength(Vector3 from, Vector3 to)
{
	return double(sqrtf(powf(to.x - from.x, 2.0) + powf(to.y - from.y, 2.0) + powf(to.z - from.z, 2.0)));
}


Vector3 AimbotPrediction(float bulletVelocity, float bulletGravity, float targetDistance, Vector3 targetPosition, Vector3 targetVelocity)
{
	Vector3 recalculated = targetPosition;
	float gravity = fabs(bulletGravity);
	float time = targetDistance / fabs(bulletVelocity);
	float bulletDrop = (gravity / 250) * time * time;
	recalculated.z += bulletDrop * 120;
	recalculated.x += time * (targetVelocity.x);
	recalculated.y += time * (targetVelocity.y);
	recalculated.z += time * (targetVelocity.z);
	return recalculated;
}




inline void DrawString(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImColor(color), text.c_str());
}

FVector target_prediction(FVector TargetPosition, FVector ComponentVelocity, float player_distance, float ProjectileSpeed)
{
	float gravity = abs(-336); // Gravity (Probably other ways to get this but I set it as a constant value)
	float time = player_distance / abs(ProjectileSpeed);
	float bulletDrop = (gravity / 250) * time* time;
	return FVector(TargetPosition.x += time * (ComponentVelocity.x), TargetPosition.y += time * (ComponentVelocity.y), TargetPosition.z += time * (ComponentVelocity.z));
}

auto GetNameByIndex(uintptr_t player_state, bool inlobby) -> std::string
{

	int pNameLength;
	_WORD* pNameBufferPointer;
	int i;
	char v25;
	int v26;
	int v29;

	char16_t* pNameBuffer;

	uintptr_t pNameStructure = read < uintptr_t >(player_state + 0xAF0); //pNameStructure
	if (is_valid(pNameStructure)) {
		pNameLength = read <int>(pNameStructure + 0x10);
		if (pNameLength <= 0)
			return "BOT";

		pNameBuffer = new char16_t[pNameLength];
		uintptr_t pNameEncryptedBuffer = read <uintptr_t>(pNameStructure + 0x8);
		if (is_valid(pNameEncryptedBuffer)) {
			read_array(pNameEncryptedBuffer, pNameBuffer, pNameLength);

			v25 = pNameLength - 1;
			v26 = 0;
			pNameBufferPointer = (_WORD*)pNameBuffer;

			for (i = (v25) & 3;; *pNameBufferPointer++ += i & 7) {
				v29 = pNameLength - 1;
				if (!(_DWORD)pNameLength)
					v29 = 0;

				if (v26 >= v29)
					break;

				i += 3;
				++v26;
			}

			std::u16string temp_wstring(pNameBuffer);
			delete[] pNameBuffer;
			return std::string(temp_wstring.begin(), temp_wstring.end());
		}
	}
}
std::string string_To_UTF8(const std::string& str)
{
	HKSSPFF;
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

void DrawNewTextCustomWithOutline(int x, int y, int R, int G, int B, int A, const char* str)
{
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	float outlineThickness = 1.5f; // Adjust the outline thickness as needed

	// Draw the text with black outline
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), 18.0f, ImVec2(x - outlineThickness, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, A / 255.0f)), utf_8_2.c_str());
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), 18.0f, ImVec2(x + outlineThickness, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, A / 255.0f)), utf_8_2.c_str());
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), 18.0f, ImVec2(x, y - outlineThickness), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, A / 255.0f)), utf_8_2.c_str());
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), 18.0f, ImVec2(x, y + outlineThickness), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, A / 255.0f)), utf_8_2.c_str());

	// Draw the main text with the specified color
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), 18.0f, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(R / 255.0f, G / 255.0f, B / 255.0f, A / 255.0f)), utf_8_2.c_str());
}


uintptr_t RootComponent(uintptr_t actor)
{

	return read<uintptr_t>(actor + 0x198);
}
FVector GetLocation(uintptr_t actor)
{

	return read<FVector>(RootComponent(actor) + 0x128);
}
char* wchar_to_char(const wchar_t* pwchar)
{
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);

	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}


enum GAME_INFORMATION : int {
	GAME_THREAD_FAILED = 0,
	GAME_SETUP_SUCCESSFUL = 1
};
int HeldWeaponType;

enum EFortWeaponType : int
{
	Rifle = 0,
	Shotgun = 1,
	Smg = 2,
	Sniper = 3
};
static int current_item = 0;
ImColor visible_color;
inline int headfunction = 0;
inline int bodyfunction = 0;
inline int handsfunction = 0;
inline int legsfunction = 0;
namespace game {
	class c_game {
	public:

		auto Setup() -> GAME_INFORMATION {

			std::thread(game::c_game::CacheData).detach();


		
			///std::thread(game::c_game::CacheLevels).detach();
			


			return GAME_INFORMATION::GAME_SETUP_SUCCESSFUL;
		}
		auto isVisible(uintptr_t test) -> bool
		{
			float fLastSubmitTime = read<float>(offset::skeletal_mesh + offset::fLastSubmitTime);
			float fLastRenderTimeOnScreen = read<float>(offset::skeletal_mesh + offset::fLastRenderTimeOnScreen);
			const float fVisionTick = 0.06f;
			bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;
			return bVisible;
		}
		double Distance2(const FVector& v2)
		{
			double x;
			double y;
			double z;

			double dx = v2.x - x;
			double dy = v2.y - y;
			double dz = v2.z - z;

			return sqrt(dx * dx + dy * dy + dz * dz);
		}
		
		float WorldGravityZ;

		FVector LocationPredict(FVector Target, FVector Velocityy, float GetProjectileSpeed, float ProjectileGravity, float DistanceToTarget)
		{
			float H_time = DistanceToTarget / GetProjectileSpeed;
			float V_time = DistanceToTarget / GetProjectileSpeed;

			Target.x += Velocityy.x * H_time;
			Target.y += Velocityy.y * H_time;
			Target.z += Velocityy.z * H_time +
			abs(WorldGravityZ * ProjectileGravity) * 0.5f * (V_time * V_time);

			return Target;
		}
		

		FVector CalculatePrediction(FVector AimedBone, FVector Velocity, float Distance, float BulletSpeed)
		{
			BulletSpeed *= 100;
			float Gravity = 9.81f * 100.0f;
			float Time = Distance / BulletSpeed;

			FVector TargetPos = AimedBone + (Velocity * Time);

			return TargetPos;
		}

		FVector PredictLocaKurwa(FVector target, FVector targetVelocity, float projectileSpeed, float projectileGravityScale, float distance)
		{
			float horizontalTime = distance / projectileSpeed;
			float verticalTime = distance / projectileSpeed;

			target.x += targetVelocity.x * horizontalTime;
			target.y += targetVelocity.y * horizontalTime;
			target.z += targetVelocity.z * verticalTime + abs(-980 * projectileGravityScale) * 0.5f * (verticalTime * verticalTime);
				//abs(WorldGravityZ * projectileGravityScale) * 0.5f * (verticalTime * verticalTime);

			return target;
		}

		void DrawBox(int x, int y, int w, int h, ImColor color, int thickness) {
			ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();

			Drawlist->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.0f, 0, thickness);
		}

		void DrawCorneredBox(int x, int y, int w, int h, ImColor color, int thickness) {

			ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();

			float line_w = (w / 8);
			float line_h = (h / 8);
			Drawlist->AddLine(ImVec2(x, y), ImVec2(x, y + line_h), color, thickness);
			Drawlist->AddLine(ImVec2(x, y), ImVec2(x + line_w, y), color, thickness);
			Drawlist->AddLine(ImVec2(x + w - line_w, y), ImVec2(x + w, y), color, thickness);
			Drawlist->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + line_h), color, thickness);
			Drawlist->AddLine(ImVec2(x, y + h - line_h), ImVec2(x, y + h), color, thickness);
			Drawlist->AddLine(ImVec2(x, y + h), ImVec2(x + line_w, y + h), color, thickness);
			Drawlist->AddLine(ImVec2(x + w - line_w, y + h), ImVec2(x + w, y + h), color, thickness);
			Drawlist->AddLine(ImVec2(x + w, y + h - line_h), ImVec2(x + w, y + h), color, thickness);
		}

		static auto CacheData() -> void {

			for (;; ) {

				temporary_entity_list.clear();

				pointer->uworld = read<uintptr_t>(base_address + offset::uworld);

				pointer->game_instance = read<uintptr_t>(pointer->uworld + offset::game_instance);

				pointer->levels = read<uintptr_t>(pointer->levels + 0x170);

				pointer->game_state = read<uintptr_t>(pointer->uworld + offset::game_state);

				pointer->local_player = read<uintptr_t>(read<uintptr_t>(pointer->game_instance + offset::local_player));

				pointer->player_controller = read<uintptr_t>(pointer->local_player + offset::player_controller);

				pointer->acknowledged_pawn = read<uintptr_t>(pointer->player_controller + offset::acknowledged_pawn);

				pointer->current_weapon = read<uintptr_t>(pointer->acknowledged_pawn + offset::current_weapon);
				pointer->skeletal_mesh = read<uintptr_t>(pointer->acknowledged_pawn + offset::skeletal_mesh);

				pointer->player_state = read<uintptr_t>(pointer->acknowledged_pawn + offset::player_state);

				pointer->root_component = read<uintptr_t>(pointer->acknowledged_pawn + offset::root_component);

				pointer->team_index = read<int>(pointer->player_state + offset::team_index);
				
				pointer->relative_location = read<FVector>(pointer->root_component + offset::relative_location);

				pointer->player_array = read<uintptr_t>(pointer->game_state + offset::player_array);

				pointer->player_array_size = read<int>(pointer->game_state + (offset::player_array + sizeof(uintptr_t)));



				for (int i = 0; i < pointer->player_array_size; ++i) {
					auto player_state = read<uintptr_t>(pointer->player_array + (i * sizeof(uintptr_t)));
					auto current_actor = read<uintptr_t>(player_state + offset::pawn_private);
					
					if (current_actor == pointer->acknowledged_pawn) continue;
					auto skeletalmesh = read<uintptr_t>(current_actor + offset::skeletal_mesh);
					if (!skeletalmesh) continue;

					auto base_bone = Utilities->GetBoneLocation(skeletalmesh, bone::HumanBase);
					if (base_bone.x == 0 && base_bone.y == 0 && base_bone.z == 0) continue;

					if (!Utilities->InScreen(Utilities->WorldToScreen(Utilities->GetBoneLocation(skeletalmesh, bone::HumanPelvis)))) continue;

					auto is_despawning = (read<char>(current_actor + 0x758) >> 3);

					if (is_despawning) continue;

					if (pointer->acknowledged_pawn)
					{
						auto team_index = read<int>(player_state + offset::team_index);
						if (pointer->team_index == team_index) continue;
					}

					entity cached_actors{};
					cached_actors.actor = current_actor;
					cached_actors.skeletal_mesh = read<uintptr_t>(current_actor + offset::skeletal_mesh);
					cached_actors.root_component = read<uintptr_t>(current_actor + offset::root_component);
					cached_actors.player_state = read<uintptr_t>(current_actor + offset::player_state);
					cached_actors.team_index = read<int>(cached_actors.player_state + offset::team_index);
					temporary_entity_list.push_back(cached_actors);				
				}
				entity_list.clear();
				entity_list = temporary_entity_list;

				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}

		}


		auto ActorLoop() -> void {



			target_dist = FLT_MAX;
			target_entity = NULL;
			desync_target_entity = NULL;

			Utilities->UpdateCamera();

			if (pointer->acknowledged_pawn) {

				uint64_t player_weapon = read<uint64_t>(pointer->acknowledged_pawn + 0xa20); // 	struct AFortWeapon* CurrentWeapon;

				if (is_valid(player_weapon)) {

					uint64_t weapon_data = read<uint64_t>(player_weapon + 0x4a8);	//struct UFortWeaponItemDefinition* WeaponData;
					if (is_valid(weapon_data)) {

						uint64_t ftext_ptr = read<uint64_t>(weapon_data + 0x90);

						if (is_valid(ftext_ptr)) {
							uint64_t ftext_data = read<uint64_t>(ftext_ptr + 0x28);
							int ftext_length = read<int>(ftext_ptr + 0x30);
							if (ftext_length > 0 && ftext_length < 50) {
								wchar_t* ftext_buf = new wchar_t[ftext_length];

								mem::read_physical(reinterpret_cast<void*>(ftext_data), reinterpret_cast<uint8_t*>(ftext_buf), ftext_length * sizeof(wchar_t));
								std::wstring wstr_buf(ftext_buf);

								wchar_t* WeaponName = ftext_buf;

								delete[] ftext_buf;							
							}
						}								
					}
				}
			}

			for (auto& cached_entity : entity_list) {

				auto root_location = Utilities->GetBoneLocation(cached_entity.skeletal_mesh, bone::HumanBase);
				auto root_screen = Utilities->WorldToScreen(root_location);
				auto head_location = Utilities->GetBoneLocation(cached_entity.skeletal_mesh, bone::HumanHead);
				auto head_screen = Utilities->WorldToScreen(Utilities->GetBoneLocation(cached_entity.skeletal_mesh, bone::HumanHead));
				auto head_screen1 = Utilities->GetBoneLocation(cached_entity.skeletal_mesh, bone::HumanHead);

				FVector2d head_box = Utilities->WorldToScreen(FVector(head_screen1.x, head_screen1.y, head_screen1.z + 15));
				FVector2d head_2d = Utilities->WorldToScreen(FVector(head_location.x, head_location.y, head_location.z + 20));

				float box_height = abs(head_screen.y - root_screen.y);
				float box_width = box_height * 0.50f;
				float distance = camera::location.Distance(root_location) / 100;

				if (globals->aimbot) {
					auto dx = head_screen.x - (globals->width / 2);
					auto dy = head_screen.y - (globals->height / 2);
					auto dist = sqrtf(dx * dx + dy * dy);

					if (dist < globals->field_of_view && dist < target_dist) {
						target_dist = dist;
						target_entity = cached_entity.actor;
					}
				}

				enemyID += 1;

				ImColor visible_color_box;
				ImColor visible_color_skel;
				ImColor visible_color_Snapline;
				ImColor visible_color_Text;
				ImColor visible_color_Text1;


				bool inlobby;

				if (pointer->acknowledged_pawn == NULL)
				{
					inlobby = true;
				}
				else
				{
					inlobby = false;
				}


				if (distance <= 15)
				{
					InFovEnemy += 1;
				}

				if (globals->DoVisibleCheck) {
					if (Utilities->IsVisible(cached_entity.skeletal_mesh)) {
						visennemy += 1;
						visible_color_box = ImVec4(PlayerColor::BoxVisible[0], PlayerColor::BoxVisible[1], PlayerColor::BoxVisible[2], 1.0f);
						visible_color_Snapline = ImVec4(PlayerColor::SnaplineVisible[0], PlayerColor::SnaplineVisible[1], PlayerColor::SnaplineVisible[2], 1.0f);
						visible_color_Text = ImVec4(PlayerColor::TopTextVisible[0], PlayerColor::TopTextVisible[1], PlayerColor::TopTextVisible[2], 1.0f);
						visible_color_Text1 = ImVec4(PlayerColor::BottomTextVisible[0], PlayerColor::BottomTextVisible[1], PlayerColor::BottomTextVisible[2], 1.0f);
					}
					else {
						visible_color_box = ImVec4(PlayerColor::BoxNotVisible[0], PlayerColor::BoxNotVisible[1], PlayerColor::BoxNotVisible[2], 1.0f);
						visible_color_Snapline = ImVec4(PlayerColor::SnaplineNotVisible[0], PlayerColor::SnaplineNotVisible[1], PlayerColor::SnaplineNotVisible[2], 1.0f);
						visible_color_Text = ImVec4(PlayerColor::TopTextNotVisible[0], PlayerColor::TopTextNotVisible[1], PlayerColor::TopTextNotVisible[2], 1.0f);
						visible_color_Text1 = ImVec4(PlayerColor::BottomTextNotVisible[0], PlayerColor::BottomTextNotVisible[1], PlayerColor::BottomTextNotVisible[2], 1.0f);
					}
				}

				if (globals->playername) {

					std::string username_str = GetNameByIndex(cached_entity.player_state, inlobby);
					ImVec2 text_size = ImGui::CalcTextSize(username_str.c_str());
					DrawString(globals->font_size, head_box.x - (text_size.x / 2), head_box.y + -20, visible_color_Text1, false, true, username_str.c_str());

				}


				if (globals->weaponesp)
				{
					if (pointer->acknowledged_pawn)
					{

						WeaponInformation held_weapon{ };

						uint64_t player_weapon = read<uint64_t>(cached_entity.entity + 0xa20); // updated CurrentWeapons 

						if (is_valid(player_weapon)) {
							held_weapon.ammo_count = read <int32_t>(player_weapon + 0xe54);  // updated 

							uint64_t weapon_data = read <uint64_t>(player_weapon + 0x4f0);  //WeaponData 

							if (is_valid(weapon_data)) {
								held_weapon.tier = read <BYTE>(weapon_data + 0x13b); // updated

								uint64_t ftext_ptr = read <uint64_t>(weapon_data + 0x38); // okay updated

								if (is_valid(ftext_ptr)) {
									uint64_t ftext_data = read <uint64_t>(ftext_ptr + 0x28); //dunno loler
									int ftext_length = read <int>(ftext_ptr + 0x30); //okay updated
									if (ftext_length > 0 && ftext_length < 50) {
										wchar_t* ftext_buf = new wchar_t[ftext_length];

										mem::read1(ftext_data, ftext_buf, ftext_length * sizeof(wchar_t));
										std::wstring wstr_buf(ftext_buf);
										held_weapon.weapon_name = std::string(wstr_buf.begin(), wstr_buf.end());
										delete[] ftext_buf;
									}
								}

							}

							WeaponInfo = held_weapon;

							std::string final = ("") + WeaponInfo.weapon_name + ("");

							ImVec2 TextSize = ImGui::CalcTextSize(final.c_str());

							ImVec2 text_size = ImGui::CalcTextSize(final.c_str());
							int add;
							if (globals->distance)
							{
								add = 25;
							}
							else
							{
								add = 5;
							}

							if (globals->weaponrar)
							{
								if (WeaponInfo.tier == 0)
								{
									if (strstr(WeaponInfo.weapon_name.c_str(), E("Pickaxe")) != nullptr)
									{
										DrawString(15, (root_screen.x) - (TextSize.x / 2), (root_screen.y + add), ImColor(255, 255, 255), false, true, final.c_str());
									}
									else
									{
										std::string fina1l = ("Building Plan");
										ImVec2 TextSiz1e = ImGui::CalcTextSize(fina1l.c_str());
										DrawString(15, (root_screen.x) - (TextSiz1e.x / 2), (root_screen.y + add), ImColor(255, 255, 255), false, true, fina1l.c_str());
									}

								}
								if (WeaponInfo.tier == 1)
								{
									DrawString(15, (root_screen.x) - (TextSize.x / 2), (root_screen.y + add), ImColor(170, 165, 169), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 2)
								{
									DrawString(15, (root_screen.x) - (TextSize.x / 2), (root_screen.y + add), ImColor(30, 255, 0), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 3)
								{
									DrawString(15, (root_screen.x) - (TextSize.x / 2), (root_screen.y + add), ImColor(0, 112, 221), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 4)
								{
									DrawString(15, (root_screen.x) - (TextSize.x / 2), (root_screen.y + add), ImColor(163, 53, 238), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 5)
								{
									DrawString(15, (root_screen.x) - (TextSize.x / 2), (root_screen.y + add), ImColor(255, 128, 0), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 6)
								{
									DrawString(15, (root_screen.x) - (TextSize.x / 2), (root_screen.y + add), ImColor(255, 255, 0), false, true, final.c_str());

								}
							}
							else
							{
								if (WeaponInfo.tier == 0)
								{
									if (strstr(WeaponInfo.weapon_name.c_str(), E("Pickaxe")) != nullptr)
									{
										DrawString(15, (root_screen.x) - (TextSize.x / 2), (root_screen.y + add), visible_color_Text1, false, true, final.c_str());
									}
									else
									{
										std::string fina1l = ("Building Plan");
										ImVec2 TextSiz1e = ImGui::CalcTextSize(fina1l.c_str());
										DrawString(15, (root_screen.x) - (TextSiz1e.x / 2), (root_screen.y + add), visible_color_Text1, false, true, fina1l.c_str());
									}
								}
								else
								{
									DrawString(14, root_screen.x - (text_size.x / 2), root_screen.y + 20, visible_color_Text1, false, true, final.c_str());
								}
							}
						}

					}
				}


				if (globals->bounding_box) {
					auto root_box1 = Utilities->WorldToScreen(Utilities->GetBoneLocation(cached_entity.skeletal_mesh, 0));

					float CornerHeight = abs(head_box.y - root_box1.y);
					float CornerWidth = box_height * 0.50f;
					if (globals->outlinebox)
					{
						DrawBox(head_box.x - (CornerWidth / 2), head_box.y, CornerWidth, CornerHeight, ImColor(0, 0, 0), globals->box_thick + 3.5);
					}
					DrawBox(head_box.x - (CornerWidth / 2), head_box.y, CornerWidth, CornerHeight, visible_color_box, globals->box_thick);
				}
				ImDrawList* draw_list = ImGui::GetForegroundDrawList();

				if (globals->snaplin) {
					draw_list->AddLine(ImVec2(globals->width / 2, 0), ImVec2(head_2d.x, head_2d.y), visible_color_Snapline, globals->Linethick);
				}

				int CloseRangeDistanceID = 0;
				float CloseRangeDistance = 50.f;
				int enemyID = 0;
				int enemyIDvis = 0;	

				if (enemyID != 0)
					enemyID = 0;

				if (CloseRangeDistanceID != 0)
					CloseRangeDistanceID = 0;

				if (enemyIDvis != 0)
					enemyIDvis = 0;



				if (globals->distance) {
					std::string distance_string = "" + std::to_string((int)distance) + "m";
					ImVec2 text_size = ImGui::CalcTextSize(distance_string.c_str());

					if (globals->text_outline)
					{
						DrawString(globals->font_size, root_screen.x - (text_size.x / 2), root_screen.y + 5, visible_color_Text1, false, true, distance_string.c_str());

					}
					else
					{
						DrawString(globals->font_size, root_screen.x - (text_size.x / 2), root_screen.y + 5, visible_color_Text1, false, false, distance_string.c_str());
					}
				}

				if (enemyID != 0)
					enemyID = 0;

				if (InFovEnemy != 0)
					InFovEnemy = 0;

				if (visennemy != 0)
					visennemy = 0;

			}




			if (target_entity && globals->aimbot) {
				auto test = read<uintptr_t>(target_entity + offset::root_component);
				FVector Velocity = read<FVector>(pointer->root_component + offset::velocity); //offset::velocity

				auto closest_mesh = read<uint64_t>(target_entity + offset::skeletal_mesh);

				uint64_t currentactormesh = read<uint64_t>(target_entity + 0x280);

				FVector hitbox3;
				FVector hitbox;
				float projectileSpeed;//0;	
				float projectileGravityScale;//0;

				hitbox3 = Utilities->GetBoneLocation(closest_mesh, bone::HumanHead);

				if (globals->HeadBone) {
					hitbox = Utilities->GetBoneLocation(closest_mesh, bone::HumanHead);
				}		
				else if (globals->ChestBone) {
					hitbox = Utilities->GetBoneLocation(closest_mesh, bone::HumanChest);
				}


				int bone = bone::HumanHead;
				
				FVector2d hitbox_screen = Utilities->WorldToScreen(hitbox);

				auto Distance = camera::location.Distance(hitbox);

				auto rootHead = Utilities->GetBoneWithRotation(closest_mesh, bone::HumanHead);
				Vector3 rootHeadOut = Utilities->ProjectWorldToScreen(rootHead);
				if (hitbox.x != 0 || hitbox.y != 0 && (Utilities->GetCrossDistance(hitbox.x, hitbox.y, globals->width / 2, globals->height / 2) <= globals->field_of_view))
				{

					if (Utilities->IsVisible(closest_mesh)) {
						if (GetAsyncKeyState_Spoofed(globals->aimbot_key))
						{
							if (globals->prediction) {

								//     Learn something from it, do not paste like idiot

								float projectileSpeed = 60000; // Change it to real value, if u have more than 80iq u can make it work for all weapons :>
								float projectileGravityScale = 3.5f;  // Change it to real value, if u have more than 80iq u can make it work for all weapons :>

								auto closest_mesh2 = read<std::uint64_t>(target_entity + offset::skeletal_mesh);

								FVector hitbox = Utilities->GetBoneLocation(closest_mesh2, bone::HumanHead);

								float distance = camera::location.Distance(hitbox);

								auto test = read<uintptr_t>(target_entity + offset::root_component);

								FVector Velocity = read<FVector>(test + 0x168);

								FVector Predictor = Utilities->Prediction(hitbox, Velocity, distance, projectileSpeed);

								FVector2d hitbox_screen_predict = Utilities->WorldToScreen(Predictor);

								Utilities->cursor_to(hitbox_screen_predict.x, hitbox_screen_predict.y);

							}
							else
								Utilities->cursor_to(hitbox_screen.x, hitbox_screen.y);
						}
					}
				}
				
			}
			else {
				target_dist = FLT_MAX;
				target_entity = NULL;
			}			
		}
	};
} static game::c_game* Game = new game::c_game();