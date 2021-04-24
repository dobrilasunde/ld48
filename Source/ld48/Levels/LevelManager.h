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

private:
	ALevelPrototype* LoadLevel(const ELevelName& level);
	void UnloadCurrentLevel();

	APawn* FindPlayerPawn() const;

private:
	UPROPERTY(EditDefaultsOnly)
	ELevelName _initialLevel;

	UPROPERTY(EditDefaultsOnly)
	TMap<ELevelName, TSubclassOf<ALevelPrototype>> _levels;

private:
	UPROPERTY()
	ALevelPrototype* _currentLevelInstance = nullptr;

	ELevelName _currentLevel;
	TMap<ELevelName, bool> _levelsLocked;

};
/*----------------------------------------------------------------------------------------------------*/