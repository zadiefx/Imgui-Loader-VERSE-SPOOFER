#include "!items.h"
#include "main.h"

void Move_Window()
{
    RECT rc;

    GetWindowRect(g_hwnd, &rc);
    MoveWindow(g_hwnd, rc.left + ImGui::GetWindowPos().x, rc.top + ImGui::GetWindowPos().y, window::size.x, window::size.y, TRUE);
    ImGui::SetWindowPos(ImVec2(0.f, 0.f));
}

void add_borders(ImVec2 size)
{
    auto* window = ImGui::GetForegroundDrawList();
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.f);

    const int vtx = window->VtxBuffer.Size;
    const ImVec4 color = ImColor(60, 124, 212, 255);

    window->AddRect(ImVec2(1, 1), ImVec2(size.x - 1, size.y - 1), ImGui::GetColorU32(color), window::rouding, ImDrawFlags_None, 2.f);
    ImGui::ShadeVertsLinearColorGradientKeepAlpha(window, vtx, window->VtxBuffer.Size, ImVec2(1, 1), ImVec2(size.x / 4, size.y / 3), ImGui::GetColorU32(color), ImColor(24, 24, 24, 24));

    ImGui::PopStyleVar();
}

void title(const char* name, const char* version, float _py)
{
    auto* window = ImGui::GetCurrentWindow();

    const ImVec2 t_name = ImGui::CalcTextSize(name);
    const ImVec2 t_version = ImGui::CalcTextSize(version);
    const ImVec2 t_login = ImGui::CalcTextSize("LOGIN");

    ImVec4 t = ImVec4(colors::white.x, colors::white.y, colors::white.z, colors::white.w / 3);

    ImGui::ShadowText(name, ImGui::GetColorU32(colors::white), ImGui::GetColorU32(t), 100, ImVec2((window->Size.x - t_name.x) / 2 - t_name.x + 30, _py));
    ImGui::ShadowText(version, ImGui::GetColorU32(colors::main_color), ImGui::GetColorU32(colors::main_color), 100, ImVec2((window->Size.x - t_version.x) / 2, _py));
    ImGui::ShadowText("LOGIN", ImGui::GetColorU32(colors::white), ImGui::GetColorU32(t), 100, ImVec2((window->Size.x - t_login.x) / 2 + t_login.x - 25, _py));
}

void custom::begin_child(const char* name, ImVec2 pos, ImVec2 size)
{
    auto* window = ImGui::GetCurrentWindow();

    const ImVec2 _pos = window->Pos + _pos;
    const ImVec2 _size = size;

    ImVec4 col = ImColor(60, 124, 212, 255);
    ImVec4 col2 = ImColor(7, 7, 7, 100);

    window->DrawList->AddRectFilled(pos, pos + size, ImGui::GetColorU32(col2), 0);
    window->DrawList->AddShadowRect(pos, pos + size, ImGui::GetColorU32(col), 50, { 0,0 }, ImDrawFlags_ShadowCutOutShapeBackground);
    window->DrawList->AddRect(pos, pos + size, ImGui::GetColorU32(col), 0.f, 0.f, 2.f);

    ImGui::SetNextWindowPos(pos);
    ImGui::BeginChild(name, size, false, ImGuiWindowFlags_NoScrollbar);
    {
        auto* c = ImGui::GetCurrentWindow();
    }
}

void custom::begin(const char* name, ImVec2 size)
{
    DWORD Window_Flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse;

    auto& style = ImGui::GetStyle();
    style.Alpha = 1.f;

    ImGui::SetNextWindowSize(size);
    ImGui::Begin(name, NULL, Window_Flags);
    auto* window = ImGui::GetCurrentWindow();

    window->DrawList->AddRectFilled(window->Pos + ImVec2(1, 1), window->Size - ImVec2(1, 1), ImGui::GetColorU32(colors::bg), window::rouding);

    Snowflake::Update(snow, Snowflake::vec3(0, 0), Snowflake::vec3(window::size.x, window::size.y));

    ImGui::PushFont(fonts::inter);
    window->DrawList->AddText({ ImVec2(window->Size.x - 165, 30) }, ImGui::GetColorU32(colors::lwhite), "06/04/20:56");
    window->DrawList->AddLine({ window->Size.x - 55, 33.5 }, { window->Size.x - 55, 48 }, ImGui::GetColorU32(colors::lwhite), 2);
    ImGui::PopFont();

    window->DrawList->AddImage(images::logo, { 20, 10 }, { 85, 75 }, { 0,0 }, { 1,1 }, ImGui::GetColorU32(ImVec4(1, 1, 1, 1)));
    if (tab == 0) title(name, "V4", 100);

    add_borders(size);
    Move_Window();
}

