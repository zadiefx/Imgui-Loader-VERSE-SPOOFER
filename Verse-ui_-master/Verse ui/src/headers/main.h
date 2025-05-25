#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#pragma comment(lib, "D3DX11.lib")

#include <windows.h>
#include <D3DX11tex.h>
#include <d3d11.h>

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"
#include "snowflakes.hpp"

extern HWND g_hwnd;
inline ID3D11Device* g_pd3dDevice = nullptr;
extern std::vector<Snowflake::Snowflake> snow;

inline int tab = 0;
inline int subtab1 = 0;
inline int subtab2 = 10;

inline float alpha = 0;
inline float alpha2 = 0;

inline std::string mobo_manufacturer;
inline std::string mobo_model;
inline std::string ethernet_adapter;
inline std::string disks;
inline std::string _cpu;
inline std::string mobo;
inline std::string chassis;
inline std::string mac;
inline std::string uuid;

inline bool wifi;
inline bool bt;
inline bool tpm;


namespace ui {
	void Render();
	void Before_Loop();
}

namespace colors {
	const ImVec4 bg = ImColor(7, 7, 7, 225);
	const ImVec4 lbg = ImColor(17, 17, 17, 255);

	const ImVec4 main_color = ImColor(60, 124, 212, 255);
	const ImVec4 second_color = ImColor(60, 124, 212, 255);

	const ImVec4 white = ImColor(252, 255, 254, 255);
	const ImVec4 lwhite = ImColor(174, 174, 174, 255);
	const ImVec4 gray = ImColor(111, 111, 111, 255);
	const ImVec4 gray2 = ImColor(125, 125, 125, 255);
	const ImVec4 dark_gray = ImColor(40, 40, 40, 255);
	const ImVec4 red = ImColor(162, 14, 19, 255);
	const ImVec4 green = ImColor(78, 209, 76, 255);

	const ImVec4 item_bg = ImColor(60, 124, 212, 255);
	const ImVec4 item_col = ImColor(60, 124, 212, 255);
	const ImVec4 item_col2 = ImColor(60, 124, 212, 255);
	const ImVec4 particles = ImColor(100, 100, 100, 100);

	const ImVec4 transparent = { 0,0,0,0 };
}

namespace images {
	inline ID3D11ShaderResourceView* logo;
	inline ID3D11ShaderResourceView* disc;
}

namespace fonts {
	inline ImFont* inter = nullptr;
	inline ImFont* inter2 = nullptr;
	inline ImFont* inter3 = nullptr;
	inline ImFont* icon = nullptr;
	inline ImFont* t = nullptr;
}

namespace window {
	inline ImVec2 size = { 670, 480 };
	const float rouding = 8.f;
}

inline void alpha_anim() {
	auto& style = ImGui::GetStyle();
	style.Alpha = alpha;
	alpha = std::clamp(alpha + (2 * ImGui::GetIO().DeltaTime * 1.5f), 0.0f, 1.f);
}

enum log_type {
	none,
	success,
	error
};
