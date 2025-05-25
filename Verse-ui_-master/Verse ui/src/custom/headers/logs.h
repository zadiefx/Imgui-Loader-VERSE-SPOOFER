#pragma once
#include "!items.h"
#include "main.h"

struct Logs {
	std::string log;
	ImVec4 text_col;
	log_type type;
	ImVec2 pos;
	float alpha;
	float time = ImGui::GetIO().DeltaTime * 5;
};

std::vector<Logs> logs;