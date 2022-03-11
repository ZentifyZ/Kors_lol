#pragma once
#include "pch.h"
#include "RustHooks.h"

uintptr_t Hooks::hk_FakeCreateProjectile(void* baseProjectile, void* prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity)
{
	__try
	{
		//Ulog("%s - hk_FakeCreateProjectile called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_CreateProjectile(baseProjectile, prefabPath, pos, forward, velocity);
}

BasePlayer FindTarget(float fovDistance)
{
	BasePlayer target;

	for (BasePlayer& basePlayer : BasePlayers)
	{
		if ((strstr(basePlayer.className, "BasePlayer") && !Settings::Combat::Silent::IgnorePlayers) || (!strstr(basePlayer.className, "BasePlayer") && !Settings::Combat::Silent::IgnoreNPCs))
		{
			if (strstr(basePlayer.className, "BasePlayer"))
			{
				if ((basePlayer.lifestate() != LifeState::Alive || basePlayer.health() < 0.1f)) continue;
				if (basePlayer.playerFlags() & PlayerFlags(Sleeping) && Settings::Combat::Silent::IgnoreSleepers) continue;
				if (basePlayer.playerFlags() & PlayerFlags(Wounded) && Settings::Combat::Silent::IgnoreWounded) continue;
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

	return target;
}

BasePlayer FindClosestTarget(Vector3 from)
{
	BasePlayer target;
	float Closest = FLT_MAX;

	for (BasePlayerVectors& basePlayerV3 : basePlayerVectorList)
	{
		if (UnityEngine::LineOfSight(basePlayerV3.basePlayer.model.GetTransform(head).GetPosition(), from, 10551296))
		{
			if (from.Distance(basePlayerV3.basePlayer.model.GetTransform(head).GetPosition()) < Closest)
			{
				target = basePlayerV3.basePlayer;
				Closest = from.Distance(basePlayerV3.basePlayer.model.GetTransform(head).GetPosition());
			}
		}
	}

	return target;
}

void Hooks::hk_FrameUpdate(UINT_PTR PlayerModel, bool wounded)
{
	__try
	{
		if (Settings::Misc::SilentWalk)
		{
			static UINT_PTR model = 0x402402;
			static UINT_PTR flag = 0x402402;
			static UINT_PTR LCP = 0x402402;

			if (LCP == 0x402402)
			{
				LCP = Dumper::GetFieldOffet("Assembly-CSharp", "", "PlayerModel", "isLocalPlayer");
			}

			auto& localplayer = *(bool*)(PlayerModel + LCP);

			if (!localplayer) {
				Globals::Functions::Original_FrameUpdate(PlayerModel, wounded);
				return;
			}

			if (model == 0x402402)
			{
				model = Dumper::GetFieldOffet("Assembly-CSharp", "", "PlayerModel", "modelState");
			}

			if (flag == 0x402402)
			{
				flag = Dumper::GetFieldOffet("Rust.Data", "", "ModelState", "flags");
			}

			auto& modelState = *(UINT_PTR*)(PlayerModel + model);
			auto& modelflags = *(int*)(modelState + flag);

			int original = modelflags;
			modelflags |= (int)32;
			Globals::Functions::Original_FrameUpdate(PlayerModel, wounded);
			modelflags = original;
			return;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_FrameUpdate(PlayerModel, wounded);
}

void Hooks::hk_FakeVisUpdateUsingCulling(void* basePlayer, float dist, bool visibility)
{
	__try
	{
		//Ulog("%s - hk_FakeVisUpdateUsingCulling called", __FUNCTION__);
		if (Settings::Visuals::Players::Chams && !Settings::Visuals::Players::VisibleOnly)
			return Globals::Functions::Original_VisUpdateUsingCulling(basePlayer, 2.f, true);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_VisUpdateUsingCulling(basePlayer, dist, visibility);
}

Vector3 Hooks::hk_MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake MoveTowards called", __FUNCTION__);

		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "SimulateAimcone");
		}

		UINT_PTR returnAddress = (UINT_PTR)_ReturnAddress();

		if (returnAddress > var && returnAddress < var + 0x800)
		{
			target *= (Settings::Combat::WeaponMods::Recoil / 100.f);
			maxDistanceDelta *= Settings::Combat::WeaponMods::Recoil / 100.f;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_MoveTowards(current, target, maxDistanceDelta);
}

void Hooks::hk_AddPunch(UINT_PTR heldEntity, Vector3 amount, float duration)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake AddPunch called", __FUNCTION__);

		amount *= Settings::Combat::WeaponMods::Recoil / 100.0f;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_AddPunch(heldEntity, amount, duration);
}

void Hooks::hk_EokaDoAttack(UINT_PTR baseProjectile)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake Eoka DoAttack called", __FUNCTION__);

		if (Settings::Combat::WeaponMods::InstantEoka)
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "FlintStrikeWeapon", "_didSparkThisFrame");
			}

			auto& _didSparkThisFrame = *(bool*)(baseProjectile + var);
			_didSparkThisFrame = true;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_EokaDoAttack(baseProjectile);
}

void Hooks::hk_UpdateGravity(UINT_PTR PlayerWalkMovement, UINT_PTR state)
{
	__try
	{
		//Ulog("%s - hk_UpdateGravity called", __FUNCTION__);

		if (Settings::Misc::JumpHigh)
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "PlayerWalkMovement", "gravityMultiplier");
			}

			auto& gravityMultiplier = *(float*)(PlayerWalkMovement + var);
			auto origianlGravity = gravityMultiplier;

			if (Settings::Misc::JumpHigh)
				gravityMultiplier = 1.25f;

			Globals::Functions::Original_UpdateGravity(PlayerWalkMovement, state);

			gravityMultiplier = origianlGravity;

			return;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}
	return Globals::Functions::Original_UpdateGravity(PlayerWalkMovement, state);
}

