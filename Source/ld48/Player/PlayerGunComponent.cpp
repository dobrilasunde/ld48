// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "PlayerGunComponent.h"
#include "Projectile.h"
/*----------------------------------------------------------------------------------------------------*/
void UPlayerGunComponent::Shoot(FVector direction)
{
	if (_ammoCount <= 0)
	{
		return;
	}

	SpawnProjectile(direction);

	_ammoCount--;
}
/*----------------------------------------------------------------------------------------------------*/
void UPlayerGunComponent::SpawnProjectile(FVector direction)
{
	if (_projectileClass == nullptr)
	{
		return;
	}

	if (AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(_projectileClass))
	{
		projectile->Launch(GetComponentLocation() + direction * _projectileSpawnOffset, direction * _projectileSpeed);
	}
}
/*----------------------------------------------------------------------------------------------------*/