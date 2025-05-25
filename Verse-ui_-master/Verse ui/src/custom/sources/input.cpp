#include "input.h"

bool items::input(const char* name, ImVec2 pos, static char buf[], size_t buf_size, ImGuiInputTextFlags flags)
/*
DO NOT MODIFY THIS FILE IN CASE YOU WANT TO CHANGE
GENERAL THINGS AS COLORS OR SHAODW THICKNESS
CHANGE THEM IN INPUT.H
*/
{
	auto* window = ImGui::GetCurrentWindow();
	auto& style = ImGui::GetStyle();
	if (window->SkipItems) return false;

	const ImGuiID id = window->GetID(name);
	const ImVec2 size = { 300.f, 10.f };
	const ImVec2 _pos = window->Pos - window->Scroll + pos;
	ImVec2 text_size = ImGui::CalcTextSize(name);

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, size.y));
	const ImVec2 _pmax = ImVec2(size.x, ImGui::GetFrameHeight());
	const float rounding = 0;

	std::string lbl = "###";
	lbl += name;

	ImGui::SetCursorPos(_pos);
	ImGui::SetNextItemWidth(size.x);

	ImGui::PushStyleColor(ImGuiCol_TextDisabled, { 0,0,0,0 });
	ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0,0,0,0 });

	bool result = ImGui::InputTextWithHint(lbl.c_str(), name, buf, (int)buf_size, flags);

	bool active = ImGui::IsItemActive();
	bool hovered = ImGui::IsItemHovered();
	bool empty = (!active && strlen(buf) == 0);

	ImVec4 text_col = empty ? colors::gray : colors::transparent;
	ImVec4 line_col = input::line;
	float line_thc = active ? input::shadow_active : input::shadow;

	static std::map<ImGuiID, c> anim;
	auto& w = anim.emplace(id, ::c{ ImGui::GetIO().DeltaTime * 4, line_thc, text_col }).first->second;

	w.shadow_thickness = ImLerp(w.shadow_thickness, line_thc, w.time);
	w.text_col = ImLerp(w.text_col, text_col, w.time);

	window->DrawList->AddShadowRect(ImVec2(_pos.x, _pos.y + _pmax.y - 3), _pos + _pmax - ImVec2(0, 3), ImGui::GetColorU32(line_col), w.shadow_thickness, { 0, 0 }, 0, rounding);
	window->DrawList->AddRectFilled(ImVec2(_pos.x, _pos.y + _pmax.y - 3), _pos + _pmax - ImVec2(0, 3), ImGui::GetColorU32(line_col), 8);
	window->DrawList->AddText(ImVec2(_pos.x + style.FramePadding.x, _pos.y + (_pmax.y - text_size.y) / 2), ImGui::GetColorU32(w.text_col), name);

	ImGui::PopStyleColor(2);
	ImGui::PopStyleVar();

	return result;
}
