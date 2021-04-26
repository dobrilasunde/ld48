// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "LevelShared.h"
#include <Engine/EngineTypes.h>
#include "Door.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UBoxComponent;
class UPaperSpriteComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	ADoor();

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	void OnIsLockedChanged();
	void Open();

	void Activate();

	void ChooseRandomTargetLevel();

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<ELevelName, float> _targetLevelsWithSpawnChance;

	UPROPERTY()
	ELevelName _targetLevel;

	UPROPERTY(EditDefaultsOnly)
	float _activationTime = -1.f;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* _doorSprite;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* _lockedDoorsSprite;

	UPROPERTY(EditAnywhere)
	UBoxComponent* _boxComponent;

private:
	bool _isLocked = false;
	bool _isActive = false;
	FTimerHandle _isActiveTimerHandle;
};
/*----------------------------------------------------------------------------------------------------*/