void Hooks::hk_SetFlying(UINT_PTR ModelState)
{
	// always use SEH in any hook cus its a god given right

	__try
	{
		if (Settings::Misc::FakeAdmin) return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_SetFlying(ModelState);
}

void Hooks::hk_DoAttack(UINT_PTR baseProjectile)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake DoAttack called", __FUNCTION__);

		static UINT_PTR automatic_var = 0x402402;

		if (automatic_var == 0x402402)
		{
			automatic_var = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseProjectile", "automatic");
		}

		auto& automatic = *(bool*)(baseProjectile + automatic_var);
		auto defaultAutomaticValue = automatic;

		if (Settings::Combat::WeaponMods::Automatic) automatic = true;

		static UINT_PTR repeatDelay_var = 0x402402;

		if (repeatDelay_var == 0x402402)
		{
			repeatDelay_var = Dumper::GetFieldOffet("Assembly-CSharp", "", "AttackEntity", "repeatDelay");
		}

		auto& repeatDelay = *(float*)(baseProjectile + repeatDelay_var);
		auto defaultrepeatDelay = repeatDelay;

		repeatDelay /= Settings::Combat::WeaponMods::FireRate / 100.f;

		auto& projectileVelocityScale = BaseProjectile(baseProjectile).projectileVelocityScale();
		auto defaultprojectileVelocityScale = projectileVelocityScale;

		projectileVelocityScale *= Settings::Combat::WeaponMods::FastBulletSpeed;
		//projectileVelocityScale *= wcscmp(LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).itemDefinition.GetDisplayName(), L"L96 Rifle") ? 1.3f : Settings::Combat::WeaponMods::FastBulletSpeed;;

		Globals::Functions::Original_DoAttack(baseProjectile);

		projectileVelocityScale = defaultprojectileVelocityScale;
		automatic = defaultAutomaticValue;
		repeatDelay = defaultrepeatDelay;

		return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_DoAttack(baseProjectile);
}

