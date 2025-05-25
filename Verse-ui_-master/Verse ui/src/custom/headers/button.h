#pragma once
#include "!items.h"
#include "main.h"

struct d {
	ImVec4 bg_col;
	ImVec4 bg_col2;
	ImVec4 text_col;

	float time = ImGui::GetIO().DeltaTime * 4;
	const char* t;
};

struct m {
	ImVec4 col;
	float time = ImGui::GetIO().DeltaTime * 5;
};

struct h {
	ImVec4 col;
	const char* t = "?";

	bool opened;
	float time = ImGui::GetIO().DeltaTime * 5;
};
