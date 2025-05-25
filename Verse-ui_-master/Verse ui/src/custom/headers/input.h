#pragma once
#include "!items.h"
#include "main.h"

struct c {
	float time = ImGui::GetIO().DeltaTime * 4;

	float shadow_thickness;
	ImVec4 text_col;
};

namespace input {
	const ImVec4 line = colors::item_col;

	const ImVec4 text_active = colors::transparent;
	const ImVec4 text = colors::white;

	float shadow_active = 50;
	float shadow = 30;
}