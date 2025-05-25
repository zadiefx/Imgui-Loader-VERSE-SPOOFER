#pragma once
#include "main.h"
#include "!items.h"

struct t {
	ImVec4 icon;
	float time = ImGui::GetIO().DeltaTime * 5;
};

struct z {
	ImVec2 line_pos;
	ImVec4 line_col;
	ImVec4 text_col;
	float time = ImGui::GetIO().DeltaTime * 4;
};