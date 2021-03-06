namespace Hooks
{
	void     hk_Launch(UINT_PTR);
	void     hk_ProjectileMovement(UINT_PTR, float);
	bool     hk_IsWaterMaterial(UINT_PTR, UINT_PTR);
	void     hk_OnAttacked(UINT_PTR, UINT_PTR);
	void     hk_DoHitNotify(UINT_PTR, UINT_PTR);
	void     hk_DoAttack(UINT_PTR);
	void     hk_SetFlying(UINT_PTR);
	void     hk_UpdateGravity(UINT_PTR, UINT_PTR);
	void     hk_OnLand(UINT_PTR, float);
	void     hk_EditViewAngles(UINT_PTR);
	void     hk_FrameUpdate(UINT_PTR, bool);
	void     hk_HandleJumping(UINT_PTR, UINT_PTR, bool, bool);
	void     hk_OnCameraPositionChanged(UINT_PTR, UINT_PTR, UINT_PTR);
	void     hk_HandleRunDuckCrawl(UINT_PTR, UINT_PTR, bool, bool, bool);
	void     hk_ViewModelPlay(UINT_PTR, pUncStr, int);
	bool     hk_CanHoldItems(UINT_PTR);
	bool     hk_CanAttack(UINT_PTR);
	bool     hk_GetIsHeadshot(UINT_PTR);
	void     hk_SendProjectileAttack(UINT_PTR, UINT_PTR);
	bool     hk_DoHit(UINT_PTR, UINT_PTR, Vector3, Vector3);
	void     hk_EokaDoAttack(UINT_PTR);
	void     hk_OnGUI(UINT_PTR);
	Vector3  hk_MoveTowards(Vector3, Vector3, float);
	void     hk_AddPunch(UINT_PTR, Vector3, float);
	void     hk_ClientInput(UINT_PTR, UINT_PTR);
	bool     hk_FakeShouldShowHud();
	void	 hk_FakeVisUpdateUsingCulling(void*, float, bool);
	UINT_PTR hk_FakeCreateProjectile(void*, void*, Vector3, Vector3, Vector3);
	Vector3  hk_FakeGetModifiedAimConeDirection(float, Vector3, bool);
}