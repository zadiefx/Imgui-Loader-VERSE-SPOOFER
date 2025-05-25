#include "button.h"

bool items::button(const char* name, ImVec2 pos, ImVec2 size, std::string id_)
{
	auto* window = ImGui::GetCurrentWindow();
	if (window->SkipItems) return false;

	const ImVec2 _pos = window->Pos - window->Scroll + pos;
	const ImVec2 _size = size;
	const ImVec2 text_size = ImGui::CalcTextSize(name);
	const float rounding = 0.f;

	ImGuiID id = NULL;

	if (id_.empty()) {
		id_ = name;
		id = window->GetID(name);
	}

	else {
		id = window->GetID(id_.c_str());	
	}

	ImGui::SetCursorPos(_pos);
	bool result = ImGui::InvisibleButton(id_.c_str(), _size);

	bool active = ImGui::IsItemActive();
	bool hovered = ImGui::IsItemHovered();

	ImVec4 p = ImColor(60, 124, 212, 255);

	ImVec4 bg_col = active ? p : hovered ? colors::item_col2 : colors::item_col2;
	ImVec4 bg_col2 = active ? p : hovered ? p : colors::item_col2;
	ImVec4 text_col = active ? colors::white : hovered ? colors::white : colors::white;

	static std::map<ImGuiID, d> anim;
	auto& w = anim.emplace(id, ::d{ bg_col, bg_col2, text_col, ImGui::GetIO().DeltaTime * 4 }).first->second;

	w.bg_col = ImLerp(w.bg_col, bg_col, 0.06);
	w.bg_col2 = ImLerp(w.bg_col2, bg_col2, 0.06);
	w.text_col = ImLerp(w.text_col, text_col, w.time);

	window->DrawList->AddRectFilledMultiColor(_pos, _pos + _size, ImGui::GetColorU32(w.bg_col2), ImGui::GetColorU32(w.bg_col), ImGui::GetColorU32(w.bg_col), ImGui::GetColorU32(w.bg_col2));
	window->DrawList->AddText(_pos + ImVec2((_size - text_size) / 2), ImGui::GetColorU32(w.text_col), name);

	return result;
}

bool r_button(const char* name, ImVec2 pos, ImVec2 size = { 430, 46 })
{
	auto* window = ImGui::GetCurrentWindow();
	if (window->SkipItems) return false;

	const auto id = window->GetID(name);
	const ImVec2 b_size = size;
	const float r_rounding = 3.f;

	ImGui::SetCursorPos(pos);
	bool r = ImGui::InvisibleButton(name, b_size);

	bool r_act = ImGui::IsItemActive();
	bool r_hov = ImGui::IsItemHovered();

	ImVec4 r_col = r_act ? ImColor(60, 124, 212) : r_hov ? ImColor(60, 124, 212) : ImColor(60, 124, 212, 255);

	static std::map<ImGuiID, m> anim;
	auto& w = anim.emplace(id, m{ r_col }).first->second;

	w.col = ImLerp(w.col, r_col, w.time);

	window->DrawList->AddRectFilled(window->Pos + pos, window->Pos + pos + b_size, ImGui::GetColorU32(w.col), r_rounding);
	window->DrawList->AddText(window->Pos + pos + ImVec2((b_size - ImGui::CalcTextSize(name)) / 2), ImGui::GetColorU32(colors::white), name);

	return r;
}

bool items::button_hint(const char* name, ImVec2 pos, const char* fst_line, const char* scn_line, const char* thr_line, const char* frt_line, const char* fif_line)
{
	auto* window = ImGui::GetCurrentWindow();
	if (window->SkipItems) return false;

	const auto id = window->GetID(name);
	const ImVec2 b_size = { 430, 46 };

	bool r = r_button(name, pos);

	static std::map<ImGuiID, h> anim;
	auto& w = anim.emplace(id, ::h{  }).first->second;

	const ImVec2 h_pos = pos + ImVec2(440, 0);
	std::string _id = "_";
	_id += name;

	if (items::button(w.t, h_pos, { window->Size.x - 30 - h_pos.x, b_size.y }, _id)) w.opened = true;

	if (w.opened)
	{
		DWORD Window_Flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse;
		ImVec2 window_size = { 450, 255 };
		ImVec4 w_bg = ImColor(20, 20, 20, 255);
		ImVec4 mask = ImColor(7, 7, 7, 100);
		ImVec4 d_blue = ImColor(0, 0, 48, 255);
		const float _rounding = 5.f;

		window->DrawList->AddRectFilled(window->Pos, window->Pos + window->Size, ImGui::GetColorU32(mask), window::rouding);

		ImGui::SetNextWindowPos((window::size - window_size) / 2);
		ImGui::BeginChild("POPUP", window_size, false, Window_Flags);
		{
			auto* wi = ImGui::GetCurrentWindow();
			wi->DrawList->AddRectFilled(wi->Pos, wi->Pos + wi->Size, ImGui::GetColorU32(w_bg), _rounding);
			wi->DrawList->AddRectFilledMultiColor(wi->Pos, wi->Pos + ImVec2(wi->Size.x, 40), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), ImGui::GetColorU32(d_blue), ImGui::GetColorU32(d_blue), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)));
			wi->DrawList->AddText(wi->Pos + ImVec2(10, 10), ImGui::GetColorU32(colors::white), name);



			ImGui::PushFont(fonts::inter3);
			{
				wi->DrawList->AddText(wi->Pos + ImVec2(20, 70), ImGui::GetColorU32(colors::gray), fst_line);

				wi->DrawList->AddText(wi->Pos + ImVec2(20, 100), ImGui::GetColorU32(colors::green), scn_line);
				wi->DrawList->AddText(wi->Pos + ImVec2(20, 115), ImGui::GetColorU32(colors::green), thr_line);

				wi->DrawList->AddText(wi->Pos + ImVec2(20, 150), ImGui::GetColorU32(colors::red), frt_line);
				wi->DrawList->AddText(wi->Pos + ImVec2(20, 165), ImGui::GetColorU32(colors::red), fif_line);
			}
			ImGui::PopFont();

			if (r_button("close", ImVec2((wi->Size.x - 100) / 2, wi->Size.y - 50), { 100, 25 })) w.opened = false;
			wi->DrawList->AddRect(wi->Pos, wi->Pos + wi->Size, ImGui::GetColorU32(colors::white), _rounding);
		}
		ImGui::End();

	}
	return r;
}
