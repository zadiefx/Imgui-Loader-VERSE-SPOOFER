#include "logs.h"

void items::add_log(const std::string& log, log_type type_, ImVec2 pos)
{
	logs.push_back(Logs(log, colors::transparent, type_, pos, 0.f));
}

bool items::render_logs()
{
	auto* window = ImGui::GetCurrentWindow();

	for (auto it = logs.begin(); it != logs.end(); ++it)
	{
		auto id = window->GetID(it->log.c_str());

		std::string status;
		ImVec4 col;

		switch (it->type)
		{
		case none: status = "[+] "; col = colors::white; break;
		case success: status = "[+] "; col = colors::green; break;
		case error: status = "[-] "; col = colors::red; break;
		}

		std::string final_t = status + it->log;

		ImVec2 size = ImGui::CalcTextSize(final_t.c_str());
		ImVec2 pos = window->DC.CursorPos + it->pos + ImVec2(15, 0);

		ImGui::ItemSize(size); if (!ImGui::ItemAdd({ pos, pos + size }, id)) continue;

		it->text_col = ImLerp(it->text_col, col, it->time);
		window->DrawList->AddText(pos, ImGui::GetColorU32(it->text_col), final_t.c_str());
	}
}