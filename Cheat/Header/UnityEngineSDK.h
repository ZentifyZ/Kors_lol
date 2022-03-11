#pragma once

inline UINT_PTR getComponent(UINT_PTR gameObject, char* componentName)
{
	__try
	{
		//Ulog("%s - getComponent called", __FUNCTION__);

		if (gameObject == 0) return 0;
		auto componentList = *(UINT_PTR*)(gameObject + 0x30); if (!componentList) return 0;
		for (int h = 0; h < 20; h++)
		{
			auto listItem = *(UINT_PTR*)(componentList + 0x10 * h + 0x8); if (!listItem) continue;
			auto componentclass = *(UINT_PTR*)(listItem + 0x28); if (!componentclass) continue;
			auto ClassNameBuffer = *(pUncStr*)(*(UINT_PTR*)(componentclass + 0x0) + 0x10); if (!ClassNameBuffer) continue;
			auto ClassName = ClassNameBuffer->stub; if (!ClassName) continue;
			if (strstr(ClassName, componentName))
			{
				return componentclass;
			}
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return 0;
}

inline double CalcBulletDrop(double height, double DepthPlayerTarget, float velocity, float gravity) {
	double pitch = (my_atan2(height, DepthPlayerTarget));
	double BulletVelocityXY = velocity * my_cos(pitch);
	double Time = DepthPlayerTarget / BulletVelocityXY;
	double TotalVerticalDrop = (0.4905f * gravity * Time * Time);
	return TotalVerticalDrop * 10;
}

inline void Prediction(Vector3 local, Vector3& target, Vector3 targetvel, float bulletspeed, float gravity) {
	float Dist = target.distance(local);
	float BulletTime = Dist / bulletspeed;
	Vector3 vel = Vector3(targetvel.x, 0, targetvel.z) * 0.75f;
	Vector3 PredictVel = vel * BulletTime;
	target += PredictVel;
	float height = target.y - local.y;
	Vector3 dir = target - local;
	float DepthPlayerTarget = my_sqrt((dir.x * dir.x) + (dir.z * dir.z));
	float drop = CalcBulletDrop(height, DepthPlayerTarget, bulletspeed, gravity);
	target.y += drop;
}

namespace UnityEngine
{
	inline float get_realtimeSinceStartup()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Time", "get_realtimeSinceStartup");
			}

			typedef float Method();
			return ((Method*)(Globals::g_GameAssemblyBase + var))();
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	inline Vector3 get_gravity()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.PhysicsModule", "UnityEngine", "Physics", "get_gravity");
			}

			typedef Vector3 Method();
			return ((Method*)(Globals::g_GameAssemblyBase + var))();
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}

	inline float get_timeScale()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Time", "get_timeScale");
			}

			typedef float Method();
			return ((Method*)(Globals::g_GameAssemblyBase + var))();
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	inline float get_fixedDeltaTime()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Time", "get_fixedDeltaTime");
			}

			typedef float Method();
			return ((Method*)(Globals::g_GameAssemblyBase + var))();
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	inline void RebuildAll()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerModel", "RebuildAll");
			}

			typedef void Method();
			((Method*)(Globals::g_GameAssemblyBase + var))();
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	inline UINT_PTR asset_bundle = 0x402402;

	inline UINT_PTR LoadAssetBundle(Str string)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.AssetBundleModule", "UnityEngine", "AssetBundle", "LoadFromFile_Internal");
			}

			typedef UINT_PTR Method(Str, UINT_PTR, UINT_PTR);
			asset_bundle = ((Method*)(Globals::g_GameAssemblyBase + var))(string, 0, 0);
			return asset_bundle;
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	inline void UnLoadAssetBundle(UINT_PTR assetbundle, bool unloadAllLoadedObjects)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.AssetBundleModule", "UnityEngine", "AssetBundle", "Unload");
			}

			typedef void Method(UINT_PTR, bool);
			((Method*)(Globals::g_GameAssemblyBase + var))(assetbundle, unloadAllLoadedObjects);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	inline UINT_PTR LoadAsset(UINT_PTR bundle, Str string)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.AssetBundleModule", "UnityEngine", "AssetBundle", "LoadAsset_Internal");
			}

			typedef UINT_PTR Method(UINT_PTR, Str, UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(bundle, string, Dumper::GetObjectType("UnityEngine.CoreModule", "UnityEngine", "Shader"));
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	inline UINT_PTR GetComponent(UINT_PTR gameObject, UINT_PTR type)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "", "Component", "GetComponent");
			}

			typedef UINT_PTR Method(UINT_PTR, UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(gameObject, type);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	inline void DDrawGet()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "UnityEngine", "DDraw", "Get");
			}

			typedef void Method();
			((Method*)(Globals::g_GameAssemblyBase + var))();
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	inline void DrawLabel(Rect position, char* text)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.IMGUIModule", "UnityEngine", "GUI", "Label", 2);
			}

			const size_t cSize = strlen(text) + 1;
			wchar_t* wc = new wchar_t[cSize];
