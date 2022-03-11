#pragma once
#include "pch.h"
float timeBefore;
Vector3 LocalPosition;
Quaternion LocalRotation;
Item heldEntity;
Vector3 beforeInvalid = Vector3().Zero();

bool Entity::isPlayer(char* EntityClassName)
{
	bool validPlayer = false;
	if (strstr(EntityClassName, "Corpse"))
		validPlayer = false;
	else if (strstr(EntityClassName, "BasePlayer"))
		return true;// Settings::Visuals::Players::Players;
	else if (strstr(EntityClassName, "BanditGuard"))
		validPlayer = true;
	else if (strstr(EntityClassName, "UnderwaterDweller"))
		validPlayer = true;
	else if (strstr(EntityClassName, "TunnelDweller"))
		validPlayer = true;
	else if (strstr(EntityClassName, "ScientistNPCNew"))
		validPlayer = true;
	else if (strstr(EntityClassName, "HumanNPCNew"))
		validPlayer = true;
	else if (strstr(EntityClassName, "HTNPlayer"))
		validPlayer = true;
	else if (strstr(EntityClassName, "Scientist"))
		validPlayer = true;
	else if (strstr(EntityClassName, "NPCPlayer"))
		validPlayer = true;
	else if (strstr(EntityClassName, "HumanNPC"))
		validPlayer = true;
	else if (strstr(EntityClassName, "NPCMurderer"))
		validPlayer = true;
	else if (strstr(EntityClassName, "NPCPlayerApex"))
		validPlayer = true;
	else if (strstr(EntityClassName, "HeavyScientist"))
		validPlayer = true;
	if (validPlayer)
	{
		return true;// Settings::Visuals::Players::NPC;
	}
	else
	{
		return false;
	}
}

bool AreAllDataInitialized()
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;

	__try
	{
		// Making sure GlobalObjectManager is ready
		if (Globals::g_GlobalObjectManager &&
			Globals::g_GlobalObjectManager->pGlobalObjectManager->pListStart &&

			// Making sure the BaseNetworkable is ready
			Globals::g_BaseNetworkable &&
			Globals::g_BaseNetworkable->pBaseNetworkable &&
			Globals::g_BaseNetworkable->pBaseNetworkable->pEntityRealm &&
			Globals::g_BaseNetworkable->pBaseNetworkable->pEntityRealm->pClientEntities->pEntityList->pBufferListVals->BufferListCount)
		{
			return true;
		}
	}
	__except (
		ExceptionCode = GetExceptionCode(),
		ExceptionPointers = GetExceptionInformation(),
		EXCEPTION_EXECUTE_HANDLER
		) {
		if (ExceptionPointers)
		{
			Ulog("Exception (%lx) caught in %s @ (%p) (%llx)",
				ExceptionCode, __FUNCTION__,
				ExceptionPointers->ExceptionRecord->ExceptionAddress,
				Globals::g_GameAssemblyBase
			);
		}
	}
	return false;
}

class Text
{
public:
	Text(Vector3 pos, ImU32 col, std::string string)
	{
		this->Position = pos;
		this->Color = col;
		this->Input = string;
	}
	Vector3 Position;
	ImU32 Color;
	std::string Input;
};

std::list<Text> textList;
std::list<Text> temp_textList;
std::list<Text> g_textList;

class TextGroup
{
public:
	TextGroup(Vector3 pos)
	{
		this->textList = g_textList;
		this->Position = pos;
	}

	std::list<Text> textList;
	Vector3 Position;
};

std::list<TextGroup> textGroupList;
std::list<TextGroup> temp_textGroupList;

bool RefreshShaders = false;