bool custom::serial(const char* name, std::string serial, ImVec2 pos, ImVec4 col, bool draw_line)
{
    auto* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    const auto id = window->GetID(name);
    const ImVec2 _pos = window->Pos + pos;
    const ImVec2 size = ImGui::CalcTextSize(name) + ImVec2(ImGui::CalcTextSize(serial.c_str()).x, 0);
    const ImRect total = { _pos, _pos + size };

    ImGui::ItemSize(total, id); if (!ImGui::ItemAdd(total, id)) return false;

    window->DrawList->AddText(_pos, ImGui::GetColorU32(col), name);
    window->DrawList->AddText(_pos + ImVec2(ImGui::CalcTextSize(name).x + 8, 0), ImGui::GetColorU32(col), serial.c_str());

    if (draw_line)
    {
        window->DrawList->AddLine(total.Min + ImVec2(size.x, 0) + ImVec2(15, 3), total.Max + ImVec2(15, -2), ImGui::GetColorU32(colors::white), 2.f);
    }
}


bool custom::model(const char* model, std::string r, ImVec2 pos)
{
    auto* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    const auto id = window->GetID(model);
    const ImVec2 _pos = window->DC.CursorPos + pos;
    const ImVec2 t_size = ImGui::CalcTextSize(model) + ImVec2(ImGui::CalcTextSize(r.c_str()).x, 0);
    const ImRect total = ImRect(_pos, _pos + t_size);

    ImGui::ItemSize(total, id); if (!ImGui::ItemAdd(total, id)) return false;

    const ImVec4 model_col = ImColor(79, 235, 226, 255);
    const ImVec4 str_col = colors::white;
    const ImVec2 space = { 5, 0 };

    window->DrawList->AddText(total.Min, ImGui::GetColorU32(model_col), model);
    window->DrawList->AddText(total.Min + ImVec2(ImGui::CalcTextSize(model).x, 0) + space, ImGui::GetColorU32(str_col), r.c_str());
}

bool custom::status_check(std::string name, ImVec2 pos, bool* v, bool draw_line)
{
    auto* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    std::string final = *v ? name += " Avaliable" : name += " Unavaliable";
    ImVec4 col = *v ? colors::red : colors::green;

    const auto id = window->GetID(final.c_str());
    const ImVec2 _pos = window->Pos + pos;
    const ImVec2 size = ImGui::CalcTextSize(final.c_str());
    const ImRect total = ImRect(_pos, _pos + size);

    ImGui::ItemSize(total, id); if (!ImGui::ItemAdd(total, id)) return false;

    window->DrawList->AddText(_pos, ImGui::GetColorU32(col), final.c_str());
    if (draw_line)
    {
        window->DrawList->AddLine(total.Min + ImVec2(size.x, 0) + ImVec2(8, 3), total.Max + ImVec2(8, -2), ImGui::GetColorU32(colors::white), 2.f);
    }
}

bool custom::announcement(const char* title, const char* description, ImVec2 pos)
{
    auto* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    const auto id = window->GetID(title);
    const ImVec2 _pos = window->DC.CursorPos + pos;
    const ImVec2 size = { 530, 65 };
    const ImRect total = { _pos, _pos + size };

    ImGui::ItemSize(total, id); if (!ImGui::ItemAdd(total, id)) return false;

    const ImVec4 title_col = colors::main_color;
    const ImVec4 description_col = ImColor(60, 124, 212, 255);
    const ImVec4 bg_col = ImColor(20, 20, 20, 255);
    const float rounding = 6.f;

    window->DrawList->AddRectFilled(total.Min, total.Max, ImGui::GetColorU32(bg_col), rounding);
    window->DrawList->AddText(total.Min + ImVec2(15, 10), ImGui::GetColorU32(colors::main_color), title);
    window->DrawList->AddText(total.Min + ImVec2(15, 35), ImGui::GetColorU32(description_col), description);
}

struct i {
    ImVec4 text_col;
    float time = ImGui::GetIO().DeltaTime * 2;
};