#pragma warning(suppress : 4996)
			mbstowcs(wc, text, cSize);

			typedef void Method(Rect, Str);
			((Method*)(Globals::g_GameAssemblyBase + var))(position, Str(wc));
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	inline UINT_PTR get_whiteTexture()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Texture2D", "get_whiteTexture");
			}

			typedef UINT_PTR Method();
			return ((Method*)(Globals::g_GameAssemblyBase + var))();
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	inline Color GetColor()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.IMGUIModule", "UnityEngine", "GUI", "get_color");
			}

			typedef Color Method();
			return ((Method*)(Globals::g_GameAssemblyBase + var))();
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Color(0, 0, 0, 0);
	}

	inline void SetColor(Color color)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.IMGUIModule", "UnityEngine", "GUI", "set_color");
			}

			typedef void Method(Color);
			((Method*)(Globals::g_GameAssemblyBase + var))(color);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	inline void DrawTexture(Rect position, UINT_PTR texture)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.IMGUIModule", "UnityEngine", "GUI", "DrawTexture", 2);
			}

			typedef void Method(Rect, UINT_PTR);
			((Method*)(Globals::g_GameAssemblyBase + var))(position, texture);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	inline void SendSignalBroadcast(UINT_PTR heldEntity, Signal signal, Str arg = Str(L""))
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseEntity", "SendSignalBroadcast");
			}

			typedef void Method(UINT_PTR, Signal, Str);
			((Method*)(Globals::g_GameAssemblyBase + var))(heldEntity, signal, arg);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	inline void IgnoreLayerCollision(int layer1, int layer2, bool ignore)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				auto processAddress = GetProcAddress(GetModuleHandleA("GameAssembly.dll"), "il2cpp_resolve_icall");
				if (!processAddress) return;
				var = reinterpret_cast<UINT_PTR(__fastcall*)(char*)>(processAddress)("UnityEngine.Physics::IgnoreLayerCollision");
			}

			typedef void Method(int, int, bool);
			((Method*)(var))(layer1, layer2, ignore);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	inline bool CheckCapsule(Vector3 start, Vector3 end, float radius, int layerMask)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.PhysicsModule", "UnityEngine", "Physics", "CheckCapsule", 5);
			}

			typedef bool Method(Vector3, Vector3, float, int, int);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(start, end, radius, layerMask, 1);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}

	inline bool LineOfSight(Vector3 p0, Vector3 p1, int layerMask = 0, float padding = 0.f)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "GamePhysics", "LineOfSight", 4);
			}

			layerMask = Settings::Combat::WeaponMods::Penetrate ? 10551296 : 1503731969;

			typedef bool Method(Vector3, Vector3, int, float);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(p0, p1, layerMask, padding);;
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}
}