void DrawBasePlayer(BasePlayer basePlayer)
{
	if (!((basePlayer.lifestate() == LifeState::Alive || basePlayer.health() >= 0.1f))) return;
	Vector3 position = basePlayer.get_transform().GetPosition();

	ImU32 color = ImColor(Settings::Visuals::Players::Colors::InVisible[0], Settings::Visuals::Players::Colors::InVisible[1], Settings::Visuals::Players::Colors::InVisible[2]);
	bool Visible = false;

	if (UnityEngine::LineOfSight(basePlayer.model.GetTransform(47).GetPosition(), LocalPlayer.Eyes.GetPosition(), 10551296))
	{
		color = ImColor(Settings::Visuals::Players::Colors::Visible[0], Settings::Visuals::Players::Colors::Visible[1], Settings::Visuals::Players::Colors::Visible[2]);
		Visible = true;
	}

	box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };

	BoneList Bones[15] = {
		l_foot, l_knee, l_hip,
		r_foot, r_knee, r_hip,
		spine1, neck, head,
		l_upperarm, l_forearm, l_hand,
		r_upperarm, r_forearm, r_hand
	};

	CornerBox cornerBox;

	for (int j = 0; j < 15; j++)
	{
		auto currentBoneV3 = basePlayer.model.GetTransform(BoneList(Bones[j])).GetPosition(); Vector2 bone_screen;
		if (Bones[j] == BoneList(head))
		{
			currentBoneV3.y += 0.2f;
		}
		else if (Bones[j] == BoneList(r_foot) || Bones[j] == BoneList(l_foot))
		{
			currentBoneV3.y -= 0.2f;
		}
		WorldToScreen(currentBoneV3, bone_screen);
		if (bone_screen.x < ret.left)
		{
			ret.left = bone_screen.x;
			cornerBox.left = currentBoneV3;
		}
		if (bone_screen.x > ret.right)
		{
			ret.right = bone_screen.x;
			cornerBox.right = currentBoneV3;
		}
		if (bone_screen.y < ret.top)
		{
			ret.top = bone_screen.y;
			cornerBox.top = currentBoneV3;
		}
		if (bone_screen.y > ret.bottom)
		{
			ret.bottom = bone_screen.y;
			cornerBox.bottom = currentBoneV3;
		}
	}

	if (ret.empty()) cornerBox.Valid = false;

	cornerBox.Color = color;

	temp_basePlayerVectorList.push_back(BasePlayerVectors(basePlayer, position, cornerBox, Visible));
	if (strstr(basePlayer.className, "BasePlayer") && Settings::Visuals::Players::Skeleton)
	{
		CreateBoneLine(BoneList(head), BoneList(neck), color, basePlayer);

		{
			CreateBoneLine(BoneList(neck), BoneList(l_clavicle), color, basePlayer);
			CreateBoneLine(BoneList(l_clavicle), BoneList(l_upperarm), color, basePlayer);
			CreateBoneLine(BoneList(l_upperarm), BoneList(l_forearm), color, basePlayer);
			CreateBoneLine(BoneList(l_forearm), BoneList(l_ulna), color, basePlayer);
			CreateBoneLine(BoneList(l_ulna), BoneList(l_hand), color, basePlayer);
			if (1 == 1)
			{
				CreateBoneLine(BoneList(l_hand), BoneList(l_index1), color, basePlayer);
				CreateBoneLine(BoneList(l_index1), BoneList(l_index2), color, basePlayer);
				CreateBoneLine(BoneList(l_index2), BoneList(l_index3), color, basePlayer);

				CreateBoneLine(BoneList(l_hand), BoneList(l_little1), color, basePlayer);
				CreateBoneLine(BoneList(l_little1), BoneList(l_little2), color, basePlayer);
				CreateBoneLine(BoneList(l_little2), BoneList(l_little3), color, basePlayer);

				CreateBoneLine(BoneList(l_hand), BoneList(l_middle1), color, basePlayer);
				CreateBoneLine(BoneList(l_middle1), BoneList(l_middle2), color, basePlayer);
				CreateBoneLine(BoneList(l_middle2), BoneList(l_middle3), color, basePlayer);

				CreateBoneLine(BoneList(l_hand), BoneList(l_ring1), color, basePlayer);
				CreateBoneLine(BoneList(l_ring1), BoneList(l_ring2), color, basePlayer);
				CreateBoneLine(BoneList(l_ring2), BoneList(l_ring3), color, basePlayer);

				CreateBoneLine(BoneList(l_hand), BoneList(l_thumb1), color, basePlayer);
				CreateBoneLine(BoneList(l_thumb1), BoneList(l_thumb2), color, basePlayer);
				CreateBoneLine(BoneList(l_thumb2), BoneList(l_thumb3), color, basePlayer);
			}
		}

		{
			CreateBoneLine(BoneList(neck), BoneList(r_clavicle), color, basePlayer);
			CreateBoneLine(BoneList(r_clavicle), BoneList(r_upperarm), color, basePlayer);
			CreateBoneLine(BoneList(r_upperarm), BoneList(r_forearm), color, basePlayer);
			CreateBoneLine(BoneList(r_forearm), BoneList(r_ulna), color, basePlayer);
			CreateBoneLine(BoneList(r_ulna), BoneList(r_hand), color, basePlayer);
			if (1 == 1)
			{
				CreateBoneLine(BoneList(r_hand), BoneList(r_index1), color, basePlayer);
				CreateBoneLine(BoneList(r_index1), BoneList(r_index2), color, basePlayer);
				CreateBoneLine(BoneList(r_index2), BoneList(r_index3), color, basePlayer);

				CreateBoneLine(BoneList(r_hand), BoneList(r_little1), color, basePlayer);
				CreateBoneLine(BoneList(r_little1), BoneList(r_little2), color, basePlayer);
				CreateBoneLine(BoneList(r_little2), BoneList(r_little3), color, basePlayer);

				CreateBoneLine(BoneList(r_hand), BoneList(r_middle1), color, basePlayer);
				CreateBoneLine(BoneList(r_middle1), BoneList(r_middle2), color, basePlayer);
				CreateBoneLine(BoneList(r_middle2), BoneList(r_middle3), color, basePlayer);

				CreateBoneLine(BoneList(r_hand), BoneList(r_ring1), color, basePlayer);
				CreateBoneLine(BoneList(r_ring1), BoneList(r_ring2), color, basePlayer);
				CreateBoneLine(BoneList(r_ring2), BoneList(r_ring3), color, basePlayer);

				CreateBoneLine(BoneList(r_hand), BoneList(r_thumb1), color, basePlayer);
				CreateBoneLine(BoneList(r_thumb1), BoneList(r_thumb2), color, basePlayer);
				CreateBoneLine(BoneList(r_thumb2), BoneList(r_thumb3), color, basePlayer);
			}
		}

		CreateBoneLine(BoneList(neck), BoneList(spine4), color, basePlayer);
		CreateBoneLine(BoneList(spine4), BoneList(spine3), color, basePlayer);
		CreateBoneLine(BoneList(spine3), BoneList(spine2), color, basePlayer);
		CreateBoneLine(BoneList(spine2), BoneList(spine1), color, basePlayer);
		{
			CreateBoneLine(BoneList(spine1), BoneList(l_hip), color, basePlayer);
			CreateBoneLine(BoneList(spine1), BoneList(l_hip), color, basePlayer);
			CreateBoneLine(BoneList(l_hip), BoneList(l_knee), color, basePlayer);
			CreateBoneLine(BoneList(l_knee), BoneList(l_ankle_scale), color, basePlayer);
			CreateBoneLine(BoneList(l_ankle_scale), BoneList(l_foot), color, basePlayer);
			CreateBoneLine(BoneList(l_foot), BoneList(l_toe), color, basePlayer);
		}

		{
			CreateBoneLine(BoneList(spine1), BoneList(r_hip), color, basePlayer);
			CreateBoneLine(BoneList(spine1), BoneList(r_hip), color, basePlayer);
			CreateBoneLine(BoneList(r_hip), BoneList(r_knee), color, basePlayer);
			CreateBoneLine(BoneList(r_knee), BoneList(r_ankle_scale), color, basePlayer);
			CreateBoneLine(BoneList(r_ankle_scale), BoneList(r_foot), color, basePlayer);
			CreateBoneLine(BoneList(r_foot), BoneList(r_toe), color, basePlayer);
		}
	}
	else if (!strstr(basePlayer.className, "BasePlayer") && Settings::Scientist::Skeleton)
	{
		CreateBoneLine(BoneList(head), BoneList(neck), color, basePlayer);

		{
			CreateBoneLine(BoneList(neck), BoneList(l_clavicle), color, basePlayer);
			CreateBoneLine(BoneList(l_clavicle), BoneList(l_upperarm), color, basePlayer);
			CreateBoneLine(BoneList(l_upperarm), BoneList(l_forearm), color, basePlayer);
			CreateBoneLine(BoneList(l_forearm), BoneList(l_ulna), color, basePlayer);
			CreateBoneLine(BoneList(l_ulna), BoneList(l_hand), color, basePlayer);
			if (1 == 1)
			{
				CreateBoneLine(BoneList(l_hand), BoneList(l_index1), color, basePlayer);
				CreateBoneLine(BoneList(l_index1), BoneList(l_index2), color, basePlayer);
				CreateBoneLine(BoneList(l_index2), BoneList(l_index3), color, basePlayer);

				CreateBoneLine(BoneList(l_hand), BoneList(l_little1), color, basePlayer);
				CreateBoneLine(BoneList(l_little1), BoneList(l_little2), color, basePlayer);
				CreateBoneLine(BoneList(l_little2), BoneList(l_little3), color, basePlayer);

				CreateBoneLine(BoneList(l_hand), BoneList(l_middle1), color, basePlayer);
				CreateBoneLine(BoneList(l_middle1), BoneList(l_middle2), color, basePlayer);
				CreateBoneLine(BoneList(l_middle2), BoneList(l_middle3), color, basePlayer);

				CreateBoneLine(BoneList(l_hand), BoneList(l_ring1), color, basePlayer);
				CreateBoneLine(BoneList(l_ring1), BoneList(l_ring2), color, basePlayer);
				CreateBoneLine(BoneList(l_ring2), BoneList(l_ring3), color, basePlayer);

				CreateBoneLine(BoneList(l_hand), BoneList(l_thumb1), color, basePlayer);
				CreateBoneLine(BoneList(l_thumb1), BoneList(l_thumb2), color, basePlayer);
				CreateBoneLine(BoneList(l_thumb2), BoneList(l_thumb3), color, basePlayer);
			}
		}

		{
			CreateBoneLine(BoneList(neck), BoneList(r_clavicle), color, basePlayer);
			CreateBoneLine(BoneList(r_clavicle), BoneList(r_upperarm), color, basePlayer);
			CreateBoneLine(BoneList(r_upperarm), BoneList(r_forearm), color, basePlayer);
			CreateBoneLine(BoneList(r_forearm), BoneList(r_ulna), color, basePlayer);
			CreateBoneLine(BoneList(r_ulna), BoneList(r_hand), color, basePlayer);
			if (1 == 1)
			{
				CreateBoneLine(BoneList(r_hand), BoneList(r_index1), color, basePlayer);
				CreateBoneLine(BoneList(r_index1), BoneList(r_index2), color, basePlayer);
				CreateBoneLine(BoneList(r_index2), BoneList(r_index3), color, basePlayer);

				CreateBoneLine(BoneList(r_hand), BoneList(r_little1), color, basePlayer);
				CreateBoneLine(BoneList(r_little1), BoneList(r_little2), color, basePlayer);
				CreateBoneLine(BoneList(r_little2), BoneList(r_little3), color, basePlayer);

				CreateBoneLine(BoneList(r_hand), BoneList(r_middle1), color, basePlayer);
				CreateBoneLine(BoneList(r_middle1), BoneList(r_middle2), color, basePlayer);
				CreateBoneLine(BoneList(r_middle2), BoneList(r_middle3), color, basePlayer);

				CreateBoneLine(BoneList(r_hand), BoneList(r_ring1), color, basePlayer);
				CreateBoneLine(BoneList(r_ring1), BoneList(r_ring2), color, basePlayer);
				CreateBoneLine(BoneList(r_ring2), BoneList(r_ring3), color, basePlayer);

				CreateBoneLine(BoneList(r_hand), BoneList(r_thumb1), color, basePlayer);
				CreateBoneLine(BoneList(r_thumb1), BoneList(r_thumb2), color, basePlayer);
				CreateBoneLine(BoneList(r_thumb2), BoneList(r_thumb3), color, basePlayer);
			}
		}

		CreateBoneLine(BoneList(neck), BoneList(spine4), color, basePlayer);
		CreateBoneLine(BoneList(spine4), BoneList(spine3), color, basePlayer);
		CreateBoneLine(BoneList(spine3), BoneList(spine2), color, basePlayer);
		CreateBoneLine(BoneList(spine2), BoneList(spine1), color, basePlayer);
		{
			CreateBoneLine(BoneList(spine1), BoneList(l_hip), color, basePlayer);
			CreateBoneLine(BoneList(spine1), BoneList(l_hip), color, basePlayer);
			CreateBoneLine(BoneList(l_hip), BoneList(l_knee), color, basePlayer);
			CreateBoneLine(BoneList(l_knee), BoneList(l_ankle_scale), color, basePlayer);
			CreateBoneLine(BoneList(l_ankle_scale), BoneList(l_foot), color, basePlayer);
			CreateBoneLine(BoneList(l_foot), BoneList(l_toe), color, basePlayer);
		}

		{
			CreateBoneLine(BoneList(spine1), BoneList(r_hip), color, basePlayer);
			CreateBoneLine(BoneList(spine1), BoneList(r_hip), color, basePlayer);
			CreateBoneLine(BoneList(r_hip), BoneList(r_knee), color, basePlayer);
			CreateBoneLine(BoneList(r_knee), BoneList(r_ankle_scale), color, basePlayer);
			CreateBoneLine(BoneList(r_ankle_scale), BoneList(r_foot), color, basePlayer);
			CreateBoneLine(BoneList(r_foot), BoneList(r_toe), color, basePlayer);
		}
	}

	if (Settings::Visuals::Players::Chams && RefreshShaders)
	{
		static UINT_PTR asset_bundle = 0x402402;
		bool flatChams = true;
		if (flatChams)
		{
			if (asset_bundle == 0x402402)
			{
				asset_bundle = UnityEngine::LoadAssetBundle(L"rust.assets");
			}
		}

		static UINT_PTR shader = 0;
		static int setShader = 420;

		if (setShader != Menu::currentCham)
		{
			if (Menu::currentCham == 0)
			{
				shader = UnityEngine::LoadAsset(asset_bundle, L"Chams");
			}
			else if (Menu::currentCham == 1)
			{
				shader = UnityEngine::LoadAsset(asset_bundle, L"SeethroughShader");
			}
			else if (Menu::currentCham == 2)
			{
				shader = UnityEngine::LoadAsset(asset_bundle, L"WireframeTransparent");
			}
			if (Menu::currentCham == 3)
			{
				shader = UnityEngine::LoadAsset(asset_bundle, L"chamslit");
			}
			setShader = Menu::currentCham;
		}

		if (shader)
		{
			auto multimesh = basePlayer.playerModel._multiMesh();
			if (multimesh)
			{
				SkinnedMultiMesh mesh(multimesh);
				auto mainRendList = mesh.get_Renderers();
				for (int idx = 0; idx < mainRendList->get_size(); idx++)
				{
					Renderer renderer(mainRendList->get_value(idx));
					if (renderer.Base_ != 0)
					{
						Material material(renderer.get_material());
						if (material.Base_ != 0)
						{
							if (shader != material.get_shader())
							{
								material.set_shader(shader);
							}

							if (flatChams)
							{
								if (Menu::currentCham == 0 || Menu::currentCham == 3)
								{
									material.SetColor(Str(L"_ColorVisible"), Color(Settings::Visuals::Players::Colors::VisibleChams[0], Settings::Visuals::Players::Colors::VisibleChams[1], Settings::Visuals::Players::Colors::VisibleChams[2], Settings::Visuals::Players::Colors::VisibleChams[3]));
									material.SetColor(Str(L"_ColorBehind"), Color(Settings::Visuals::Players::Colors::InVisibleChams[0], Settings::Visuals::Players::Colors::InVisibleChams[1], Settings::Visuals::Players::Colors::InVisibleChams[2], Settings::Visuals::Players::Colors::InVisibleChams[3]));
								}
								else if (Menu::currentCham == 2)
								{
									material.SetInt(Str(L"_WireThickness"), Settings::Visuals::Players::WireThickness);
									material.SetColor(Str(L"_WireColor"), Color(Settings::Visuals::Players::Colors::VisibleChams[0], Settings::Visuals::Players::Colors::VisibleChams[1], Settings::Visuals::Players::Colors::VisibleChams[2], Settings::Visuals::Players::Colors::VisibleChams[3]));
								}
							}
							else
							{
								if (!Settings::Visuals::Players::VisibleOnly) material.SetInt(Str(L"_ZTest"), 8);
								material.SetColor(Str(L"_Color"), Color(Settings::Visuals::Players::Colors::Chams[0], Settings::Visuals::Players::Colors::Chams[1], Settings::Visuals::Players::Colors::Chams[2], Settings::Visuals::Players::Colors::Chams[3]));
							}
						}
					}
				}
			}
		}
	}
}

