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

	TArray<FVector> spawnLocations = _levelGridGenerator->GetSpawnLocations();
	if (spawnLocations.Num() == 0)
	{
		return;
	}

	ShuffleSpawners(spawnLocations);

	for (int32 i = 0; i < amount; ++i)
	{
		GetWorld()->SpawnActor<ANPC>(_enemyClass, spawnLocations[i], FRotator::ZeroRotator);
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
