// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "NPC.h"
#include "BossNPC.generated.h"
/*----------------------------------------------------------------------------------------------------*/
 class APickup;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ABossNPC : public ANPC
{
	GENERATED_BODY()

public:
	ABossNPC();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	virtual void MoveToTarget(AActor* target) override;
	virtual void OnArrivedToTarget(AActor* target) override;
	virtual void AttackTarget(AActor* target) override;

	virtual void OnDeathAnimationFinishedPlaying() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UPROPERTY(EditAnywhere)
	TSubclassOf<APickup> _pickupClass;
};
/*----------------------------------------------------------------------------------------------------*/