void Hooks::hk_OnCameraPositionChanged(UINT_PTR baseViewModel, UINT_PTR camera, UINT_PTR basePlayer)
{
	__try {
		//Ulog("%s - hk_OnCameraPositionChanged called", __FUNCTION__);
		static UINT_PTR bobVar = 0x402402;
		static UINT_PTR lowerVar = 0x402402;
		static UINT_PTR swayVar = 0x402402;

		if (bobVar == 0x402402)
			bobVar = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseViewModel", "bob");

		if (lowerVar == 0x402402)
			lowerVar = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseViewModel", "lower");

		if (swayVar == 0x402402)
			swayVar = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseViewModel", "sway");

		auto& bob = *(UINT_PTR*)(baseViewModel + bobVar);
		auto defaultBobValue = bob;

		auto& lower = *(UINT_PTR*)(baseViewModel + lowerVar);
		auto defaultLowerValue = lower;

		auto& sway = *(UINT_PTR*)(baseViewModel + swayVar);
		auto defaultSwayValue = sway;

		if (Settings::Misc::NoBobbing)
			bob = 0;
		if (Settings::Misc::NoLowering)
			lower = 0;
		if (Settings::Misc::NoSwaying)
			sway = 0;

		Globals::Functions::Original_OnCameraPositionChanged(baseViewModel, camera, basePlayer);

		bob = defaultBobValue;
		lower = defaultLowerValue;
		sway = defaultSwayValue;

		return;
	}
	__except (true) {
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_OnCameraPositionChanged(baseViewModel, camera, basePlayer);
}

void Hooks::hk_EditViewAngles(UINT_PTR baseProjectile)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake DoAttack called", __FUNCTION__);

		static UINT_PTR aimswayvar = 0x402402;
		static UINT_PTR aimSwaySpeedvar = 0x402402;

		if (aimswayvar == 0x402402)
		{
			aimswayvar = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseProjectile", "aimSway");
		}

		if (aimSwaySpeedvar == 0x402402)
		{
			aimSwaySpeedvar = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseProjectile", "aimSwaySpeed");
		}

		auto& aimsway = *(float*)(baseProjectile + aimswayvar);
		auto& aimSwaySpeed = *(float*)(baseProjectile + aimSwaySpeedvar);
		auto defaultAimSwayValue = aimsway;

		aimsway *= Settings::Combat::WeaponMods::Sway / 100.f;
		aimSwaySpeed *= Settings::Combat::WeaponMods::Sway / 100.f;

		Globals::Functions::Original_EditViewAngles(baseProjectile);

		aimsway = defaultAimSwayValue;
		aimSwaySpeed = defaultAimSwayValue;
		return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_EditViewAngles(baseProjectile);
}

void Hooks::hk_ViewModelPlay(UINT_PTR viewModel, pUncStr name, int layer)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake Play called", __FUNCTION__);

		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "DoAttack");
		}

		UINT_PTR returnAddress = (UINT_PTR)_ReturnAddress();

		if (returnAddress > var && returnAddress < var + 0x296)
		{
			if (Settings::Combat::WeaponMods::NoAttackAnimation) return;
			//target *= (Settings::Combat::WeaponMods::Recoil / 100.f);
			//maxDistanceDelta *= Settings::Combat::WeaponMods::Recoil / 100.f;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_ViewModelPlay(viewModel, name, layer);
}

bool Hooks::hk_CanHoldItems(UINT_PTR baseMountable)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_CanHoldItems called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	if (Settings::Combat::WeaponMods::CanHoldItems)
	{
		return true;
	}

	return Globals::Functions::Original_CanHoldItems(baseMountable);
}