void HandleBasePlayer(UINT_PTR player_ptr, char* entityClass)
{
	__try
	{
		BasePlayer basePlayer = BasePlayer(player_ptr);
		basePlayer.className = entityClass;

		if (basePlayer.Base_ == 0)
		{
			Ulog("%s - Exception Occurred.", entityClass);
			return;
		}

		if (basePlayer.playerModel.Base_ == 0) return;
		if (basePlayer.model.Base_ == 0) return;
		if (basePlayer.Inventory.Base_ == 0) return;
		if (basePlayer.Inventory.ContainerBelt.Base_ == 0) return;
		if (basePlayer.Inventory.ContainerWear.Base_ == 0) return;
		if (basePlayer.Inventory.ContainerBelt.GetItemList() == 0) return;
		if (basePlayer.Inventory.ContainerBelt.GetItems() == 0) return;

		TempBasePlayers.push_back(basePlayer);

		if (strstr(entityClass, "BasePlayer"))
		{
			if (!Settings::Visuals::Players::Players) return;
			if ((basePlayer.lifestate() != LifeState::Alive || basePlayer.health() < 0.1f)) return;
			if (basePlayer.playerFlags() & PlayerFlags(Sleeping) && !Settings::Visuals::Players::Sleepers) return;
			if (basePlayer.playerFlags() & PlayerFlags(Wounded) && !Settings::Visuals::Players::Wounded) return;
		}
		else
		{
			if (!Settings::Visuals::Players::NPC) return;
		}

		DrawBasePlayer(basePlayer);
	}
	__except (true)
	{
		Ulog("%s - Exception Occurred.", __FUNCTION__);
	}
}

