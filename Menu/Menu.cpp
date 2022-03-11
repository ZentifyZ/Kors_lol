#include "pch.h"
#include "Settings.h"

ImGuiContext* pImGuiContext;
ID3D11RenderTargetView* mainRenderTargetView;

void Settings::AddESPObject(char* SubTab, char* Prefab, char* Name, bool Draw)
{
	bool Exists = false;

	for (const ESPOption& option : ESPOptions)
	{
		if (option.Prefab == Prefab) Exists = true;
	}

	if (!Exists)
	{
		ESPOption Op;
		Op.Draw = Draw;
		Op.Prefab = Prefab;
		Op.Name = Name;
		Op.SubTab = SubTab;
		ESPOptions.push_back(Op);
	}
}

void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("[?]");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 30.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void ResourcesSubTab()
{
	static char* SelectedPrefab = "stone-ore.prefab";

	ImGui::BeginChild("Resources1", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "Resources") continue;

		if (!(SelectedPrefab == option.Prefab))
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
		else
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

		if (ImGui::Button(option.Name, ImVec2(100, 0)))
		{
			SelectedPrefab = option.Prefab;
		}

		ImGui::PopStyleColor();
	}
	ImGui::EndChild();

	ImGui::SameLine();

	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "Resources") continue;

		if (SelectedPrefab == option.Prefab)
		{
			ImGui::BeginChild("ResourcesCase0", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("Enabled", &option.Draw);
				ImGui::Checkbox("Name", &option.DrawName);
				ImGui::Checkbox("Distance", &option.DrawDistance);
				ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Max Distance", &option.checkMaxDistance); if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);

				ImGui::EndChild();
			}
			break;
		}
	}
}

void AnimalsSubTab()
{
	static char* SelectedPrefab = "wolf.prefab";

	ImGui::BeginChild("Animals1", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "Animals")continue;

		if (!(SelectedPrefab == option.Prefab))
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
		else
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

		if (ImGui::Button(option.Name, ImVec2(100, 0)))
		{
			SelectedPrefab = option.Prefab;
		}

		ImGui::PopStyleColor();
	}
	ImGui::EndChild();

	ImGui::SameLine();

	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "Animals") continue;

		if (SelectedPrefab == option.Prefab)
		{
			ImGui::BeginChild("AnimalsCase0", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("Enabled", &option.Draw);
				ImGui::Checkbox("Name", &option.DrawName);
				ImGui::Checkbox("Distance", &option.DrawDistance);
				ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Max Distance", &option.checkMaxDistance); if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);

				ImGui::EndChild();
			}
			break;
		}
	}
}

void VehiclesSubTab()
{
	static char* SelectedPrefab = "bradley";

	ImGui::BeginChild("Vehicles", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "Vehicles")continue;

		if (!(SelectedPrefab == option.Prefab))
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
		else
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

		if (ImGui::Button(option.Name, ImVec2(100, 0)))
		{
			SelectedPrefab = option.Prefab;
		}

		ImGui::PopStyleColor();
	}
	ImGui::EndChild();

	ImGui::SameLine();

	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "Vehicles") continue;

		if (SelectedPrefab == option.Prefab)
		{
			ImGui::BeginChild("VehiclesCase0", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("Enabled", &option.Draw);
				ImGui::Checkbox("Name", &option.DrawName);
				ImGui::Checkbox("Distance", &option.DrawDistance);
				ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Max Distance", &option.checkMaxDistance); if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);

				ImGui::EndChild();
			}
			break;
		}
	}
}

void TrapsSubTab()
{
	static char* SelectedPrefab = "flameturret.deployed.prefab";

	ImGui::BeginChild("Traps", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "Traps")continue;

		if (!(SelectedPrefab == option.Prefab))
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
		else
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

		if (ImGui::Button(option.Name, ImVec2(100, 0)))
		{
			SelectedPrefab = option.Prefab;
		}

		ImGui::PopStyleColor();
	}
	ImGui::EndChild();

	ImGui::SameLine();

	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "Traps") continue;

		if (SelectedPrefab == option.Prefab)
		{
			ImGui::BeginChild("TrapsCase0", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("Enabled", &option.Draw);
				ImGui::Checkbox("Name", &option.DrawName);
				ImGui::Checkbox("Distance", &option.DrawDistance);
				ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Max Distance", &option.checkMaxDistance); if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);

				ImGui::EndChild();
			}
			break;
		}
	}
}

void WorldSubTab()
{
	static char* SelectedPrefab = "(world)";

	ImGui::BeginChild("World", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "World")continue;

		if (!(SelectedPrefab == option.Prefab))
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
		else
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

		if (ImGui::Button(option.Name, ImVec2(100, 0)))
		{
			SelectedPrefab = option.Prefab;
		}

		ImGui::PopStyleColor();
	}
	ImGui::EndChild();

	ImGui::SameLine();

	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "World") continue;

		if (SelectedPrefab == option.Prefab)
		{
			ImGui::BeginChild("WorldCase0", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("Enabled", &option.Draw);
				ImGui::Checkbox("Name", &option.DrawName);
				ImGui::Checkbox("Distance", &option.DrawDistance);
				ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Max Distance", &option.checkMaxDistance); if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);

				ImGui::EndChild();
			}
			break;
		}
	}
}

void ConstructionSubTab()
{
	static char* SelectedPrefab = "loot-barrel-1.prefab";

	ImGui::BeginChild("Construction", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "Construction")continue;

		if (!(SelectedPrefab == option.Prefab))
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
		else
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

		if (ImGui::Button(option.Name, ImVec2(100, 0)))
		{
			SelectedPrefab = option.Prefab;
		}

		ImGui::PopStyleColor();
	}
	ImGui::EndChild();

	ImGui::SameLine();

	for (ESPOption& option : ESPOptions)
	{
		if (option.SubTab != "Construction") continue;

		if (SelectedPrefab == option.Prefab)
		{
			ImGui::BeginChild("ConstructionCase0", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("Enabled", &option.Draw);
				ImGui::Checkbox("Name", &option.DrawName);
				ImGui::Checkbox("Distance", &option.DrawDistance);
				ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Max Distance", &option.checkMaxDistance); if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);

				ImGui::EndChild();
			}
			break;
		}
	}
}

