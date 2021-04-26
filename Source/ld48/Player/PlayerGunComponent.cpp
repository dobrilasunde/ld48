// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "PlayerGunComponent.h"
#include "Projectile.h"
#include "SuitPlayer.h"
/*----------------------------------------------------------------------------------------------------*/
void UPlayerGunComponent::Shoot(FVector direction)
{
	if (_ammoCount <= 0)
	{
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

// 	if (AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(_projectileClass))
// 	{
// 		projectile->Launch(GetComponentLocation() + direction * _projectileSpawnOffset, direction * _projectileSpeed);
// 	}
}
/*----------------------------------------------------------------------------------------------------*/