void HandleObject(EntityClass* curEntity)
{
	for (ESPOption& option : ESPOptions)
	{
		if (option.Draw && strstr(curEntity->m_CachedPtr->pObjectClass->pPrefabNameString, option.Prefab))
		{
			auto mainclass = curEntity->m_CachedPtr->pBaseClass;
			BaseEntity baseEntity(mainclass);
			auto transform = baseEntity.get_transform();
			auto position = transform.GetPosition();
			std::string string;

			if (option.checkMaxDistance && option.MaxDistance < position.distance(LocalPlayer.get_transform().GetPosition())) break;

			if (option.DrawDistance)
			{
				char buf[256] = { 0 }; sprintf_s(buf, "[%.2f m] ", position.distance(LocalPlayer.get_transform().GetPosition()));
				string += buf;
			}
			if (option.DrawName)
			{
				char buf[256] = { 0 }; sprintf_s(buf, "%s", option.Name);
				string += buf;
			}

			temp_textList.push_back(Text(position, ImColor(option.Color[0], option.Color[1], option.Color[2]), string));
			break;
		}
	}
}

BasePlayer lastTarget;

BasePlayer LightFindTarget(float fovDistance)
{
	BasePlayer target;
	if (Settings::Combat::Aimbot::KeepTarget && lastTarget.Base_ != 0)
	{
		if ((strstr(lastTarget.className, "BasePlayer") && !Settings::Combat::Aimbot::IgnorePlayers) || (!strstr(lastTarget.className, "BasePlayer") && !Settings::Combat::Aimbot::IgnoreNPCs))
		{
			if (strstr(lastTarget.className, "BasePlayer"))
			{
				if ((target.lifestate() == LifeState::Alive || target.health() > 0.1f))
				{
					if (!(target.playerFlags() & PlayerFlags(Sleeping)) || !Settings::Combat::Aimbot::IgnoreSleepers)
					{
						if (!(target.playerFlags() & PlayerFlags(Wounded)) || !Settings::Combat::Aimbot::IgnoreWounded)
						{
							if (UnityEngine::LineOfSight(lastTarget.model.GetTransform(head).GetPosition(), LocalPlayer.Eyes.GetPosition(), 10551296))
							{
								Vector2 position;
								if (WorldToScreen(lastTarget.model.GetTransform(neck).GetPosition(), position))
								{
									if (fovDistance > position.Distance(GetScreenCenter()))
									{
										return lastTarget;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	for (BasePlayer& basePlayer : BasePlayers)
	{
		if ((strstr(basePlayer.className, "BasePlayer") && !Settings::Combat::Aimbot::IgnorePlayers) || (!strstr(basePlayer.className, "BasePlayer") && !Settings::Combat::Aimbot::IgnoreNPCs))
		{
			if (strstr(basePlayer.className, "BasePlayer"))
			{
				if ((basePlayer.lifestate() != LifeState::Alive || basePlayer.health() < 0.1f)) continue;
				if (basePlayer.playerFlags() & PlayerFlags(Sleeping) && Settings::Combat::Aimbot::IgnoreSleepers) continue;
				if (basePlayer.playerFlags() & PlayerFlags(Wounded) && Settings::Combat::Aimbot::IgnoreWounded) continue;
			}

			if (UnityEngine::LineOfSight(basePlayer.model.GetTransform(head).GetPosition(), LocalPlayer.Eyes.GetPosition(), 10551296))
			{
				Vector2 position;
				if (WorldToScreen(basePlayer.model.GetTransform(neck).GetPosition(), position))
				{
					if (fovDistance > position.Distance(GetScreenCenter()))
					{
						fovDistance = position.Distance(GetScreenCenter());
						target = basePlayer;
					}
				}
			}
		}
	}

	lastTarget = target;
	return target;
}

inline void StepConstant(Vector2& angles)
{
	bool smooth = Settings::Combat::Aimbot::Smoothing;
	int smooth_factor = Settings::Combat::Aimbot::SmoothingAmount;
	Vector2 angles_step = angles - LocalPlayer.input.bodyAngles();
	Normalize(angles_step.x, angles_step.y);

	if (smooth) {
		float factor_pitch = (smooth_factor / 10.f);
		if (angles_step.x < 0.f) {
			if (factor_pitch > std::abs(angles_step.x)) {
				factor_pitch = std::abs(angles_step.x);
			}
			angles.x = LocalPlayer.input.bodyAngles().x - factor_pitch;
		}
		else {
			if (factor_pitch > angles_step.x) {
				factor_pitch = angles_step.x;
			}
			angles.x = LocalPlayer.input.bodyAngles().x + factor_pitch;
		}
	}
	if (smooth) {
		float factor_yaw = (smooth_factor / 10.f);
		if (angles_step.y < 0.f) {
			if (factor_yaw > std::abs(angles_step.y)) {
				factor_yaw = std::abs(angles_step.y);
			}
			angles.y = LocalPlayer.input.bodyAngles().y - factor_yaw;
		}
		else {
			if (factor_yaw > angles_step.y) {
				factor_yaw = angles_step.y;
			}
			angles.y = LocalPlayer.input.bodyAngles().y + factor_yaw;
		}
	}
}


void Visuals::SyncedThread()
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		if (!AreAllDataInitialized()) return;

		static float LastShaderRefresh = 0.f;
		static float LastUpdate = 0.f;
		static float LastRefresh = 0.f;

		if (Settings::Misc::GroundAngles)
		{
			//if (GroundAngle == -1.f)
			//	GroundAngle = LocalPlayer.movement.groundAngle();
			//if (GroundAngleNew == -1.f)
			//	GroundAngleNew = LocalPlayer.movement.groundAngleNew();

			LocalPlayer.movement.groundAngle() = 0.f;
			LocalPlayer.movement.groundAngleNew() = 0.f;
		}

		for (int i = 0; i <= Globals::g_BaseNetworkable->pBaseNetworkable->pEntityRealm->pClientEntities->pEntityList->pBufferListVals->BufferListCount; i++)
		{
			auto curEntity = Globals::g_BaseNetworkable->pBaseNetworkable->pEntityRealm->pClientEntities->pEntityList->pBufferListVals->pBufferListData->Items[i].pItemClass;

			if (!curEntity || !curEntity->m_CachedPtr || !curEntity->pClassPointer || !curEntity->pClassPointer->pEntityClassNameString)
				continue;

			if (strcmp(curEntity->m_CachedPtr->pObjectClass->pPrefabNameString, "LocalPlayer") == 0)
			{
				BasePlayer basePlayer = BasePlayer(curEntity->m_CachedPtr->pBaseClass);
				basePlayer.className = curEntity->pClassPointer->pEntityClassNameString;
				LocalPlayer = basePlayer;
			}
			else
			{
				if (Entity::isPlayer(curEntity->pClassPointer->pEntityClassNameString))
				{
					HandleBasePlayer(curEntity->m_CachedPtr->pBaseClass, curEntity->pClassPointer->pEntityClassNameString);
				}
				else
				{
					HandleObject(curEntity);
				}
			}
		}

		/*
		if (LocalPlayer.Base_ != 0)//TRIGGERBOT???
		{
			if (LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).Base_ != 0)
			{
				if (LightFindTarget(10).Base_ != 0 && !LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.HasReloadCooldown())
				{
					if (!LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.HasAttackCooldown())
					{
						LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.LaunchProjectile();
						LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.primaryMagazine().contents()--;
						LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.UpdateAmmoDisplay();
						LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.ShotFired();
						LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.DidAttackClientside();
						LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.BeginCycle();
					}
				}
			}
		}
		*/

		if (LocalPlayer.Base_ != 0)
		{
			LocalPosition = LocalPlayer.get_transform().GetPosition();
			LocalRotation = LocalPlayer.Eyes.GetRotation();
			heldEntity = LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem());


			static float lastFireTime = 0.f;

			if (Settings::Combat::WeaponMods::Spam)
			{
				if (UnityEngine::get_realtimeSinceStartup() > lastFireTime + 1.f / Settings::Combat::WeaponMods::SpamRate)
				{
					lastFireTime = UnityEngine::get_realtimeSinceStartup();
					if (LocalPlayer.clActiveItem() != 0)
					{
						Item activeItem = LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem());
						if (activeItem.heldEntity())
						{
							if (Settings::Combat::WeaponMods::AlwaysSpam)
							{
								UnityEngine::SendSignalBroadcast(activeItem.heldEntity(), Signal::Attack);
							}
							else if (Globals::PressedKeys[Globals::Hotkeys::hotkey_SpamKey])
							{
								UnityEngine::SendSignalBroadcast(activeItem.heldEntity(), Signal::Attack);
							}
						}
					}
				}
			}
			else
			{
				lastFireTime = 0.f;
			}

			static float lastFallTime = 0.f;

			if (Settings::Misc::Suicide)
			{
				if (UnityEngine::get_realtimeSinceStartup() > lastFallTime + 1.f / Settings::Misc::SuicideRate)
				{
					lastFallTime = UnityEngine::get_realtimeSinceStartup();

					if (Settings::Misc::AlwaysSuicide || Globals::PressedKeys[Globals::Hotkeys::hotkey_SuicideKey])
					{
						LocalPlayer.OnLand(-50.f);
						LocalPlayer.OnLand(-50.f);
					}
				}
			}
			else
			{
				lastFallTime = 0.f;
			}

			static bool alreadystartedReload = false;

			static bool alreadyReset = false;
			if (Settings::Combat::Rage::Desync)
			{
				alreadyReset = false;
				static int updownleft = 0;
				static bool waspressed = false;
				if (Globals::PressedKeys[VK_DELETE])
				{
					waspressed = true;
				}

				if (!Globals::PressedKeys[VK_DELETE] && waspressed)
				{
					waspressed = false;
					updownleft += 1;
					if (updownleft > 3)
					{
						updownleft = 0;
					}
				}

				if (Globals::PressedKeys[Settings::Combat::Rage::DesyncKey])
				{
					float desyncTime = (UnityEngine::get_realtimeSinceStartup() - LocalPlayer.lastSentTickTime()) - 0.03125 * 3;
					float mm_max_eye = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5f) * 5.5f) - 0.05f;
					LocalPlayer.clientTickInterval() = 1.f;

					if (updownleft == 0)
					{
						LocalPlayer.Eyes.viewOffset().y = 1.5f;
					}
					else if (updownleft == 1)
					{
						LocalPlayer.Eyes.viewOffset().x = mm_max_eye;
					}
					else if (updownleft == 2)
					{
						LocalPlayer.Eyes.viewOffset().x = -mm_max_eye;
					}
					else if (updownleft == 3)
					{
						LocalPlayer.Eyes.viewOffset().z = -mm_max_eye;
					}
					if (Settings::Visuals::Players::Chams)
					{
						if (UnityEngine::get_realtimeSinceStartup() > LastUpdate + 60.f)
						{
							UnityEngine::RebuildAll();
							LastUpdate = UnityEngine::get_realtimeSinceStartup();
						}
						LastRefresh = 0.f;

						if (UnityEngine::get_realtimeSinceStartup() > LastShaderRefresh + 5.f)
						{
							LastShaderRefresh = UnityEngine::get_realtimeSinceStartup();
							RefreshShaders = true;
						}
						else
						{
							RefreshShaders = false;
						}
					}
					else
					{
						if (UnityEngine::get_realtimeSinceStartup() > LastRefresh + 60.f)
						{
							UnityEngine::RebuildAll();
							LastRefresh = UnityEngine::get_realtimeSinceStartup();
						}
						else
						{
							LastRefresh = UnityEngine::get_realtimeSinceStartup();
						}
						LastUpdate = 0.f;
						RefreshShaders = true;
					}

					auto desynctime = UnityEngine::get_realtimeSinceStartup() - LocalPlayer.lastSentTickTime();
					auto desyncpercentage = ((desynctime / 0.99f) * 100.0f) + 1.f;
					static int shotCount = 0;
					if (desyncpercentage < 100 && Settings::Combat::Rage::InstantShoot && LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).Base_ != 0)
					{
						if (Settings::Combat::Rage::PowerShot && desyncpercentage > 90)
						{
							if (!LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.HasReloadCooldown() && LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.primaryMagazine().contents() == 0)
							{
								LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.reloadPressTime() = 0.1f;
							}
							if (shotCount < (int)(desynctime / LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.repeatDelay()))
							{
								if (LightFindTarget(Settings::Combat::Silent::SilentFOV).Base_ != 0)
								{
									if (LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.primaryMagazine().contents() != 0)
									{
										shotCount++;
										LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.LaunchProjectile();
										LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.primaryMagazine().contents()--;
										LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.UpdateAmmoDisplay();
										LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.ShotFired();
										LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.DidAttackClientside();
									}
								}
							}
						}
						else if (!Settings::Combat::Rage::PowerShot && desyncpercentage > 5)
						{
							if (!LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.HasReloadCooldown() && LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.primaryMagazine().contents() == 0)
							{
								LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.reloadPressTime() = 0.1f;
							}
							if (shotCount < (int)(desynctime / LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.repeatDelay()))
							{
								if (LightFindTarget(Settings::Combat::Silent::SilentFOV).Base_ != 0)
								{
									if (LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.primaryMagazine().contents() != 0)
									{
										shotCount++;
										LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.LaunchProjectile();
										LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.primaryMagazine().contents()--;
										LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.UpdateAmmoDisplay();
										LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.ShotFired();
										LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).baseProjectile.DidAttackClientside();
									}
								}
							}
						}
					}
					else
					{
						shotCount = 0;
					}
				}
				else
				{
					LocalPlayer.Eyes.viewOffset() = Vector3().Zero() + Vector3(0, LocalPlayer.Eyes.viewOffset().y, 0);
					LocalPlayer.clientTickInterval() = 0.05f;
				}
			}
			else if (!alreadyReset)
			{
				LocalPlayer.Eyes.viewOffset() = Vector3().Zero();
				alreadyReset = true;
			}

			if (Settings::Combat::Silent::Silent && (Globals::Hotkeys::hotkey_SilentKey == 0 || Globals::PressedKeys[Globals::Hotkeys::hotkey_SilentKey]) && Settings::Combat::Silent::AutoShoot && heldEntity.Base_ != 0)
			{
				if (heldEntity.baseProjectile.primaryMagazine().contents() == 0)
				{
					if (!alreadystartedReload)
					{
						if (!heldEntity.baseProjectile.HasReloadCooldown() && heldEntity.baseProjectile.primaryMagazine().contents() == 0)
						{
							if (heldEntity.baseProjectile.reloadPressTime() == 0.f)
							{
								alreadystartedReload = true;
								heldEntity.baseProjectile.reloadPressTime() = 0.10f;
							}
						}
					}
				}
				else
				{
					alreadystartedReload = false;

					if (LightFindTarget(Settings::Combat::Silent::SilentFOV).Base_ != 0 && !heldEntity.baseProjectile.HasReloadCooldown())
					{
						if (!heldEntity.baseProjectile.HasAttackCooldown())
						{
							heldEntity.baseProjectile.LaunchProjectile();
							heldEntity.baseProjectile.primaryMagazine().contents()--;
							heldEntity.baseProjectile.UpdateAmmoDisplay();
							heldEntity.baseProjectile.ShotFired();
							heldEntity.baseProjectile.DidAttackClientside();
							heldEntity.baseProjectile.BeginCycle();
						}
					}
				}
			}
			else
			{
				alreadystartedReload = false;
			}
		}
	}
	__except (
		ExceptionCode = GetExceptionCode(),
		ExceptionPointers = GetExceptionInformation(),
		EXCEPTION_EXECUTE_HANDLER
		) {
		if (ExceptionPointers)
		{
			Ulog("Exception (%lx) caught in %s @ (%p) (%llx)",
				ExceptionCode, __FUNCTION__,
				ExceptionPointers->ExceptionRecord->ExceptionAddress,
				Globals::g_GameAssemblyBase
			);
		}
	}

	textGroupList = temp_textGroupList;
	temp_textGroupList.clear(); //sss




	BasePlayers = TempBasePlayers;
	TempBasePlayers.clear();

	basePlayerVectorList = temp_basePlayerVectorList;
	temp_basePlayerVectorList.clear();
}

void SafeDraw()
{
	DrawList = ImGui::GetBackgroundDrawList();

	if (!AreAllDataInitialized() || LocalPlayer.Base_ == 0)
	{
		StaticCamera = 0;
		return;
	}

	if (Menu::currentCrosshair == 1)
		DrawCrossCrosshair(Settings::Misc::CrosshairSize);
	else if (Menu::currentCrosshair == 2)
		DrawXCrosshair(Settings::Misc::CrosshairSize);
	else if (Menu::currentCrosshair == 3)
		DrawCircleCrosshair(Settings::Misc::CrosshairSize);
	else if (Menu::currentCrosshair == 4)
		DrawCustomCrosshair(Settings::Misc::CrosshairSize, Settings::Misc::CrosshairThickness, Settings::Misc::CrosshairGap);

	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	if (Settings::Combat::Rage::Desync)
	{
		auto desynctime = UnityEngine::get_realtimeSinceStartup() - LocalPlayer.lastSentTickTime();
		auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;

		float red, green, blue;
		float Num = desyncpercentage;
		if (desyncpercentage < 0.1)
			Num = 0;

		if (Settings::Combat::Rage::ShowDesync && Num != 0)
		{
			if (Num < 0.5)
			{
				red = Num * 2.f * 255.f;
				green = 255.f;
				blue = 0.f;
			}
			else
			{
				red = 255.f;
				green = (2.f - 2.f * Num) * 255.f;
				blue = 0.f;
			}

			if (Num > 1.f)
				Num = 1.f;

			ImVec2 center(Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2);

			DrawList->PathArcTo({ center.x, center.y - 1 }, -42, PI, 0, 48);
			DrawList->PathStroke(ImColor(40, 40, 40, 230), false, 5);

			DrawList->PathArcTo({ center.x, center.y - 1 }, -42, PI * Num, 0, 48);
			DrawList->PathStroke(ImColor((int)(red), (int)(green), (int)(blue)), false, 5);
		}
	}

	if (heldEntity.Base_ != 0)
	{
		if (heldEntity.baseProjectile.HasReloadCooldown())
		{
			if (Settings::Misc::Reloadindicator) {
				float reloadDuration = heldEntity.baseProjectile.GetReloadCooldown();
				float reloadDurationTotal = heldEntity.baseProjectile.GetReloadDuration();
				auto percentage = (((reloadDuration / reloadDurationTotal) * 100.0f) + 1.f) / 100;

				float red, green, blue;
				float Num = percentage;

				if (Num < 0.5)
				{
					red = Num * 2.f * 255.f;
					green = 255.f;
					blue = 0.f;
				}
				else
				{
					red = 255.f;
					green = (2.f - 2.f * Num) * 255.f;
					blue = 0.f;
				}

				red -= 100;
				green -= 100;
				blue -= 100;

				ImVec2 center(Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2 - 25);
				center.y += 30.f;

				DrawList->PathArcTo({ center.x, center.y }, -42, -PI, 0, 48);
				DrawList->PathStroke(ImColor(40, 40, 40, 230), false, 5);

				DrawList->PathArcTo({ center.x, center.y }, -42, -PI * (1.f - Num), 0, 48);
				DrawList->PathStroke(ImColor((int)(red), (int)(green), (int)(blue), 230), false, 5);
			}
		}
	}

	for (const Text& text : textList)
	{
		Vector2 screenPosition;
		if (WorldToScreen(text.Position, screenPosition))
		{
			DrawList->AddText({ screenPosition.x - (ImGui::CalcTextSize(text.Input.c_str()).x / 2), screenPosition.y }, text.Color, text.Input.c_str());
		}
	}

	for (const TextGroup& textGroup : textGroupList)
	{
		Vector2 screenPosition;
		if (WorldToScreen(textGroup.Position, screenPosition))
		{
			for (const Text& text : textGroup.textList)
			{
				DrawList->AddText({ screenPosition.x - (ImGui::CalcTextSize(text.Input.c_str()).x / 2), screenPosition.y }, text.Color, text.Input.c_str());
				screenPosition.y += ImGui::CalcTextSize("1").y;
			}
		}
	}

	for (const ILine& iLine : ILines)
	{
		Vector2 startPosition; Vector2 endPosition;

		auto p0w = WorldToScreen(iLine.Start, startPosition);
		auto p1w = WorldToScreen(iLine.End, endPosition);
		if ((p0w && p1w))
			DrawList->AddLine(ImVec2(startPosition.x, startPosition.y), ImVec2(endPosition.x, endPosition.y), iLine.Color);
	}

	for (BasePlayerVectors& basePlayerV3 : basePlayerVectorList)
	{
		Vector3 position = basePlayerV3.position;
		BasePlayer basePlayer = basePlayerV3.basePlayer;
		CornerBox cornerBox = basePlayerV3.cornerBox;
		Vector2 screenPosition;
		Vector3 textPosition = position;

		ImU32 color = ImColor(Settings::Visuals::Players::Colors::InVisible[0], Settings::Visuals::Players::Colors::InVisible[1], Settings::Visuals::Players::Colors::InVisible[2]);

		if (basePlayerV3.visible)
		{
			color = ImColor(Settings::Visuals::Players::Colors::Visible[0], Settings::Visuals::Players::Colors::Visible[1], Settings::Visuals::Players::Colors::Visible[2]);
		}

		if (Settings::Visuals::Players::CornerBox)
		{
			if (cornerBox.Valid)
			{
				Vector2 left;
				auto leftw2s = WorldToScreen(cornerBox.left, left);

				Vector2 right;
				auto rightw2s = WorldToScreen(cornerBox.right, right);

				Vector2 top;
				auto topw2s = WorldToScreen(cornerBox.top, top);

				Vector2 bottom;
				auto bottomw2s = WorldToScreen(cornerBox.bottom, bottom);

				if (cornerBox.Valid && leftw2s || rightw2s || topw2s || bottomw2s)
				{
					DrawCornerBox(Vector2(left.x, top.y), Vector2(right.x, bottom.y), color, 1.5f);
				}
			}
		}
		textPosition.y -= 0.3f;

		auto vis = WorldToScreen(textPosition, screenPosition);

		if (vis)
		{
			if (Settings::Visuals::Players::Name || Settings::Visuals::Players::Distance)
			{
				std::string string;

				if (strstr(basePlayer.className, "BasePlayer") && Settings::Visuals::Players::Distance)
				{
					char buf[256] = { 0 }; sprintf_s(buf, "[%.2f M]", position.distance(LocalPosition));
					string = buf;
				}

				if (Settings::Visuals::Players::Distance && Settings::Visuals::Players::Name) string += " ";

				if (strstr(basePlayer.className, "BasePlayer") && Settings::Visuals::Players::Name)
				{
					char buf[256] = { 0 }; sprintf_s(buf, "%ls", basePlayer.GetDisplayName());
					string += buf;
				}

				ImVec2 textsize = (ImGui::CalcTextSize(string.c_str()));
				DrawList->AddText({ screenPosition.x - (textsize.x / 2), screenPosition.y }, color, string.c_str());
				screenPosition.y += ImGui::CalcTextSize("1").y;
			}

			if (Settings::Visuals::Players::HeldItem)
			{
				std::string string;
				if (basePlayer.clActiveItem() != 0)
				{
					Item item = basePlayer.Inventory.ContainerBelt.FindActiveItem(basePlayer.clActiveItem());
					if (item.Base_)
					{
						char buf[256] = { 0 }; sprintf_s(buf, "%ls", item.itemDefinition.GetDisplayName());
						basePlayer.HeldWeapon = buf;
						string = buf;
					}
					else
					{
						string = "None";
					}
				}
				else
				{
					string = "None";
				}

				DrawList->AddText({ screenPosition.x - (ImGui::CalcTextSize(string.c_str()).x / 2), screenPosition.y }, color, string.c_str());
				screenPosition.y += ImGui::CalcTextSize("1").y;
			}


			if (Settings::Visuals::Players::Health)
			{
				char buf[256] = { 0 }; sprintf_s(buf, " [%.2f HP]", basePlayer.health());
				std::string string = buf;

				DrawList->AddText({ screenPosition.x - (ImGui::CalcTextSize(string.c_str()).x / 2), screenPosition.y }, color, string.c_str());
				screenPosition.y += ImGui::CalcTextSize("1").y;
			}


			if (Settings::Visuals::Players::Snaplines)
			{
				DrawList->AddLine(ImVec2(GetScreenSize().Width / 2, GetScreenSize().Height - 100.f), ImVec2(screenPosition.x, screenPosition.y), color);
			}

			if ( Settings::Visuals::Players::HealthBar)
			{
				DrawHealthBar(screenPosition, 100.f, basePlayer.health(), basePlayer.MaxHealth());
			}
		}
		else
		{
			if (Settings::Visuals::Players::OffscreenIndicators)
			{
				InvisiblePlayerIndicator(position, LocalPosition, LocalRotation, color);
			}
		}
	}

	if (Settings::Combat::Aimbot::Aimbot && Settings::Combat::Aimbot::DrawFOV)
	{
		DrawList->AddCircle({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2 }, Settings::Combat::Aimbot::FOV, ImColor(255, 4, 0), 64);
		DrawList->AddCircle({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2 }, Settings::Combat::Aimbot::FOV + 0.5, ImColor(10, 10, 10, 200), 64, 0.5);
	}

	if (Settings::Combat::Silent::Silent && Settings::Combat::Silent::SilentFOV)
	{
		DrawList->AddCircle({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2 }, Settings::Combat::Silent::SilentFOV, ImColor(255, 4, 0), 64);
		DrawList->AddCircle({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2 }, Settings::Combat::Silent::SilentFOV + 0.5, ImColor(10, 10, 10, 200), 64, 0.5);
	}
}

void Visuals::DrawESP()
{
	__try
	{
		//Ulog("%s called", __FUNCTION__);

		SafeDraw();
	}
	__except (true)
	{
		Ulog("%s - Exception occurred within SafeDraw Function.", __FUNCTION__);
	}
}