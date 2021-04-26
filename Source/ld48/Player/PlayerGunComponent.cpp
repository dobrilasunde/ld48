// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "PlayerGunComponent.h"
#include "Projectile.h"
#include "SuitPlayer.h"
#include "SuitPlayerController.h"
/*----------------------------------------------------------------------------------------------------*/
void UPlayerGunComponent::Shoot(FVector direction)
{
	if (_ammoCount <= 0)
	{
		if (ASuitPlayer* owner = Cast<ASuitPlayer>(GetOwner()))
		{
			owner->SetHasGun(false);
		}
		return;
	}

	SpawnProjectile(direction);

	_ammoCount--;

	if (ASuitPlayer* owner = Cast<ASuitPlayer>(GetOwner()))
	{
		owner->UpdateUI();
	}
}
/*----------------------------------------------------------------------------------------------------*/
int32 UPlayerGunComponent::GetAmmoCount() const
{
	return _ammoCount;
}
/*----------------------------------------------------------------------------------------------------*/
void UPlayerGunComponent::SetAmmoCount(int32 value)
{
	_ammoCount = value;

	if (_ammoCount > 0)
	{
		if (ASuitPlayer* owner = Cast<ASuitPlayer>(GetOwner()))
		{
			owner->SetHasGun(true);
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void UPlayerGunComponent::SpawnProjectile(FVector direction)
{
	if (_projectileClass == nullptr)
	{
		return;
	}

	FVector newLocation = GetComponentLocation() + direction * _projectileSpawnOffset;
	FVector newDirection = direction * _projectileSpeed;
	FMatrix rotationMatrix = FRotationMatrix::MakeFromXY(newDirection, FVector::RightVector);

	FActorSpawnParameters spawnParameters;
	spawnParameters.Owner = GetOwner();
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(_projectileClass, newLocation, rotationMatrix.Rotator(), spawnParameters);

// 	if (ASuitPlayer* Player = Cast<ASuitPlayer>(GetOwner()))
// 	{
// 		if (ASuitPlayerController* PlayerController = Cast<ASuitPlayerController>(Player->GetController()))
// 		{
// 			projectile->SetDirection(PlayerController->GetPlayerDirection());
// 		}
// 	}
}
/*----------------------------------------------------------------------------------------------------*/