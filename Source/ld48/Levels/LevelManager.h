// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "LevelShared.h"
#include "LevelPrototype.h"
#include "LevelManager.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ALevelManager : public AActor
{
	GENERATED_BODY()

public:
	ALevelManager();

public:
	virtual void BeginPlay() override;
	void SetCurrentLevel(const ELevelName& level);
	
	bool IsLevelLocked(const ELevelName& level) const;
	void LockLevel(const ELevelName& level);
	void UnlockLevel(const ELevelName& level);

	void ResetLevels();

	void OnEnemyDied();
	int32 GetRemainingEnemies() const;

	void Event_OnNPCDied();

private:
	ALevelPrototype* LoadLevel(const ELevelName& level);
	void UnloadCurrentLevel();

	APawn* FindPlayerPawn() const;

	int32 GetCurrentLevelEnemySpawnAmount() const;

private:
	UPROPERTY(EditDefaultsOnly)
	ELevelName _initialLevel;

	UPROPERTY(EditDefaultsOnly)
	TMap<ELevelName, TSubclassOf<ALevelPrototype>> _levels;

	UPROPERTY(EditDefaultsOnly)
	int32 _remainingEnemies = 100;

	UPROPERTY(EditDefaultsOnly)
	int32 _currentMaxEnemySpawnAmount = 8;

	UPROPERTY(EditDefaultsOnly)
	float _enemySpawnAmountPercentIncreasePerLevel = 1.3;

private:
	UPROPERTY()
	ALevelPrototype* _currentLevelInstance = nullptr;

	ELevelName _currentLevel;
	TMap<ELevelName, bool> _levelsLocked;

};
/*----------------------------------------------------------------------------------------------------*/