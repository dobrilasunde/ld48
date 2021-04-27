// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "LevelManager.h"
#include "LevelPrototype.h"
#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>
/*----------------------------------------------------------------------------------------------------*/
ALevelManager::ALevelManager()
{

}
/*----------------------------------------------------------------------------------------------------*/
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();

	// Init level locked status
	_levelsLocked.Emplace(ELevelName::LevelOffice, false);
	_levelsLocked.Emplace(ELevelName::LevelElevator, true);
	_levelsLocked.Emplace(ELevelName::LevelGarage, false);
	_levelsLocked.Emplace(ELevelName::LevelStairs, true);
	_levelsLocked.Emplace(ELevelName::LevelOfficeElevator, false);
	_levelsLocked.Emplace(ELevelName::FinalLevel, true);

	SetCurrentLevel(_initialLevel);
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelManager::SetCurrentLevel(const ELevelName& level)
{
	UnloadCurrentLevel();
	_currentLevelInstance = LoadLevel(level);
	_currentLevel = level;
	_currentLevelInstance->SpawnEnemies(GetCurrentLevelEnemySpawnAmount());

	if (_currentLevelInstance != nullptr)
	{
		if (APawn* playerPawn = FindPlayerPawn())
		{
			playerPawn->SetActorLocation(_currentLevelInstance->GetPlayerStartLocation());
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
bool ALevelManager::IsLevelLocked(const ELevelName& level) const
{
	const bool* valuePtr = _levelsLocked.Find(level);
	if (valuePtr == nullptr)
	{
		return false;
	}

	return *valuePtr;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelManager::LockLevel(const ELevelName& level)
{
	_levelsLocked.FindOrAdd(level) = true;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelManager::UnlockLevel(const ELevelName& level)
{
	_levelsLocked.FindOrAdd(level) = false;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelManager::ResetLevels()
{
	for (uint8 i = 0; i < (uint8)ELevelName::Count; ++i)
	{
		LockLevel((ELevelName)i);
	}

	UnlockLevel(ELevelName::LevelOffice);
	UnlockLevel(ELevelName::LevelElevator);

	SetCurrentLevel(ELevelName::LevelOffice);
}
/*----------------------------------------------------------------------------------------------------*/
ALevelPrototype* ALevelManager::LoadLevel(const ELevelName& level)
{
	if (level == ELevelName::LevelGarage)
	{
		_currentMaxEnemySpawnAmount = _currentMaxEnemySpawnAmount * _enemySpawnAmountPercentIncreasePerLevel;
	}

	// Final level
	if (_remainingEnemies == 0 && level == ELevelName::LevelGarage)
	{
		if (TSubclassOf<ALevelPrototype>* levelPtr = _levels.Find(ELevelName::FinalLevel))
		{
			TSubclassOf<ALevelPrototype> levelPrototypeClass = *levelPtr;

			UWorld* world = GetWorld();
			if (world == nullptr)
			{
				return nullptr;
			}

			UObject* CDO = levelPrototypeClass->GetDefaultObject();
			if (CDO == nullptr)
			{
				return nullptr;
			}

			return world->SpawnActor<ALevelPrototype>(CDO->GetClass(), FVector::ZeroVector, FQuat::Identity.Rotator());
		}
	}
	else if (TSubclassOf<ALevelPrototype>* levelPtr = _levels.Find(level))
	{
		TSubclassOf<ALevelPrototype> levelPrototypeClass = *levelPtr;

		UWorld* world = GetWorld();
		if (world == nullptr)
		{
			return nullptr;
		}

		UObject* CDO = levelPrototypeClass->GetDefaultObject();
		if (CDO == nullptr)
		{
			return nullptr;
		}

		return world->SpawnActor<ALevelPrototype>(CDO->GetClass(), FVector::ZeroVector, FQuat::Identity.Rotator());
	}

	return nullptr;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelManager::UnloadCurrentLevel()
{
	if (_currentLevelInstance == nullptr)
	{
		return;
	}

	_currentLevelInstance->Destroy();
	_currentLevelInstance = nullptr;
}
/*----------------------------------------------------------------------------------------------------*/
APawn* ALevelManager::FindPlayerPawn() const
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);
	if (pc == nullptr)
	{
		return nullptr;
	}

	return pc->GetPawn();
}
/*----------------------------------------------------------------------------------------------------*/
int32 ALevelManager::GetCurrentLevelEnemySpawnAmount() const
{
	int32 newRemainingEnemies = _remainingEnemies - _currentMaxEnemySpawnAmount;
	return newRemainingEnemies > 0 ? _currentMaxEnemySpawnAmount : _remainingEnemies;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelManager::OnEnemyDied()
{
	_remainingEnemies = FMath::Max(_remainingEnemies - 1, 0);
}
/*----------------------------------------------------------------------------------------------------*/
int32 ALevelManager::GetRemainingEnemies() const
{
	return _remainingEnemies;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelManager::Event_OnNPCDied()
{
	if (_currentLevelInstance != nullptr)
	{
		_currentLevelInstance->Event_OnNPCDied();
	}
}
/*----------------------------------------------------------------------------------------------------*/