#include "main.h"
#include "fonts.h"
#include "!items.h"
#include "snowflakes.hpp"
#include "spoof.h"
#include <iostream>
#include <thread>
std::vector<Snowflake::Snowflake> snow;
char license[40] = "";

void ui::Before_Loop()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, logo, sizeof(logo), nullptr, nullptr, &images::logo, 0);
	D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, disc, sizeof(disc), nullptr, nullptr, &images::disc, 0);

	fonts::inter = io.Fonts->AddFontFromMemoryTTF(inter, sizeof(inter), 20);
	fonts::inter2 = io.Fonts->AddFontFromMemoryTTF(inter_2, sizeof(inter_2), 45);
	fonts::inter3 = io.Fonts->AddFontFromMemoryTTF(inter, sizeof(inter), 15);
	fonts::icon = io.Fonts->AddFontFromMemoryTTF(icon, sizeof(icon), 20);
	fonts::t = io.Fonts->AddFontFromMemoryTTF(icont, sizeof(icont), 39);

	Snowflake::CreateSnowFlakes(snow, 40, 3.f/*minimum size*/, 20.f/*maximum size*/, 0/*imgui window x position*/, 0/*imgui window y position*/, window::size.x, window::size.y, Snowflake::vec3(0.08, .50f)/*gravity*/, ImGui::GetColorU32(colors::particles)/*color*/);
	custom::Blur(g_hwnd);
	custom::style();
}
bool spoofasus;
bool spoof;
bool done;
bool macspoof132;
bool success13 = spoof13(); // Call function and store result
void ui::Render()
{
	ImGui::PushFont(fonts::inter2);

	custom::begin("VERSE", window::size);
	{
		auto* window = ImGui::GetCurrentWindow();
		auto& style = ImGui::GetStyle();

		if (custom::icon_button("c", { window->Size.x - 50, 31 }, true)) exit(0);

		ImGui::PushFont(fonts::inter);
		custom::discord_button(L"https://discord.gg/KmjaPf6J3b", { 30, window->Size.y - 70 });
		style.Alpha = alpha;

		if (tab == 0)
		{
			alpha_anim();
			items::input("LICENSE KEY", { (window->Size.x - 300) / 2, 190 }, license, IM_ARRAYSIZE(license), 0);

			// Define your 10 valid keys
			const char* validKeys[10] = {
				"SosaOT", "1", "2", "3", "4",
				"5", "6", "7", "8", "9"
			};

			// Check if the input matches any of the valid keys
			bool validKeyFound = false;
			for (int i = 0; i < 10; ++i)
			{
				if (strcmp(license, validKeys[i]) == 0)
				{
					validKeyFound = true;
					break;
				}
			}

			// If the key is valid, switch to tab 1, otherwise close the process
			if (items::button("Login", { (window->Size.x - 300) / 2, 240 }, { 300, 37 }))
			{
				if (validKeyFound)
				{
					alpha = 0;
					tab = 1;
				}
				else
				{
					// Close the process or do something else if the key is invalid
					exit(0); // Or you can do a custom action here to close or terminate
				}
			}

			custom::text("Build: V4.45", { window->Size - ImVec2(120, 45) }, colors::gray);
		}

		if (tab > 0)
		{
			static float a3 = 0.f;
			alpha2 = std::clamp(alpha2 + (2 * ImGui::GetIO().DeltaTime * 1.5f), 0.0f, 1.f);
			a3 = std::clamp(a3 + (2 * ImGui::GetIO().DeltaTime * 1.5f), 0.0f, 1.f);

			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, a3);
			window->DrawList->AddLine(window->Pos + ImVec2(0, 80), window->Pos + ImVec2(window->Size.x, 80), ImGui::GetColorU32(colors::main_color), 2);
			window->DrawList->AddLine(window->Pos + ImVec2(100, 80), window->Pos + ImVec2(100, window->Size.y - 10), ImGui::GetColorU32(colors::main_color), 2);
			window->DrawList->AddLine(window->Pos + ImVec2(0, window->Size.y - 100), window->Pos + ImVec2(100, window->Size.y - 100), ImGui::GetColorU32(colors::main_color), 2.f);

			ImGui::PushFont(fonts::t);
			if (items::tab("G##1", ImVec2((100 - ImGui::CalcTextSize("G").x) / 2, 180), tab == 1)) { alpha = 0; tab = 1; subtab1 = 0; subtab2 = 10; }
			if (items::tab("I##1", ImVec2((100 - ImGui::CalcTextSize("I").x) / 2, 240), tab == 2)) { alpha = 0; tab = 2; subtab2 = 0; subtab1 = 10; }
			ImGui::PopFont();
			ImGui::PopStyleVar();
		}

		if (tab == 1)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha2);
			if (items::subtab("Announcements", { 120, 38 }, subtab1 == 0)) subtab1 = 0;
			if (items::subtab("Instructions", { 270, 38 }, subtab1 == 1)) subtab1 = 1;
			ImGui::PopStyleVar();
		}

		if (tab == 2)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha2);
			if (items::subtab("Device", { 120, 38 }, subtab2 == 0)) subtab2 = 0;
			if (items::subtab("Spoofer", { 210, 38 }, subtab2 == 1)) subtab2 = 1;
			if (items::subtab("Miscellaneous", { 300, 38 }, subtab2 == 2)) subtab2 = 2;
			ImGui::PopStyleVar();
		}

		if (subtab1 == 0 && tab > 0)
		{
			alpha_anim();

			custom::announcement("You are on the latest VERSE V1.45 | 02/12/25", "Added option to unspoof all serials, & overall stability.", { 120, 45 });
			custom::announcement("VERSE V1.41 | 01/02/25", "User-interface improvements, bug fixes & overall stability.", { 120, 45 });
			custom::announcement("VERSE V1.40 | 12/03/24", "Asus improved, UI Changes, Insyde support, Bug  fixes.", { 120, 45 });
			custom::announcement("VERSE V1.35 | 10/22/24", "Revamped LEGIT Serials, Optimizations & Bug fixes.", { 120, 45 });
		}

		if (subtab2 == 0 && tab > 0)
		{
			alpha_anim();

			custom::model("Motherboard Manufacturer: ", mobo_manufacturer, { 120, 40 });
			custom::model("Motherboard Model: ", mobo_model, { 120, 45 });
			custom::model("Ethernet Adapter: ", ethernet_adapter, { 120, 50 });
			custom::model("Disk Drives: ", disks, { 120, 55 });
			custom::model("CPU: ", _cpu, { 120, 60 });
			
			window->DrawList->AddLine(window->DC.CursorPos + ImVec2(120, 65), window->DC.CursorPos + ImVec2(window->Size.x, 65), ImGui::GetColorU32(colors::dark_gray), 2.f);

			custom::status_check("WIFI:", { 120, 300 }, &wifi, true);
			custom::status_check("Bluetooth:", { 275, 300 }, &bt, false);
			custom::serial("Baseboard:", mobo, { 120, 333 }, colors::green, true);
			custom::serial("Chassis:", chassis, { 350, 333 }, colors::red);
			custom::serial("MAC Address:", mac, { 120, 366 }, colors::green, true);
			custom::serial("File Traces:", "Not found", { 428, 366 }, colors::red);
			custom::serial("UUID:", uuid, { 120, 399 }, colors::green);
			custom::status_check("TPM [Trusted Computing] Status:", { 120, 432 }, &tpm); //This will only say its real status if you run the program as admin
		}

		if (subtab2 == 1)
		{
			alpha_anim();

			custom::begin_child("LOGS", { 130, 110 }, { window->Size.x - 130 - 30, 200 });
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
				items::render_logs();
				ImGui::Spacing();
				ImGui::PopStyleVar();
			}
			ImGui::EndChild();

			if (items::button("PERMANENT SPOOF", { 130, 325 }, { window->Size.x - 130 - 30, 48 })) {

				if (!done)
				{
					items::add_log("Launched Permanent Spoofing!", none, { 0, 35 });
					items::add_log("Please be patient for 2 minutes.", none, { 0, 40 }); // Using some spacing at the end, position will be relative, test it by yourself
					std::thread([]() {
						spoof1();
						}).detach();
				}
				spoof = true;
			}

			if (items::button("ASUS SPOOF", { 130, 385 }, { (window->Size.x - 160) / 2 - 7, 51 })); 
			{
				if (!done)
				{
					//items::add_log("Launched ASUS Spoofing!", none, { 0, 35 });
					//items::add_log("Please be patient for 3 minutes", none, { 0, 40 }); // Using some spacing at the end, position will be relative, test it by yourself
				}
				spoofasus = true;
			}
			if (items::button("MAC SPOOF", { 391, 385 }, { (window->Size.x - 160) / 2 - 7, 51 }))
			{
				if (!done)
				{
					items::add_log("Launched Mac Spoofing!", none, { 0, 35 });
					items::add_log("Please be patient for 30 seconds", none, { 0, 40 }); // Using some spacing at the end, position will be relative, test it by yourself
				}
				macspoof132 = true;

				bool result = macspoof(); // Track the success or error
				macspoofVoid(); // Run the spoof process without tracking success/error
				// Provide feedback in ImGui based on success
				if (result) {
					items::add_log("Successfully Mac spoofed", success, { 0, 40 }); // Using some spacing at the end, position will be relative, test it by yourself
				}
				else {
					items::add_log("Failed to mac spoof", error, { 0, 40 }); // Using some spacing at the end, position will be relative, test it by yourself
				}
			}
		}

		if (subtab2 == 2)
		{
			alpha_anim();

			items::button_hint("RESTORE OLD SERIALS", { 130, 110}, 
			"Restores old HWID before spoofing.\nResort to this if your serials get messed up");
			items::button_hint("WIFI MAC SPOOFER", { 130, 180 }, 
				"This option will change the mac-address of the WiFi network", 
				"You can also use this function if the 'permanent mac' option",
				"does not work. (You can use this on Ethernet)",
				"NOTE: Please make sure to disable external networks such as:",
				"Bluetooth adapters. or another WI-FI Adapters.");

			items::button_hint("FIX TOURNAMENT KICK", { 130, 250 }, 
				"Fixes tournament kick by using special cleaners\nand using spoofing methods on disk");
			items::button_hint("FIX SYSTEM INFORMATION", { 130, 320 },
				"If doing msinfo32 and your system shows up\nin random chars please use this to restart wmi");
		}

		if (spoof && !done)
		{
			auto& io = ImGui::GetIO();
			static float timer = 0.f; // Start at 0
			timer += io.DeltaTime; // Accumulate time using DeltaTime (frame time)

			if (timer > 60.0f) // Wait for 30 seconds
			{
				if (success13)
					items::add_log("Successfully Permanent spoofed, restart PC.", success, { 0, 70 });
				else
					items::add_log("Failed to permanent spoof.", error, { 0, 70 });

				done = true;
				spoof = false;
			}
		}

		/*if (spoofasus && !done)
		{
			auto& io = ImGui::GetIO();
			static float timer = 0.f; // Start at 0
			timer += io.DeltaTime; // Accumulate time using DeltaTime (frame time)

			if (timer > 30.0f) // Wait for 30 seconds
			{
				if (success13)
					items::add_log("Successfully ASUS spoofed, restart PC.", success, { 0, 70 });
				else
					items::add_log("Failed to spoof ASUS address.", error, { 0, 70 });

				done = true;
				spoofasus = false;
			}
		}*/
		if (macspoof132 && !done)
		{
			auto& io = ImGui::GetIO();
			static float timer = 0.f; // Start at 0
			timer += io.DeltaTime; // Accumulate time using DeltaTime (frame time)

			if (timer > 30.0f) // Wait for 30 seconds
			{
				if (success13)
					items::add_log("Successfully Mac spoofed, restart PC.", success, { 0, 70 });
				else
					items::add_log("Failed to spoof MAC address.", error, { 0, 70 });

				done = true;
				macspoof132 = false;
			}
		}



	}
	ImGui::End();
}