// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "Projectile.h"
#include "PlayerGunComponent.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API UPlayerGunComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	void Shoot(FVector direction);
	int32 GetAmmoCount() const;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> _projectileClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float _projectileSpeed = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float _projectileSpawnOffset = 0.f;

	UPROPERTY(EditAnywhere)
	int32 _ammoCount = 0;

	int32 _lastShootTimestamp = 0;

private:
	void SpawnProjectile(FVector direction);
};
/*----------------------------------------------------------------------------------------------------*/