void CollectiblesSubTab()
{
	static int page = 0;
	const char* tabs[] = { "Ores", "Berries", "Crops", "Cloth" };

	ImGui::BeginChild("Collectibles1", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
	{
		for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
		{
			if (page != i)
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
			else
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

			if (ImGui::Button(tabs[i], ImVec2(100, 0)))
			{
				page = i;
			}

			ImGui::PopStyleColor();
		}
		ImGui::EndChild();
	}

	ImGui::SameLine();

	auto oresTab = []()
	{
		static char* SelectedPrefab = "stone-collectable.prefab";

		ImGui::BeginChild("PickupOre1", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
		for (ESPOption& option : ESPOptions)
		{
			if (option.SubTab != "PickupOre")continue;

			if (!(SelectedPrefab == option.Prefab))
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
			else
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

			if (ImGui::Button(option.Name, ImVec2(100, 0)))
			{
				SelectedPrefab = option.Prefab;
			}

			ImGui::PopStyleColor();
		}
		ImGui::EndChild();

		ImGui::SameLine();

		for (ESPOption& option : ESPOptions)
		{
			if (option.SubTab != "PickupOre") continue;

			if (SelectedPrefab == option.Prefab)
			{
				ImGui::BeginChild("PickupOre2", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
				{
					ImGui::Checkbox("Enabled", &option.Draw);
					ImGui::Checkbox("Name", &option.DrawName);
					ImGui::Checkbox("Distance", &option.DrawDistance);
					ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
					ImGui::Checkbox("Max Distance", &option.checkMaxDistance); if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);

					ImGui::EndChild();
				}
				break;
			}
		}
	};

	auto spawnedberryTab = []()
	{
		static char* SelectedPrefab = "berry-black-coll";

		float childsize = 115;
		float buttonsize = 115;

		for (ESPOption& option : ESPOptions)
		{
			if (option.SubTab != "Berries")continue;

			if (ImGui::CalcTextSize(option.Name).x + 45 > childsize)
			{
				childsize = ImGui::CalcTextSize(option.Name).x + 45;
				buttonsize = ImGui::CalcTextSize(option.Name).x + 30;
			}
		}

		ImGui::BeginChild("Berries1", ImVec2(childsize, 0), true, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize);
		for (ESPOption& option : ESPOptions)
		{
			if (option.SubTab != "Berries")continue;

			if (!(SelectedPrefab == option.Prefab))
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
			else
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

			if (ImGui::Button(option.Name, ImVec2(buttonsize, 0)))
			{
				SelectedPrefab = option.Prefab;
			}

			ImGui::PopStyleColor();
		}
		ImGui::EndChild();

		ImGui::SameLine();

		for (ESPOption& option : ESPOptions)
		{
			if (option.SubTab != "Berries") continue;

			if (SelectedPrefab == option.Prefab)
			{
				ImGui::BeginChild("Berries2", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
				{
					ImGui::Checkbox("Enabled", &option.Draw);
					ImGui::Checkbox("Name", &option.DrawName);
					ImGui::Checkbox("Distance", &option.DrawDistance);
					ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
					ImGui::Checkbox("Max Distance", &option.checkMaxDistance); if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);

					ImGui::EndChild();
				}
				break;
			}
		}
	};

	auto cropsTab = []()
	{
		static char* SelectedPrefab = "mushroom";

		ImGui::BeginChild("Crops1", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
		for (ESPOption& option : ESPOptions)
		{
			if (option.SubTab != "Crops")continue;

			if (!(SelectedPrefab == option.Prefab))
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
			else
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

			if (ImGui::Button(option.Name, ImVec2(100, 0)))
			{
				SelectedPrefab = option.Prefab;
			}

			ImGui::PopStyleColor();
		}
		ImGui::EndChild();

		ImGui::SameLine();

		for (ESPOption& option : ESPOptions)
		{
			if (option.SubTab != "Crops") continue;

			if (SelectedPrefab == option.Prefab)
			{
				ImGui::BeginChild("Crops2", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
				{
					ImGui::Checkbox("Enabled", &option.Draw);
					ImGui::Checkbox("Name", &option.DrawName);
					ImGui::Checkbox("Distance", &option.DrawDistance);
					ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
					ImGui::Checkbox("Max Distance", &option.checkMaxDistance); if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);

					ImGui::EndChild();
				}
				break;
			}
		}
	};

	auto clothTab = []()
	{
		static char* SelectedPrefab = "hemp-collectable";

		ImGui::BeginChild("Cloth1", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
		for (ESPOption& option : ESPOptions)
		{
			if (option.SubTab != "Cloth")continue;

			if (!(SelectedPrefab == option.Prefab))
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
			else
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

			if (ImGui::Button(option.Name, ImVec2(100, 0)))
			{
				SelectedPrefab = option.Prefab;
			}

			ImGui::PopStyleColor();
		}
		ImGui::EndChild();

		ImGui::SameLine();

		for (ESPOption& option : ESPOptions)
		{
			if (option.SubTab != "Cloth") continue;

			if (SelectedPrefab == option.Prefab)
			{
				ImGui::BeginChild("Cloth2", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
				{
					ImGui::Checkbox("Enabled", &option.Draw);
					ImGui::Checkbox("Name", &option.DrawName);
					ImGui::Checkbox("Distance", &option.DrawDistance);
					ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
					ImGui::Checkbox("Max Distance", &option.checkMaxDistance); if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);

					ImGui::EndChild();
				}
				break;
			}
		}
	};

	switch (page)
	{
	case 0:
		oresTab();
		break;
	case 1:
		spawnedberryTab();
		break;
	case 2:
		cropsTab();
		break;
	case 3:
		clothTab();
		break;
	}
}

void CombatTab()
{
	static int page = 0;
	const char* tabs[] = { "Aimbot", "Silent Aim", "Weapon Mods", "Rage" };

	ImGui::BeginChild("Combat1", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
	{
		for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
		{
			if (page != i)
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
			else
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

			if (ImGui::Button(tabs[i], ImVec2(100, 0)))
			{
				page = i;
			}

			ImGui::PopStyleColor();
		}
		ImGui::EndChild();
	}

	ImGui::SameLine();

	switch (page)
	{
	case 0:
		ImGui::BeginChild("Aimbot", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
		{
			ImGui::Checkbox("Aimbot", &Settings::Combat::Aimbot::Aimbot); ImGui::SameLine(); Menu::Hotkey("", &Globals::Hotkeys::hotkey_AimbotKey, ImVec2{ 100, 20 }); ImGui::SameLine(); HelpMarker("Automatically calculates best angle to hit a target.");
			ImGui::Checkbox("Smoothing", &Settings::Combat::Aimbot::Smoothing); ImGui::SameLine(); HelpMarker("Modifies The Aimbot Smoothing Amount, increasing the time it takes to aim at a target");
			ImGui::Checkbox("Draw FOV", &Settings::Combat::Aimbot::DrawFOV); ImGui::SameLine(); HelpMarker("Draws Aimbot Aim Field Of View");
			ImGui::Checkbox("Keep Target", &Settings::Combat::Aimbot::KeepTarget); ImGui::SameLine(); HelpMarker("Continues aiming at the same target regardless of other potential targets within fov");
			ImGui::SliderFloat("Aimbot Fov", &Settings::Combat::Aimbot::FOV, 0.f, 500.f);
			ImGui::SliderInt("Smoothing Amount", &Settings::Combat::Aimbot::SmoothingAmount, 0, 50);

			std::string SelectedOptions;

			SelectedOptions = "Ignoring";

			if (Settings::Combat::Aimbot::IgnorePlayers)
			{
				SelectedOptions += " Players";
			}
			if (Settings::Combat::Aimbot::IgnoreSleepers)
			{
				if (strstr(SelectedOptions.c_str(), " "))
					SelectedOptions += ", ";
				SelectedOptions += "Sleepers";
			}
			if (Settings::Combat::Aimbot::IgnoreWounded)
			{
				if (strstr(SelectedOptions.c_str(), " "))
					SelectedOptions += ", ";
				SelectedOptions += "Wounded";
			}
			if (Settings::Combat::Aimbot::IgnoreNPCs)
			{
				if (strstr(SelectedOptions.c_str(), " "))
					SelectedOptions += ", ";
				SelectedOptions += "NPCs";
			}

			if (!strstr(SelectedOptions.c_str(), " "))
			{
				SelectedOptions += " None";
			}

			if (ImGui::BeginCombo("Ignore List", SelectedOptions.c_str()))
			{
				ImGui::Checkbox("Players", &Settings::Combat::Aimbot::IgnorePlayers);
				ImGui::Checkbox("Sleeping Players", &Settings::Combat::Aimbot::IgnoreSleepers);
				ImGui::Checkbox("Wounded Players", &Settings::Combat::Aimbot::IgnoreWounded);
				ImGui::Checkbox("NPCs", &Settings::Combat::Aimbot::IgnoreNPCs);
				ImGui::EndCombo();
			}
			ImGui::EndChild();
		}
		break;
	case 1:
		ImGui::BeginChild("Silent", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
		{
			ImGui::Checkbox("Silent Aim", &Settings::Combat::Silent::Silent); ImGui::SameLine(); Menu::Hotkey("", &Globals::Hotkeys::hotkey_SilentKey, ImVec2{ 100, 20 }); ImGui::SameLine(); HelpMarker("You don't have to aim at enemies to be able to hit them");
			if (Settings::Combat::Silent::Silent) {
				ImGui::Checkbox("Draw FOV", &Settings::Combat::Silent::DrawSilent); ImGui::SameLine(); HelpMarker("Draws Silent Aim Field Of View");
				ImGui::Checkbox("Auto Shoot", &Settings::Combat::Silent::AutoShoot); ImGui::SameLine(); HelpMarker("Shoots if silent aim has a target");
				ImGui::SliderFloat("Silent Fov", &Settings::Combat::Silent::SilentFOV, 0.f, 500.f);
			}
			std::string SelectedOptions;

			SelectedOptions = "Ignoring";

			if (Settings::Combat::Silent::IgnorePlayers)
			{
				SelectedOptions += " Players";
			}
			if (Settings::Combat::Silent::IgnoreSleepers)
			{
				if (strstr(SelectedOptions.c_str(), " "))
					SelectedOptions += ", ";
				SelectedOptions += "Sleepers";
			}
			if (Settings::Combat::Silent::IgnoreWounded)
			{
				if (strstr(SelectedOptions.c_str(), " "))
					SelectedOptions += ", ";
				SelectedOptions += "Wounded";
			}
			if (Settings::Combat::Silent::IgnoreNPCs)
			{
				if (strstr(SelectedOptions.c_str(), " "))
					SelectedOptions += ", ";
				SelectedOptions += "NPCs";
			}

			if (!strstr(SelectedOptions.c_str(), " "))
			{
				SelectedOptions += " None";
			}

			if (ImGui::BeginCombo("Ignore List", SelectedOptions.c_str()))
			{
				ImGui::Checkbox("Players", &Settings::Combat::Silent::IgnorePlayers);
				ImGui::Checkbox("Sleeping Players", &Settings::Combat::Silent::IgnoreSleepers);
				ImGui::Checkbox("Wounded Players", &Settings::Combat::Silent::IgnoreWounded);
				ImGui::Checkbox("NPCs", &Settings::Combat::Silent::IgnoreNPCs);
				ImGui::EndCombo();
			}
			ImGui::EndChild();
		}
		break;
	case 2:
		ImGui::BeginChild("WeaponCase", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
		ImGui::BeginColumns("Text", 2, ImGuiColumnsFlags_::ImGuiColumnsFlags_NoResize);
		ImGui::SliderFloat("Recoil", &Settings::Combat::WeaponMods::Recoil, 0.f, 100.f);
		ImGui::SliderFloat("Spread", &Settings::Combat::WeaponMods::Spread, 0.f, 100.f); 
		ImGui::SliderFloat("Sway", &Settings::Combat::WeaponMods::Sway, 0.f, 100.f);
		ImGui::SliderFloat("Firerate", &Settings::Combat::WeaponMods::FireRate, 100.f, 200.f);
		ImGui::SliderFloat("Thickness", &Settings::Combat::WeaponMods::Thickness, 0.1f, 1.f);
		ImGui::SliderFloat("Bullet Speed", &Settings::Combat::WeaponMods::FastBulletSpeed, 1.0f, 1.5f);
		ImGui::NextColumn();
		ImGui::Checkbox("Instant Eoka", &Settings::Combat::WeaponMods::InstantEoka); 
		ImGui::Checkbox("Reload Indicator", &Settings::Misc::Reloadindicator); 
		ImGui::Checkbox("Auto Reload", &Settings::Combat::WeaponMods::AutoReload); 
		ImGui::Checkbox("Full Auto", &Settings::Combat::WeaponMods::Automatic); 
		ImGui::Checkbox("Penetrate", &Settings::Combat::WeaponMods::Penetrate); 
		ImGui::Checkbox("Weapon Spam", &Settings::Combat::WeaponMods::Spam); 
		if (Settings::Combat::WeaponMods::Spam)
		{
			if (!Settings::Combat::WeaponMods::AlwaysSpam)
			{
				ImGui::SameLine(); Menu::Hotkey("", &Globals::Hotkeys::hotkey_SpamKey, ImVec2{ 200, 20 });
			}
			ImGui::Checkbox("Always On", &Settings::Combat::WeaponMods::AlwaysSpam);
			ImGui::SliderFloat("Spam Rate", &Settings::Combat::WeaponMods::SpamRate, 1.f, 30.f);
		}
		ImGui::Checkbox("Override Kill Distance", &Settings::Combat::WeaponMods::OVDist);
		if (Settings::Combat::WeaponMods::OVDist)
			ImGui::SliderFloat("Distance", &Settings::Combat::WeaponMods::OVDistance, 1337.f, 7777.f); ImGui::SameLine(); HelpMarker("Spoofs the distance of hits/kills");

		ImGui::Checkbox("Override Hitbox", &Settings::Combat::WeaponMods::OVHitbox);
		if (Settings::Combat::WeaponMods::OVHitbox) {
			ImGui::Combo("Hitbox", &Menu::currentHitbox, "Head\0Chest\0Stomach\0R_Leg\0L_Leg\0R_Arm\0L_Arm");
			switch (Menu::currentHitbox)
			{
			case 0:
				Settings::Combat::WeaponMods::OVHit = BoneHitbox::hhead;
				break;
			case 1:
				Settings::Combat::WeaponMods::OVHit = BoneHitbox::cchest;
				break;
			case 2:
				Settings::Combat::WeaponMods::OVHit = BoneHitbox::sstomach;
				break;
			case 3:
				Settings::Combat::WeaponMods::OVHit = BoneHitbox::rleg;
				break;
			case 4:
				Settings::Combat::WeaponMods::OVHit = BoneHitbox::lleg;
				break;
			case 5:
				Settings::Combat::WeaponMods::OVHit = BoneHitbox::rhand;
				break;
			case 6:
				Settings::Combat::WeaponMods::OVHit = BoneHitbox::lhand;
				break;
			case 7:
				Settings::Combat::WeaponMods::OVHit = BoneHitbox::lhand, BoneHitbox::rhand, BoneHitbox::lleg, BoneHitbox::rleg;
				break;
			}
		}
		ImGui::EndColumns();
		ImGui::EndChild();
		break;
	case 3:
		ImGui::BeginChild("Rage", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
		{
			ImGui::Checkbox(("Desync"), &Settings::Combat::Rage::Desync); ImGui::SameLine(); HelpMarker("Desync's you from the server to allow multiple exploits");
			ImGui::Checkbox(("Show Desync Amount"), &Settings::Combat::Rage::ShowDesync); ImGui::SameLine(); HelpMarker("Shows the amount you have desynced so far");
			Menu::Hotkey("Desync Key  ", &Settings::Combat::Rage::DesyncKey, ImVec2{ 200, 20 }); ImGui::SameLine(); HelpMarker("Desync Key");
			if (Settings::Combat::Rage::Desync)
			{
				ImGui::Checkbox(("Instant Shoot"), &Settings::Combat::Rage::InstantShoot); ImGui::SameLine(); HelpMarker("Allows you to shoot multiple projectiles within the same frame, after desyncing");
				ImGui::Checkbox(("Powershot"), &Settings::Combat::Rage::PowerShot); ImGui::SameLine(); HelpMarker("Waits for high desync amount to fire projectiles, allows you to kill players instantly with AK");
			}
			ImGui::EndChild();
		}
		break;
	}
}

void MiscTab() {
	static int page = 0;
	const char* tabs[] = { "Movement", "Visuals", "Other" };

	ImGui::BeginChild("Misc1", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
	{
		for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
		{
			if (page != i)
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
			else
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

			if (ImGui::Button(tabs[i], ImVec2(100, 0)))
			{
				page = i;
			}

			ImGui::PopStyleColor();
		}
		ImGui::EndChild();
	}

	ImGui::SameLine();

	switch (page)
	{
	case 0:
		ImGui::BeginChild("MovementCase", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
		ImGui::BeginColumns("Text4", 2, ImGuiColumnsFlags_::ImGuiColumnsFlags_NoResize);
		ImGui::Checkbox("Omni-Directional Sprint", &Settings::Misc::OmniSprint); ImGui::SameLine(); HelpMarker("You can run sideways when this option is enabled");
		ImGui::Checkbox("Can Attack Always", &Settings::Misc::CanAttack); ImGui::SameLine(); HelpMarker("It makes you able to jump while shooting");
		ImGui::Checkbox("Walk On Water", &Settings::Misc::WalkOnWater); 
		ImGui::Checkbox("Walk Through Players", &Settings::Misc::WalkThroughPlayers);
		ImGui::Checkbox("Walk Through Trees", &Settings::Misc::WalkThroughTrees); 
		ImGui::Checkbox("No Fall Damage", &Settings::Misc::NoFallDamage); 
		ImGui::Checkbox("Silent Walk", &Settings::Misc::SilentWalk); ImGui::SameLine(); HelpMarker("Walk silently, pair with attack anywhere and you can shoot aswell");
		ImGui::Checkbox("Infinite Jump", &Settings::Misc::InfJump); 
		ImGui::Checkbox("High Jump", &Settings::Misc::JumpHigh);
		ImGui::NextColumn();


		ImGui::EndColumns();
		ImGui::EndChild();
		break;
	case 1:
		ImGui::BeginChild("VisualsCase", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
		ImGui::BeginColumns("Text2", 2, ImGuiColumnsFlags_::ImGuiColumnsFlags_NoResize);
		ImGui::Checkbox("No Weapon Bobing", &Settings::Misc::NoBobbing); ImGui::SameLine(); HelpMarker("Makes weapon not bob when moving");
		ImGui::Checkbox("No Weapon Lowering", &Settings::Misc::NoLowering); ImGui::SameLine(); HelpMarker("Removes weapon lowering animation while sprinting");
		ImGui::Checkbox("No Weapon Lerping", &Settings::Misc::NoSwaying); ImGui::SameLine(); HelpMarker("Removes weapon movement animation when moving camera around");
		ImGui::Checkbox("No Firing Animation", &Settings::Combat::WeaponMods::NoAttackAnimation); ImGui::SameLine(); HelpMarker("Remove weapon firing animation");

		ImGui::NextColumn();

		ImGui::Combo("Crosshair", &Menu::currentCrosshair, "None\0Cross\0X\0Circle\0Custom");
		if (Menu::currentCrosshair != 0)
			ImGui::SliderInt("Size", &Settings::Misc::CrosshairSize, 1, 60);

		if (Menu::currentCrosshair == 4)
		{
			ImGui::SliderInt("Gap", &Settings::Misc::CrosshairGap, 1, 60);
			ImGui::SliderInt("Thickness", &Settings::Misc::CrosshairThickness, 1, 60);
		}
		ImGui::EndColumns();
		ImGui::EndChild();
		break;
	case 2:
		ImGui::BeginChild("OthersCase", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
		ImGui::BeginColumns("Text1", 2, ImGuiColumnsFlags_::ImGuiColumnsFlags_NoResize);
		ImGui::Checkbox("Fake Admin", &Settings::Misc::FakeAdmin); ImGui::SameLine(); HelpMarker("Force Admin Permissions");
		ImGui::Checkbox("Suicide", &Settings::Misc::Suicide); ImGui::SameLine(); HelpMarker("Makes you take fall damage so you kill yourself");
		if (Settings::Misc::Suicide)
		{
			if (!Settings::Misc::AlwaysSuicide)
			{
				ImGui::SameLine(); Menu::Hotkey("", &Globals::Hotkeys::hotkey_SuicideKey, ImVec2{ 200, 20 });
			}
			ImGui::Checkbox("Always On", &Settings::Misc::AlwaysSuicide);
			ImGui::SliderFloat("Suicide Rate", &Settings::Misc::SuicideRate, 1.f, 30.f);
		}

		ImGui::NextColumn();
		Menu::RenderConfig();
		ImGui::EndColumns();;
		ImGui::EndChild();
		break;
	}
}

void ColorsTab()
{
	//Vars::Color
	ImGui::BeginChild("ColorsTab1", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);

	ImGui::ColorEdit4("Text Visible Color", Settings::Visuals::Players::Colors::Visible, ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_::ImGuiColorEditFlags_NoInputs);
	ImGui::ColorEdit4("Text Visible Non-Visible Color", Settings::Visuals::Players::Colors::InVisible, ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_::ImGuiColorEditFlags_NoInputs);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::ColorEdit4("Chams Visible Color", Settings::Visuals::Players::Colors::VisibleChams, ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_::ImGuiColorEditFlags_NoInputs);
	ImGui::ColorEdit4("Chams Non-Visible Color", Settings::Visuals::Players::Colors::InVisibleChams, ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_::ImGuiColorEditFlags_NoInputs);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::ColorEdit4("Wire-frame Color", Settings::Visuals::Players::Colors::VisibleChams, ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_::ImGuiColorEditFlags_NoInputs);
	ImGui::EndChild();
}

void VisualsTab()
{
	static int page = 0;
	const char* tabs[] = { "Players", "Scientist", "Resources", "Collectibles", "Animals", "Vehicles", "Traps", "World", "Construction" };

	ImGui::BeginChild("Visuals1", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
	{
		for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
		{
			if (page != i)
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
			else
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

			if (ImGui::Button(tabs[i], ImVec2(100, 0)))
			{
				page = i;
			}

			ImGui::PopStyleColor();
		}
		ImGui::EndChild();
	}

	ImGui::SameLine();

	switch (page)
	{
	case 0:
		ImGui::BeginChild("VisualsCase0", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
		{
			ImGui::BeginColumns("Text", 2, ImGuiColumnsFlags_::ImGuiColumnsFlags_NoResize);
			ImGui::Checkbox("Show Players", &Settings::Visuals::Players::Players);
			ImGui::Checkbox("Show Sleeping Players", &Settings::Visuals::Players::Sleepers);
			ImGui::Checkbox("Show Wounded Players", &Settings::Visuals::Players::Wounded);
			//ImGui::Checkbox("Show Scientists", &Settings::Visuals::Players::NPC);
			ImGui::Checkbox("Name", &Settings::Visuals::Players::Name);
			ImGui::Checkbox("Health", &Settings::Visuals::Players::Health);
			ImGui::Checkbox("Distance", &Settings::Visuals::Players::Distance);
			ImGui::Checkbox("Weapon", &Settings::Visuals::Players::HeldItem);
			ImGui::NextColumn();
			ImGui::Checkbox("Corner Box", &Settings::Visuals::Players::CornerBox);
			ImGui::Checkbox("Skeleton", &Settings::Visuals::Players::Skeleton);
			ImGui::Checkbox("Snaplines", &Settings::Visuals::Players::Snaplines);
			ImGui::Checkbox("Healthbar", &Settings::Visuals::Players::HealthBar);
			ImGui::Checkbox("Offscreen Indicator", &Settings::Visuals::Players::OffscreenIndicators); ImGui::SameLine(); HelpMarker("Arrows point towards people that are out of your line of sight.");
			ImGui::Checkbox("Chams", &Settings::Visuals::Players::Chams);
			if (Settings::Visuals::Players::Chams)
			{
				ImGui::Combo("Cham Type", &Menu::currentCham, "Flat\0Xray\0Wireframe\0Chamslit");
				ImGui::Checkbox("Occlude Chams", &Settings::Visuals::Players::VisibleOnly); ImGui::SameLine(); HelpMarker("Only shows cham shader if the player is not occluded.");
				if (Menu::currentCham != 1)
					ImGui::Checkbox("Health Based Coloring", &Settings::Visuals::Players::HealthChams);
				if (Menu::currentCham == 2)
					ImGui::SliderInt("Wire Thickness", &Settings::Visuals::Players::WireThickness, 0, 800);
			}
			ImGui::EndColumns();
			ImGui::EndChild();
		}
		break;
	case 1:
		ImGui::BeginChild("ScientistCase0", ImVec2(0, 0), true, ImGuiWindowFlags_NoResize);
		{
			ImGui::BeginColumns("Texts", 2, ImGuiColumnsFlags_::ImGuiColumnsFlags_NoResize);
			ImGui::Checkbox("[S] Show Scientist", &Settings::Visuals::Players::NPC);
			ImGui::Checkbox("[S] Name", &Settings::Scientist::Name);
			ImGui::Checkbox("[S] Distance", &Settings::Scientist::Distance);
			ImGui::Checkbox("[S] Health", &Settings::Scientist::Health);
			ImGui::Checkbox("[S] Weapon", &Settings::Scientist::HeldItem);
			ImGui::NextColumn();
			ImGui::Checkbox("[S] Skeleton", &Settings::Scientist::Skeleton);
			ImGui::Checkbox("[S] Corner Box", &Settings::Scientist::CornerBox);
			ImGui::Checkbox("[S] Health Bar", &Settings::Scientist::HealthBar);
			ImGui::Checkbox("[S] Snaplines", &Settings::Scientist::Snaplines);

			ImGui::EndColumns();
			ImGui::EndChild();
		}
		break;
	case 2:
		ResourcesSubTab();
		break;
	case 3:
		CollectiblesSubTab();
		break;
	case 4:
		AnimalsSubTab();
		break;
	case 5:
		VehiclesSubTab();
		break;
	case 6:
		TrapsSubTab();
	case 7:
		WorldSubTab();
		break;
	case 8:
		ConstructionSubTab();
		break;
	}
}

void Menu::MainMenu()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.43f, 0.02f, 0.04f, 1.f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.58f, 0.00f, 0.03f, 0.85f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.58f, 0.00f, 0.03f, 0.85f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.29f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.24f, 0.24f, 0.29f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.58f, 0.00f, 0.03f, 0.85f);

	ImGui::SetNextWindowSize(ImVec2(800, 400), ImGuiCond_::ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Last Cheat Rust", (bool*)0, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize) && !ImGui::IsWindowCollapsed())
	{
		static int page = 0;
		const char* tabs[] = {
			"Visuals",
			"Combat",
			"Misc",
			"Colors"
		};

		ImGui::BeginChild("Main1", ImVec2(115, 0), true, ImGuiWindowFlags_NoResize);
		{
			for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
			{
				if (page != i)
					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));//Non Selected Tab
				else
					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.58f, 0.00f, 0.03f, 0.70f));//Selected Tab

				if (ImGui::Button(tabs[i], ImVec2(100, 0)))
				{
					page = i;
				}

				ImGui::PopStyleColor();
			}
			ImGui::EndChild();
		}

		ImGui::SameLine();

		switch (page)
		{
		case 0:
			VisualsTab();
			break;
		case 1:
			CombatTab();
			break;
		case 2:
			MiscTab();
			break;
		case 3:
			ColorsTab();
			break;
		}
	}
	ImGui::End();
}

void LoadPrefabs()
{
	static bool alreadyLoaded = false;
	if (alreadyLoaded) return;
	Settings::AddESPObject("Cloth", "hemp-collectable", "Hemp", false);
	Settings::AddESPObject("Cloth", "hemp.entity", "Planted Hemp", false);
	Settings::AddESPObject("Crops", "mushroom", "Mushroom", false);
	Settings::AddESPObject("Crops", "cactus", "Cactus", false);
	Settings::AddESPObject("Crops", "potato-collectable", "Potato", false);
	Settings::AddESPObject("Crops", "corn-collectable", "Corn", false);
	Settings::AddESPObject("Crops", "pumpkin-collectable", "Pumpkin", false);
	Settings::AddESPObject("Crops", "potato.entity", "Planted Potato", false);
	Settings::AddESPObject("Crops", "corn.entity", "Planted Corn", false);
	Settings::AddESPObject("Crops", "pumpkin.entity", "Planted Pumpkin", false);
	Settings::AddESPObject("Berries", "berry-black-coll", "Black Berry", false);
	Settings::AddESPObject("Berries", "berry-blue-coll", "Blue Berry", false);
	Settings::AddESPObject("Berries", "berry-green-coll", "Green Berry", false);
	Settings::AddESPObject("Berries", "berry-white-coll", "White Berry", false);
	Settings::AddESPObject("Berries", "berry-red-coll", "Red Berry", false);
	Settings::AddESPObject("Berries", "berry-yellow-coll", "Yellow Berry", false);
	Settings::AddESPObject("Berries", "black_berry.entity", "Planted Black Berry", false);
	Settings::AddESPObject("Berries", "blue_berry.entity", "Planted Blue Berry", false);
	Settings::AddESPObject("Berries", "green_berry.entity", "Planted Green Berry", false);
	Settings::AddESPObject("Berries", "white_berry.entity", "Planted White Berry", false);
	Settings::AddESPObject("Berries", "red_berry.entity", "Planted Red Berry", false);
	Settings::AddESPObject("Berries", "yellow_berry.entity", "Planted Yellow Berry", false);
	Settings::AddESPObject("PickupOre", "stone-collectable.prefab", "Stone", false);
	Settings::AddESPObject("PickupOre", "metal-collectable.prefab", "Metal", false);
	Settings::AddESPObject("PickupOre", "sulfur-collectable.prefab", "Sulfur", false);
	Settings::AddESPObject("Construction", "loot-barrel-1.prefab", "Gray Barrel", false);
	Settings::AddESPObject("Construction", "loot-barrel-2.prefab", "Blue Barrel", false);
	Settings::AddESPObject("Construction", "crate_basic.prefab", "Basic Crate", false);
	Settings::AddESPObject("Construction", "crate_normal.prefab", "Normal Crate", false);
	Settings::AddESPObject("Construction", "crate_elite.prefab", "Elite Crate", false);
	Settings::AddESPObject("World", "(world)", "Dropped Item", false);
	Settings::AddESPObject("Traps", "flameturret.deployed.prefab", "Flame Turret", false);
	Settings::AddESPObject("Traps", "guntrap.deployed.prefab.prefab", "Shotgun Trap", false);
	Settings::AddESPObject("Traps", "autoturret_deployed.prefab", "Auto Turret", false);
	Settings::AddESPObject("Traps", "sam_site_turret_deployed.prefab", "Air Turret", false);
	Settings::AddESPObject("Traps", "spikes.floor.prefab", "Spikes", false);
	Settings::AddESPObject("Traps", "beartrap.prefab", "Bear Trap", false);
	Settings::AddESPObject("Traps", "landmine.prefab", "Landmine", false);
	Settings::AddESPObject("Vehicles", "bradley", "Bradley", false);
	Settings::AddESPObject("Vehicles", "patrolhelicopter.prefab", "Patrol Helicopter", false);
	Settings::AddESPObject("Vehicles", "kayak.prefab", "Kayak", false);
	Settings::AddESPObject("Vehicles", "rhib.prefab", "Military Boat", false);
	Settings::AddESPObject("Vehicles", "rowboat.prefab", "Boat", false);
	Settings::AddESPObject("Vehicles", "minicopter.entity.prefab", "Minicopter", false);
	Settings::AddESPObject("Vehicles", "scraptransporthelicopter.prefab", "Transport Helicopter", false);
	Settings::AddESPObject("Vehicles", "ch47.entity.prefab", "Chinook Helicopter", false);
	Settings::AddESPObject("Animals", "wolf.prefab", "Wolf", false);
	Settings::AddESPObject("Animals", "boar.prefab", "Boar", false);
	Settings::AddESPObject("Animals", "bear.prefab", "Bear", false);
	Settings::AddESPObject("Animals", "horse.prefab", "Horse", false);
	Settings::AddESPObject("Animals", "chicken.prefab", "Chicken", false);
	Settings::AddESPObject("Animals", "shark.prefab", "Shark", false);
	Settings::AddESPObject("Animals", "deer.prefab", "Deer", false);
	Settings::AddESPObject("Resources", "stone-ore.prefab", "Stone Ore", false);
	Settings::AddESPObject("Resources", "metal-ore.prefab", "Metal Ore", false);
	Settings::AddESPObject("Resources", "sulfur-ore.prefab", "Sulfur Ore", false);
	alreadyLoaded = true;
}

void SaveDefaultConfig()
{
	size_t sz = 0;
	char* buf = nullptr;
	std::string lcDirectory;

	if (_dupenv_s(&buf, &sz, "APPDATA") == 0 && buf != nullptr)
	{
		lcDirectory = std::string(buf) + "\\LCSSD\\";

		if (!std::filesystem::exists(lcDirectory))
		{
			std::filesystem::create_directory(lcDirectory);
		}

		lcDirectory += "RUST\\";

		free(buf);
	}
	else
	{
		Ulog("APPDATA does not exist in environment."); return;
	}

	if (std::filesystem::exists(lcDirectory))
	{
		if (!std::filesystem::exists(lcDirectory + std::string("Default.json")))
		{
			Settings::SaveSettings(lcDirectory + "Default.json");
		}
	}
	else
	{
		Ulog("Creating directory...");
		std::filesystem::create_directory(lcDirectory);
	}
}

ImFont* espFont;
ImFont* defaultFont;

void Menu::Wrapper(void* swapChain)
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		if (!Globals::Window::pChain)
		{
			if (!InitializeMenu((IDXGISwapChain*)swapChain))
			{
				Ulog("%s - Failed to initialize Menu.", __FUNCTION__);
				return;
			}
		}

		ImGui::GetIO().IniFilename = "rust.temp";
		ImGui::GetIO().IniSavingRate = 99999999999999.f;
		ImGui::GetIO().WantSaveIniSettings = false;// = "my_config.ini"

		ImGui_ImplDX11_NewFrame(); ImGui_ImplWin32_NewFrame(); ImGui::NewFrame();

		LoadPrefabs();
		SaveDefaultConfig();

		if (Globals::Ready)
		{
			if (Vars::Global::ScreenHigh != 0 && Vars::Global::ScreenWidth != 0)
			{
				ImGui::PushFont(espFont);
				__try
				{
					Visuals::DrawESP();
				}
				__except ([](unsigned int code, struct _EXCEPTION_POINTERS* ep) -> int
					{
						Ulog("ESP - Exception happened in (%s) with code %lx - at RIP %p | %p ", __FUNCTION__,
							code, ep->ExceptionRecord->ExceptionAddress, Globals::g_Module);

						return EXCEPTION_EXECUTE_HANDLER;
					}(GetExceptionCode(), GetExceptionInformation())) {
				}

				if (Globals::Settings::g_bMenu) Menu::MainMenu();
				ImGui::PopFont();
			}
		}

		ImGui::EndFrame();
		ImGui::Render();
		Globals::Window::pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		Vars::Global::ScreenHigh = ImGui::GetDrawData()->DisplaySize.y;
		Vars::Global::ScreenWidth = ImGui::GetDrawData()->DisplaySize.x;
	}
	__except (
		ExceptionCode = GetExceptionCode(),
		ExceptionPointers = GetExceptionInformation(),
		EXCEPTION_EXECUTE_HANDLER
		) {
		if (ExceptionPointers)
		{
			Ulog("Exception (%lx) caught in %s @ (%p). Base (%p) - (%p)",
				ExceptionCode, __FUNCTION__,
				ExceptionPointers->ExceptionRecord->ExceptionAddress, Globals::g_GameAssemblyBase, Globals::g_Module
			);
		}
	}
}

/**********************************************************************************************************************/
/***************************************************** [ INTERNALS ] **************************************************/
/**********************************************************************************************************************/

HRESULT GetDeviceAndCtxFromSwapchain(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext)
{
	HRESULT ret = pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)ppDevice);

	if (SUCCEEDED(ret))
		(*ppDevice)->GetImmediateContext(ppContext);

	return ret;
}

bool Menu::InitializeMenu(IDXGISwapChain* ptr_SwapChain)
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		Globals::Window::pChain = ptr_SwapChain;
		mainRenderTargetView = NULL;
		pImGuiContext = NULL;

		HRESULT result = GetDeviceAndCtxFromSwapchain(Globals::Window::pChain, &Globals::Window::pDevice, &Globals::Window::pContext);
		if (FAILED(result))
		{
			Ulog("%s - GetDeviceAndCtxFromSwapchain failed with HRESULT (%x) pChain reset (%p)", __FUNCTION__, result, Globals::Window::pChain = 0);
			return false;
		}

		DXGI_SWAP_CHAIN_DESC sd;
		Globals::Window::pChain->GetDesc(&sd);
		pImGuiContext = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.MouseDrawCursor = false;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NoMouse;

		Globals::Window::GameWindow = sd.OutputWindow;
		ImGui_ImplWin32_Init(Globals::Window::GameWindow);
		ImGui_ImplDX11_Init(Globals::Window::pDevice, Globals::Window::pContext);
		ImGui::GetIO().ImeWindowHandle = Globals::Window::GameWindow;

		unsigned char* pixels;
		int width, height, bytes_per_pixel;
		defaultFont = io.Fonts->AddFontDefault();
		espFont = io.Fonts->AddFontFromFileTTF("RobotoCondensed-Bold.ttf", 16.0f);
		io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height, &bytes_per_pixel);
		io.Fonts->Build();

		ID3D11Texture2D* pBackBuffer = 0;

		Globals::Window::pChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		if (pBackBuffer)
		{
			Globals::Window::pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
		}

		Settings::LoadSettingsChar("Default");

		return true;
	}
	__except (
		ExceptionCode = GetExceptionCode(),
		ExceptionPointers = GetExceptionInformation(),
		EXCEPTION_EXECUTE_HANDLER
		) {
		if (ExceptionPointers)
		{
			Ulog("Exception (%lx) caught in %s @ (%p). Base (%p) - (%p)",
				ExceptionCode, __FUNCTION__,
				ExceptionPointers->ExceptionRecord->ExceptionAddress, Globals::g_GameAssemblyBase, Globals::g_Module
			);
		}
	}
	return false;
}

ImVec2 ImVecAdd(ImVec2 vec1, ImVec2 vec2)
{
	return { vec1.x + vec2.x, vec1.y + vec2.y };
}

ImVec2 ImVecSubtract(ImVec2 vec1, ImVec2 vec2)
{
	return { vec1.x - vec2.x, vec1.y - vec2.y };
}

bool Menu::Hotkey(const char* label, int* k, const ImVec2& size_arg)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);
	const ImRect frame_bb(ImVecAdd(window->DC.CursorPos, ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f)), ImVecAdd(window->DC.CursorPos, size));
	const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);
	//const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
	//const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);

	if (hovered)
	{
		ImGui::SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool user_clicked = hovered && io.MouseClicked[0];

	if (focus_requested || user_clicked)
	{
		if (g.ActiveId != id)
		{
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			*k = 0;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0])
	{
		// Release focus when we click outside
		if (g.ActiveId == id)
			ImGui::ClearActiveID();
	}

	bool value_changed = false;
	int key = *k;

	if (g.ActiveId == id)
	{
		for (auto i = 0; i < 5; i++)
		{
			if (io.MouseDown[i])
			{
				switch (i)
				{
				case 0:
					key = VK_LBUTTON;
					break;
				case 1:
					key = VK_RBUTTON;
					break;
				case 2:
					key = VK_MBUTTON;
					break;
				case 3:
					key = VK_XBUTTON1;
					break;
				case 4:
					key = VK_XBUTTON2;
					break;
				}
				value_changed = true;
				ImGui::ClearActiveID();
			}
		}
		if (!value_changed)
		{
			for (auto i = VK_BACK; i <= VK_RMENU; i++)
			{
				if (io.KeysDown[i])
				{
					key = i;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (ImGui::IsKeyPressedMap(ImGuiKey_Escape))
		{
			*k = 0;
			ImGui::ClearActiveID();
		}
		else
		{
			*k = key;
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

	char buf_display[64] = "None";

	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), true, style.FrameRounding);

	if (*k != 0 && g.ActiveId != id)
	{
		if (*k > 210)
		{
			strcpy_s(buf_display, "Invalid Key");
		}
		else
		{
			strcpy_s(buf_display, Menu::KeyNames[*k]);
		}
	}
	else if (g.ActiveId == id)
	{
		strcpy_s(buf_display, "<Press a key>");
	}

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = ImVecAdd(frame_bb.Min, style.FramePadding);

	ImGui::RenderTextClipped(ImVecAdd(frame_bb.Min, style.FramePadding), ImVecSubtract(frame_bb.Max, style.FramePadding), buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);

	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(total_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), label);

	return value_changed;
}

char pendingSettingsName[0x100];
bool bPendingSettingsSave = false;
void Menu::RenderConfig()
{
	ImGui::Text("Settings Configuration");

	size_t sz = 0;
	char* buf = nullptr;
	std::string lcDirectory;

	if (_dupenv_s(&buf, &sz, "APPDATA") == 0 && buf != nullptr)
	{
		lcDirectory = std::string(buf) + "\\LCSSD\\";

		if (!std::filesystem::exists(lcDirectory))
		{
			std::filesystem::create_directory(lcDirectory);
		}

		lcDirectory += "RUST\\";

		free(buf);
	}
	else
	{
		Ulog("APPDATA does not exist in environment."); return;
	}

	if (std::filesystem::exists(lcDirectory))
	{
		if (!std::filesystem::exists(lcDirectory + std::string("Default.json")))
		{
			Settings::SaveSettings(lcDirectory + "Default.json");
		}

		for (auto& p : std::filesystem::directory_iterator(lcDirectory))
		{
			auto path = p.path().generic_string();
			auto fileName = path.substr(path.find_last_of("/\\") + 1);
			std::string::size_type const p(fileName.find_last_of('.'));
			fileName = fileName.substr(0, p);

			bool hasNameBeenAdded = false;
			for (auto name : Globals::Settings::ConfigList)
			{
				if (strcmp(name.data(), fileName.c_str()) == 0)
				{
					hasNameBeenAdded = true;
				}
			}

			if (!hasNameBeenAdded)
			{
				Globals::Settings::ConfigList.push_back(fileName);
			}
		}

		ImGui::SetNextItemWidth(130);
		if (ImGui::BeginCombo("Setting Profiles", Globals::Settings::currentConfig.data()))
		{
			for (auto config : Globals::Settings::ConfigList)
			{
				bool is_selected = (config == Globals::Settings::currentConfig);
				if (ImGui::Selectable(config.data(), is_selected))
				{
					Globals::Settings::currentConfig = config;
					Settings::LoadSettings(config);
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}
	}
	else
	{
		Ulog("Creating directory...");
		std::filesystem::create_directory(lcDirectory);
	}

	if (bPendingSettingsSave)
	{
		ImGui::SetNextItemWidth(130);
		ImGui::InputText("Config Name", pendingSettingsName, IM_ARRAYSIZE(pendingSettingsName));
	}

	if (bPendingSettingsSave)
	{
		if (ImGui::Button("Confirm Save Config"))
		{
			bPendingSettingsSave = false;
			Settings::SaveSettings(lcDirectory + std::string(pendingSettingsName) + ".json");
			memset(pendingSettingsName, 0, 16);
		}
	}
	else
	{
		if (ImGui::Button("Save Config"))
		{
			bPendingSettingsSave = true;
		}

		ImGui::SameLine();

		if (ImGui::Button("Delete Config"))
		{
			Ulog("Deleting current Config = %s", Globals::Settings::currentConfig.data());

			if (DeleteFileA((lcDirectory + Globals::Settings::currentConfig + ".json").data()))
			{
				auto itr = std::find(Globals::Settings::ConfigList.begin(), Globals::Settings::ConfigList.end(), Globals::Settings::currentConfig);
				if (itr != Globals::Settings::ConfigList.end()) Globals::Settings::ConfigList.erase(itr);

				Globals::Settings::currentConfig = "DELETED";
			}
		}
	}
}