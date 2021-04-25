// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "Projectile.h"
/*----------------------------------------------------------------------------------------------------*/
AProjectile::AProjectile()
{
	SetActorTickEnabled(true);
}
/*----------------------------------------------------------------------------------------------------*/
void AProjectile::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	// integrate
	FVector newLocation = GetActorLocation() + _velocity * deltaTime;
	SetActorLocation(newLocation);
}
/*----------------------------------------------------------------------------------------------------*/
void AProjectile::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	Destroy();
}
/*----------------------------------------------------------------------------------------------------*/
void AProjectile::Launch(FVector location, FVector velocity)
{
	SetActorLocation(location);
	_velocity = velocity;
}
/*----------------------------------------------------------------------------------------------------*/