bool custom::icon_button(const char* icon, ImVec2 pos, bool close)
{
    auto* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGui::PushFont(fonts::icon);

    const ImGuiID id = window->GetID(icon);
    const ImVec2 text_size = ImGui::CalcTextSize(icon);
    const ImVec2 _pos = window->Pos - window->Scroll + pos;

    ImGui::SetCursorPos(_pos);
    bool result = ImGui::InvisibleButton(icon, text_size);

    bool active = ImGui::IsItemActive();
    bool hovered = ImGui::IsItemHovered();

    ImVec4 text_col = close && active ? colors::white : close && hovered ? colors::white : active ? colors::main_color : hovered ? colors::main_color : colors::gray;

    static std::map<ImGuiID, i> anim;
    auto& w = anim.emplace(id, ::i{ text_col }).first->second;

    w.text_col = ImLerp(w.text_col, text_col, w.time);

    window->DrawList->AddText(_pos, ImGui::GetColorU32(w.text_col), icon);

    ImGui::PopFont();
    return result;
}

bool custom::discord_button(const wchar_t url[], ImVec2 pos)
{
    auto* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    ImVec2 _pos = window->Pos - window->Scroll + pos;
    ImVec2 size = { 40, 40 };

    ImGui::SetCursorPos(_pos);
    bool result = ImGui::InvisibleButton("discord", size);

    window->DrawList->AddRectFilled(_pos + ImVec2(8, 8), _pos + size - ImVec2(8, 8), ImGui::GetColorU32(colors::white));

    ImGui::SetCursorPos(_pos);
    ImGui::Image(images::disc, size);

    if (result) HINSTANCE open = ShellExecute(NULL, L"open", url, NULL, NULL, SW_SHOWNORMAL);

    return result;
}

void custom::style()
{
    auto& style = ImGui::GetStyle();

    style.ItemSpacing = ImVec2(0, 10);
    style.WindowPadding = ImVec2(0, 0);
    style.WindowBorderSize = 0.f;
    style.ChildBorderSize = 0.f;
    style.WindowRounding = window::rouding;
    style.ChildRounding = window::rouding / 2;

    style.Colors[ImGuiCol_ChildBg] = colors::transparent;
    style.Colors[ImGuiCol_WindowBg] = colors::bg;
    style.Colors[ImGuiCol_TextSelectedBg] = colors::item_col;
}

bool custom::text(const char* text, ImVec2 pos, ImVec4 color)
{
    auto* window = ImGui::GetCurrentWindow();
    ImGui::PushID(text);
    if (window->SkipItems) { ImGui::PopID(); return false; }

    ImVec2 text_size = ImGui::CalcTextSize(text);
    ImVec2 _pos = window->Pos - window->Scroll + pos;
    ImRect rect = ImRect(_pos, _pos + text_size);
    ImGuiID id = window->GetID(text);

    ImGui::ItemSize(rect, id);
    if (!ImGui::ItemAdd(rect, id)) { ImGui::PopID(); return false; }

    window->DrawList->AddText(rect.Min, ImGui::GetColorU32(color), text);
    ImGui::PopID();

    return true;
}

struct d {
    float line_pos;
    float total_chars;
    float target_x;
    bool reset_text;
    float lastTime;
    float a;
    float io = ImGui::GetIO().DeltaTime * 5;
    float timer = io;

    int current_text_index = 0;
    std::vector<std::string> animated_texts;
    ImVec2 pos;
};

void custom::Blur(HWND hwnd)
{
    struct ACCENTPOLICY
    {
        int na;
        int nf;
        int nc;
        int nA;
    };
    struct WINCOMPATTRDATA
    {
        int na;
        PVOID pd;
        ULONG ul;
    };

    const HINSTANCE hm = LoadLibrary(L"user32.dll");
    if (hm)
    {
        typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);

        const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hm, "SetWindowCompositionAttribute");
        if (SetWindowCompositionAttribute)
        {
            ACCENTPOLICY policy = { 3, 0, 0, 0 }; // 4,0,155,0 (Acrylic blur) 3,0,0,0 
            WINCOMPATTRDATA data = { 19, &policy,sizeof(ACCENTPOLICY) };
            SetWindowCompositionAttribute(hwnd, &data);
        }
        FreeLibrary(hm);
    }
}
