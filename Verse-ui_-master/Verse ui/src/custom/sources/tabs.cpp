#include "icon tab.h"

bool items::tab(const char* icon, ImVec2 pos, bool v)
{
	auto* window = ImGui::GetCurrentWindow();
	if (window->SkipItems) return false;

	ImGui::PushFont(fonts::t);

	const ImGuiID id = window->GetID(icon);
	const ImVec2 _pos = window->Pos - window->Scroll + pos;
	const ImVec2 text_size = { 30, 33 };

	ImGui::SetCursorPos(pos);
	bool b = ImGui::InvisibleButton(icon, text_size);

	bool active = (v == true);
	bool hovered = ImGui::IsItemHovered();

	ImVec4 icon_c = v ? colors::main_color : hovered ? colors::main_color : colors::gray;

	static std::map<ImGuiID, t> anim;
	auto& w = anim.emplace(id, ::t{ icon_c, ImGui::GetIO().DeltaTime * 5 }).first->second;

	w.icon = ImLerp(w.icon, icon_c, w.time);
	window->DrawList->AddText(_pos , ImGui::GetColorU32(w.icon), icon);

	ImGui::PopFont();

	if (b && !v) { alpha2 = 0; }
	if (b && v) return NULL;

	return b;
}

bool items::subtab(const char* name, ImVec2 pos, bool v)
{
	auto* window = ImGui::GetCurrentWindow();
	if (window->SkipItems) return false;

	const auto id = window->GetID(name);
	const ImVec2 _pos = window->Pos - window->Scroll + pos - ImVec2(5,5);
	const ImVec2 text_size = ImGui::CalcTextSize(name) + ImVec2(5,5);

	ImGui::SetCursorPos(_pos);
	bool r = ImGui::InvisibleButton(name, text_size);

	bool active = (v == true);
	bool hovered = ImGui::IsItemHovered();

	const ImVec4 text_col = active ? colors::main_color : colors::gray;
	const ImVec4 line_col = active ? colors::main_color : colors::transparent;
	const ImVec2 line_size = active ? ImVec2(20, text_size.y -1 ) : ImVec2(-5, text_size.y -1);

	static std::map<ImGuiID, z> anim;
	auto& w = anim.emplace(id, ::z{ line_size, line_col, text_col }).first->second;

	w.line_col = ImLerp(w.line_col, line_col, 0.1);
	w.text_col = ImLerp(w.text_col, text_col, 0.1);
	w.line_pos = ImLerp(w.line_pos, line_size, 0.1);

	ImGui::PushClipRect(_pos, _pos + text_size + ImVec2(0, line_size.y * 2), false);
	window->DrawList->AddText(_pos, ImGui::GetColorU32(w.text_col), name);
	window->DrawList->AddLine({ _pos.x, _pos.y + w.line_pos.y }, _pos + w.line_pos, ImGui::GetColorU32(colors::main_color), 2);
	ImGui::PopClipRect();

	if (r && !v) { alpha = 0; }
	if (r && v) return NULL;

	return r;
}