bool Hooks::hk_DoHit(UINT_PTR projectile, UINT_PTR test, Vector3 point, Vector3 normal)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		HitTest hitTest(test);

		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Dumper::GetMethodOffset("Assembly-CSharp", "", "Projectile", "get_isAuthoritative");
		}

		typedef bool Method(UINT_PTR);
		bool auth = ((Method*)(Globals::g_GameAssemblyBase + var))(projectile);
		if (Settings::Combat::WeaponMods::Penetrate) {
			if (auth)
			{
				if (hitTest.HitEntity() != 0)
				{
					auto zzz = *(UINT_PTR*)(hitTest.HitEntity());
					auto className = *(char**)(zzz + 0x10);
					Ulog("Hit entity: %s", className);

					bool validPlayer = false;
					if (strstr(className, "Corpse"))
						validPlayer = false;
					else if (strstr(className, "BasePlayer"))
						validPlayer = true;
					else if (strstr(className, "BanditGuard"))
						validPlayer = true;
					else if (strstr(className, "UnderwaterDweller"))
						validPlayer = true;
					else if (strstr(className, "TunnelDweller"))
						validPlayer = true;
					else if (strstr(className, "ScientistNPCNew"))
						validPlayer = true;
					else if (strstr(className, "HumanNPCNew"))
						validPlayer = true;
					else if (strstr(className, "HTNPlayer"))
						validPlayer = true;
					else if (strstr(className, "Scientist"))
						validPlayer = true;
					else if (strstr(className, "NPCPlayer"))
						validPlayer = true;
					else if (strstr(className, "HumanNPC"))
						validPlayer = true;
					else if (strstr(className, "NPCMurderer"))
						validPlayer = true;
					else if (strstr(className, "NPCPlayerApex"))
						validPlayer = true;
					else if (strstr(className, "HeavyScientist"))
						validPlayer = true;

					if (validPlayer)
					{
					}

					if (strstr(className, "CargoShip"))
						return false;
					else if (strstr(className, "RHIB"))
						return false;
					else if (strstr(className, "WaterCatcher"))
						return false;
					else if (strstr(className, "JunkPile"))
						return false;
					else if (strstr(className, "MotorRowboat"))
						return false;
					else if (strstr(className, "RidableHorse"))
						return false;
					else if (strstr(className, "ResourceEntity"))
						return false;
					else if (strstr(className, "BuildingPrivlidge"))
						return false;
					else if (strstr(className, "HackableLockedCrate"))
						return false;
					else if (strstr(className, "TreeEntity"))
						return false;
					else if (strstr(className, "ScrapTransportHelicopter"))
						return false;
					else if (strstr(className, "BoxStorage"))
						return false;
					else if (strstr(className, "VendingMachine"))
						return false;
					else if (strstr(className, "CH47HelicopterAIController"))
						return false;
					else if (strstr(className, "MiniCopter"))
						return false;
					else if (strstr(className, "SupplyDrop"))
						return false;
					else if (strstr(className, "SimplebuildingBlock"))
						return false;
					else if (strstr(className, "MiningQuarry"))
						return false;
					else if (strstr(className, "RepairBench"))
						return false;
					else if (strstr(className, "ResearchTable"))
						return false;
					else if (strstr(className, "IceFence"))
						return false;
					else if (strstr(className, "LootContainer"))
						return false;
					else if (strstr(className, "OreResourceEntity"))
						return false;
					else if (strstr(className, "ElevatorLift"))
						return false;
					else if (strstr(className, "Elevator"))
						return false;
					//else if (strstr(className, "Barricade"))
						//return false;
					else if (strstr(className, "BaseOven"))
						return false;
					else if (strstr(className, "Workbench"))
						return false;
				}
			}
		}

		//Ulog("%s - Fake Launch called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_DoHit(projectile, test, point, normal);
}

void Hooks::hk_HandleRunDuckCrawl(UINT_PTR PlayerWalkMovement, UINT_PTR state, bool wantsRun, bool wantsDuck, bool wantsCrawl)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_HandleRunDuckCrawl called", __FUNCTION__);
		if (Settings::Misc::OmniSprint) wantsRun = true;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_HandleRunDuckCrawl(PlayerWalkMovement, state, wantsRun, wantsDuck, wantsCrawl);
}

bool Hooks::hk_CanAttack(UINT_PTR basePlayer)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake CanAttack called", __FUNCTION__);
		if (Settings::Misc::CanAttack) return true;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_CanAttack(basePlayer);
}

void Hooks::hk_OnLand(UINT_PTR basePlayer, float velocity)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake On Land called", __FUNCTION__);

		if (Settings::Misc::NoFallDamage) return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_OnLand(basePlayer, velocity);
}


void Hooks::hk_OnAttacked(UINT_PTR basePlayer, UINT_PTR info)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_OnAttacked called", __FUNCTION__);

		if (Settings::Combat::WeaponMods::CustomHitSound)
		{
			static float lastPlay = 0.f;

			if (UnityEngine::get_realtimeSinceStartup() > lastPlay + 0.1f)
			{
				lastPlay = UnityEngine::get_realtimeSinceStartup();
				PlaySoundA(Settings::Combat::WeaponMods::HitSound, NULL, SND_ASYNC);
			}
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_OnAttacked(basePlayer, info);
}

