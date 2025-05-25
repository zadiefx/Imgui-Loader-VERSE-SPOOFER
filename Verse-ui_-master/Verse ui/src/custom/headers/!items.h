#pragma once
#include "main.h"

namespace custom {
	void begin(const char* name, ImVec2 size);
	void begin_child(const char* name, ImVec2 pos, ImVec2 size);
	void style();

	bool text(const char* text, ImVec2 pos, ImVec4 color = colors::white);
	bool announcement(const char* title, const char* description, ImVec2 pos);
	bool model(const char* model, std::string r, ImVec2 pos);
	bool serial(const char* name, std::string serial, ImVec2 pos, ImVec4 col, bool draw_line = false);
	bool status_check(std::string name, ImVec2 pos, bool* v, bool draw_line = false);
	bool discord_button(const wchar_t url[], ImVec2 pos);
	bool icon_button(const char* icon, ImVec2 pos, bool close = false);
	void Blur(HWND hwnd);
}

namespace items {
	bool input(const char* name, ImVec2 pos, static char buf[], size_t buf_size, ImGuiInputTextFlags flags);
	bool button(const char* name, ImVec2 pos, ImVec2 size = {300, 32}, std::string id = "");
	bool button_hint(const char* name, ImVec2 pos, const char* fst_line = "", const char* scn_line = "", const char* thr_line = "", const char* frt_line = "", const char* fif_line = "");
	bool tab(const char* icon, ImVec2 pos, bool v);
	bool subtab(const char* name, ImVec2 pos, bool v);
	void add_log(const std::string& log, log_type type_, ImVec2 pos = { 0,0 });
	bool render_logs();
}