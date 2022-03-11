#pragma once

namespace Settings
{
	namespace Visuals
	{
		namespace Players
		{
			inline bool Players;
			inline bool Sleepers;
			inline bool Wounded;
			inline bool NPC = false;
			inline bool Name;
			inline bool Health;
			inline bool Distance;
			inline bool HeldItem;
			inline bool Snaplines;
			inline bool Chams;
			inline int WireThickness = 100;
			inline bool VisibleOnly;
			inline bool HealthChams;
			inline bool CornerBox;
			inline bool Skeleton;
			inline bool HealthBar;
			inline bool OffscreenIndicators;

			namespace Colors
			{
				inline float Chams[] = { 1.f,1.f,1.f,1.f };
				inline float VisibleChams[] = { 0.f,1.f,0.f,1.f };
				inline float InVisibleChams[] = { 1.f,0.f,0.f,1.f };
				inline float Visible[] = { 0.f,1.f,0.f,1.f };
				inline float InVisible[] = { 1.f,0.f,0.f,1.f };
			}
		}
	}
	namespace Scientist
	{
		inline bool Snaplines;
		inline bool HealthBar;
		inline bool HeldItem;
		inline bool Name;
		inline bool Skeleton;
		inline bool Health;
		inline bool Distance;
		inline bool CornerBox;
	}

	namespace Combat
	{
		namespace WeaponMods
		{
			inline bool AutoReload = false;
			inline float FastBulletSpeed = 1.0f;
			inline bool FastBullet = false;
			inline float Recoil = 100.f;
			inline float Spread = 100.f;
			inline float Sway = 100.f;
			inline float FireRate = 100.f;
			inline float SpamRate = 1.f;
			inline float Thickness = 0.1f;
			inline bool CustomHitSound = false; inline char HitSound[] = "C:\\bonk.wav";
			inline bool OVDist = false;
			inline float OVDistance = 100.f;
			inline bool OVHitbox = false;
			inline int OVHit = 698017942;
			inline bool Penetrate = false;
			inline bool CanHoldItems = false;
			inline bool Spam = false; inline bool AlwaysSpam = false;
			inline bool NoAttackAnimation = false;
			inline bool Automatic = false;
			inline bool InstantEoka = false;
		}
		namespace Aimbot
		{
			inline bool Aimbot;
			inline bool Smoothing;
			inline int SmoothingAmount;
			inline float FOV = 0.f;
			inline bool DrawFOV;
			inline bool KeepTarget;

			inline bool IgnorePlayers;
			inline bool IgnoreSleepers;
			inline bool IgnoreWounded;
			inline bool IgnoreNPCs;
		}
		namespace Silent
		{
			inline bool Silent = false;
			inline bool AutoShoot = false;
			inline float SilentFOV = 0.f;
			inline bool DrawSilent = false;

			inline bool IgnorePlayers;
			inline bool IgnoreSleepers;
			inline bool IgnoreWounded;
			inline bool IgnoreNPCs;
		}
		namespace Rage
		{
			inline bool Desync = false;
			inline bool ShowDesync = false;
			inline int DesyncKey = 0;
			inline bool InstantShoot = false;
			inline bool PowerShot = false;
		}
	}

	namespace Misc
	{
		inline bool Reloadindicator = false;
		inline bool FakeAdmin = false;
		inline bool OmniSprint = false;
		inline bool AlwaysSprint = false;
		inline bool CanAttack = false;
		inline bool NoFallDamage = false;
		inline bool NoBobbing = false;
		inline bool NoLowering = false;
		inline bool NoSwaying = false;
		inline bool GroundAngles = false;
		inline bool SilentWalk = false;
		inline bool InfJump = false;
		inline bool WalkOnWater = false;
		inline bool WalkThroughTrees = false;
		inline bool WalkThroughPlayers = false;
		inline bool JumpHigh = false;
		inline int CrosshairSize = 5; inline int CrosshairGap = 5; inline int CrosshairLength = 5; inline int CrosshairThickness = 5;//inline bool AnimateCrosshair = false; inline int CrosshairRotation = 0;
		inline bool Suicide = false; inline bool AlwaysSuicide = false; inline float SuicideRate = 1.f;
	}
}

namespace Vars
{
	inline bool MenuOnly = false;
	namespace Global
	{
		inline int BoneToAim = 1;
		inline float ScreenHigh = 0;
		inline float ScreenWidth = 0;
		inline bool MenuVisible = false;
	}

	namespace Color {
		inline float PlayerColor[] = { 0.f, 204.f, 204.f };
		inline float ChamColor[] = { 255.f, 255.f, 255.f, 255.f };
		inline float ScientistColor[] = { 255.f, 0.f, 0.f };
		inline float SleeperColor[] = { 255.f, 0.f, 0.f };
		inline float CrosshairColor[] = { 0.f, 255.f, 0.f };
		inline float Fov[] = { 255.f, 255.f, 255.f };
	}
}