void Hooks::hk_DoHitNotify(UINT_PTR Entity, UINT_PTR info)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_DoHitNotify called", __FUNCTION__);

		BasePlayer basePlayer(Entity);

		HitInfo hitInfo(info);
		DamageTypeList damageTypeList(hitInfo.damageTypes());

		//Ulog("Hit %ls in %ls for %.2f damage", basePlayer.GetDisplayName(), hitInfo.GetBoneName()->str, damageTypeList.Total());

		if (Settings::Combat::WeaponMods::CustomHitSound) return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_DoHitNotify(Entity, info);
}

bool Hooks::hk_GetIsHeadshot(UINT_PTR hitInfo)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_GetIsHeadshot called", __FUNCTION__);

		if (Settings::Combat::WeaponMods::CustomHitSound) return false;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_GetIsHeadshot(hitInfo);
}

void Hooks::hk_SendProjectileAttack(UINT_PTR basePlayer, UINT_PTR playerProjectileAttack)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_SendProjectileAttack called", __FUNCTION__);

		auto playerAttack = *(UINT_PTR*)(playerProjectileAttack + 0x18);
		auto& distance = *(float*)(playerProjectileAttack + 0x2C);
		auto attack = *(UINT_PTR*)(playerAttack + 0x18);
		//auto hitid = *(UINT_PTR*)(attack + 0x2C);
		//auto& hitBone = *(UINT_PTR*)(attack + 0x30);

		if (Settings::Combat::WeaponMods::OVDist) {
			auto& distance = *(float*)(playerProjectileAttack + 0x2C);
			distance = Settings::Combat::WeaponMods::OVDistance;
		}

		if (Settings::Combat::WeaponMods::OVHitbox) {
			auto& hitBone = *(UINT_PTR*)(attack + 0x30);
			hitBone = Settings::Combat::WeaponMods::OVHit;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_SendProjectileAttack(basePlayer, playerProjectileAttack);
}

bool Hooks::hk_IsWaterMaterial(UINT_PTR projectile, UINT_PTR materialName)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_IsWaterMaterial called", __FUNCTION__);
		//return false;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_IsWaterMaterial(projectile, materialName);
}

void Hooks::hk_HandleJumping(UINT_PTR playerWalkMovement, UINT_PTR modelState, bool wantsJump, bool jumpInDirection)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_HandleJumping called", __FUNCTION__);

		if (!Settings::Misc::InfJump)
			return Globals::Functions::Original_HandleJumping(playerWalkMovement, modelState, wantsJump, jumpInDirection);

		if (wantsJump)
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerWalkMovement", "Jump");
			}

			typedef pUncStr Method(UINT_PTR, UINT_PTR, bool);
			((Method*)(Globals::g_GameAssemblyBase + var))(playerWalkMovement, modelState, jumpInDirection);
		}

		return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_HandleJumping(playerWalkMovement, modelState, wantsJump, jumpInDirection);
}

void Hooks::hk_Launch(UINT_PTR projectile)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake Launch called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_Launch(projectile);
}

float Max(float a, float b)
{
	return (a <= b) ? b : a;
}

void Hooks::hk_OnGUI(UINT_PTR rcx)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake OnGUI called", __FUNCTION__);

		static bool skipped = true;
		if (skipped)
		{
			Visuals::SyncedThread();
			skipped = false;
		}
		else
		{
			skipped = true;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_OnGUI(rcx);
}

