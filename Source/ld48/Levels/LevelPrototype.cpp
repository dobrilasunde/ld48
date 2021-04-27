// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "LevelPrototype.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"
#include "Engine/CollisionProfile.h"
#include "LevelGridGenerator.h"
#include "../NPC/NPC.h"
/*----------------------------------------------------------------------------------------------------*/
ALevelPrototype::ALevelPrototype()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelPrototype::BeginPlay()
{
	Super::BeginPlay();

	if (_levelGridGeneratorClass)
	{
		_levelGridGenerator = GetWorld()->SpawnActor<ALevelGridGenerator>(_levelGridGeneratorClass);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelPrototype::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	_levelGridGenerator->Destroy();

	for (ANPC* enemy : _spawnedEnemies)
	{
		if (!enemy->IsPendingKill())
		{
			enemy->Destroy();
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelPrototype::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}
/*----------------------------------------------------------------------------------------------------*/
const FVector& ALevelPrototype::GetPlayerStartLocation() const
{
	if (_levelGridGenerator == nullptr)
	{
		return _defaultPlayerStartLocation;
	}

	return _levelGridGenerator->GetPlayerStartLocation();
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelPrototype::SpawnEnemies(int32 amount)
{
	if (_levelGridGenerator == nullptr)
	{
		return;
	}

	if (_enemyClass == nullptr)
	{
		return;
	}

	for (int32 i = 0; i < amount; i++) 
	{
		FSpawnMarker* spawnMarker = ChooseRandomSpawner();
		if (spawnMarker == nullptr)
		{
			continue;
		}

		if (ANPC* SpawnedEnemy = GetWorld()->SpawnActor<ANPC>(_enemyClass, spawnMarker->SpawnLocation, FRotator::ZeroRotator))
		{
			_spawnedEnemies.Add(SpawnedEnemy);
			spawnMarker->IsSpawned = true;
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelPrototype::Event_OnNPCDied()
{
	if (_levelGridGenerator)
	{
		_levelGridGenerator->Event_OnNPCDied();
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelPrototype::ShuffleSpawners(TArray<FVector>& Array)
{
	if (Array.Num() == 0)
	{
		return;
	}

	int32 LastIndex = Array.Num() - 1;
	for (int32 i = 0; i <= LastIndex; ++i)
	{
		int32 j = FMath::RandRange(i, LastIndex);
		if (i != j)
		{
			Array.Swap(i, j);
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
FSpawnMarker* ALevelPrototype::ChooseRandomSpawner()
{
	if (_levelGridGenerator == nullptr)
	{
		return nullptr;
	}

	TArray<FSpawnMarker>& SpawnMarkers = _levelGridGenerator->GetAllSpawnMarkers();
	if (SpawnMarkers.Num() == 0)
	{
		return nullptr;
	}

	int32 sumWeight = 0;
	for (int32 i = 0; i < SpawnMarkers.Num(); i++)
	{
		if (SpawnMarkers[i].IsSpawned)
		{
			continue;
		}

		sumWeight += SpawnMarkers[i].Weight;
	}

	int32 randomNumber = FMath::RandRange(0, sumWeight);
	int32 cumulativeWeight = 0;
	for (int32 i = 0; i < SpawnMarkers.Num(); i++)
	{
		if (SpawnMarkers[i].IsSpawned)
		{
			continue;
		}

		cumulativeWeight += SpawnMarkers[i].Weight;
		if (cumulativeWeight > randomNumber)
		{
			return &SpawnMarkers[i];
		}
	}

	return nullptr;
}
/*----------------------------------------------------------------------------------------------------*/
