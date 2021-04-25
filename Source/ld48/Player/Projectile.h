// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "Projectile.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();
	virtual void Tick(float deltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;

public:
	void Launch(FVector location, FVector velocity);

private:
	FVector _velocity;
};
/*----------------------------------------------------------------------------------------------------*/