/*
float flyhackDistanceVertical = 0.f;
float flyhackDistanceHorizontal = 0.f;
float flyhackPauseTime;
void TestFlying() {
	flyhackPauseTime = Max(0.f, flyhackPauseTime - UnityEngine::get_fixedDeltaTime());
	bool inAir = false;

	typedef float Method(UINT_PTR);
	float radius = LocalPlayer.GetRadius();//((Method*)(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "GetRadius")))(LocalPlayer.Base_);
	//float radius = reinterpret_cast<float(*)(BasePlayer*)>(vars::stor::gBase + CO::GetRadius)(LocalPlayer::Entity());
	float height = LocalPlayer.GetHeight();//((Method*)(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "GetHeight")))(LocalPlayer.Base_);
	//float height = reinterpret_cast<float(*)(BasePlayer*, bool)>(vars::stor::gBase + CO::GetHeight)(LocalPlayer::Entity(), false);
	UINT_PTR lastSentTick = *(UINT_PTR*)(LocalPlayer.Base_ + Dumper::GetFieldOffet("Assembly-CSharp", "", "BasePlayer", "lastSentTick"));
	Vector3 lastSentPosition = *(Vector3*)(lastSentTick + Dumper::GetFieldOffet("Rust.Data", "", "PlayerTick", "position"));
	Vector3 position = *(Vector3*)(LocalPlayer.playerModel.Base_ + Dumper::GetFieldOffet("Assembly-CSharp", "", "PlayerModel", "position"));
	Vector3 vector = (lastSentPosition + position) * 0.5f;
	//Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->position() + read(read(LocalPlayer::Entity() + (playermodel)0x4B0, uintptr_t) + (velocity or position)0x1D8, Vector3)) * 0.5f;
	Vector3 vector2 = vector + Vector3(0.f, radius - 2.f, 0.f);
	Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
	float radius2 = radius - 0.05f;
	bool a = UnityEngine::CheckCapsule(vector2, vector3, radius2, 1503731969);
	inAir = !a;

	if (inAir) {
		bool flag = false;
		Vector3 vector4 = position - lastSentPosition;
		//Vector3 vector4 = read(read(LocalPlayer::Entity() + 0x4B0, uintptr_t) + 0x1D8, Vector3) - LocalPlayer::Entity()->lastSentTick()->position();
		float num3 = abs(vector4.y);
		float num4 = vector4.magnitude2d();
		//float num4 = reinterpret_cast<float(*)(Vector3)>(vars::stor::gBase + CO::Magnitude2D)(vector4);
		if (vector4.y >= 0.f) {
			flyhackDistanceVertical += vector4.y;
			flag = true;
		}
		if (num3 < num4) {
			flyhackDistanceHorizontal += num4;
			flag = true;
		}
		if (flag) {
			float num5 = Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
			float num6 = LocalPlayer.GetJumpHeight() + num5;
			//float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
			if (flyhackDistanceVertical > num6) {
				//return true;
			}
			float num7 = Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
			float num8 = 5.f + num7;
			if (flyhackDistanceHorizontal > num8) {
				//return true;
			}
		}
	}
	else {
		flyhackDistanceHorizontal = 0.f;
		flyhackDistanceVertical = 0.f;
	}
}

void CheckFlyhack() {
	TestFlying();
	float num5 = Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num6 = LocalPlayer.GetJumpHeight() + num5;
	Vars::Global::max_flyhack = num6;
	//vars::stuff::max_flyhack = num6;
	//if (flyhackDistanceVertical <= num6)
	{
		Vars::Global::flyhack = flyhackDistanceVertical;
	}

	float num7 = Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num8 = 5.f + num7;
	Vars::Global::max_hor_flyhack = num8;
	//vars::stuff::max_hor_flyhack = num8;
	//if (flyhackDistanceHorizontal <= num8)
	{
		Vars::Global::hor_flyhack = flyhackDistanceHorizontal;
	}
}*/

void Hooks::hk_ClientInput(UINT_PTR basePlayer, UINT_PTR state)
{
	// always use SEH in any hook cus its a god given right
	//
	BasePlayer pBasePlayer = basePlayer;
	__try
	{
		//Ulog("%s - Fake ClientInput called", __FUNCTION__);

		UnityEngine::DDrawGet();

		if (Settings::Misc::FakeAdmin)
		{
			pBasePlayer.playerFlags() |= PlayerFlags::IsAdmin;
		}

		UnityEngine::IgnoreLayerCollision(12, 4, !Settings::Misc::WalkOnWater);
		UnityEngine::IgnoreLayerCollision(12, 30, Settings::Misc::WalkThroughTrees);
		UnityEngine::IgnoreLayerCollision(12, 11, Settings::Misc::WalkThroughPlayers);

		Globals::Functions::Original_ClientInput(basePlayer, state);
		return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_ClientInput(basePlayer, state);
}

bool Hooks::hk_FakeShouldShowHud()
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		// Ulog("%s - Fake should show hud called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_ShouldShowHud();
}