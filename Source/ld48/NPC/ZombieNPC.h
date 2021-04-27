// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "NPC.h"
#include "ZombieNPC.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class APickup;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API AZombieNPC : public ANPC
{
	GENERATED_BODY()

public:
	AZombieNPC();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	virtual void MoveToTarget(AActor* target) override;
	virtual void OnArrivedToTarget(AActor* target) override;
	virtual void AttackTarget(AActor* target) override;

	virtual void OnDeathAnimationFinishedPlaying() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APickup> _pickupClass;

	UPROPERTY(EditAnywhere)
	float _dropChance = 0.1f;
};
/*----------------------------------------------------------------------------------------------------*/