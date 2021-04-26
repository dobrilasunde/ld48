// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "LevelGridCell.h"
#include "LevelPrototype.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class ALevelGridGenerator;
class ANPC;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ALevelPrototype : public AActor
{
	GENERATED_BODY()

public:
	ALevelPrototype();

	void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Tick(float deltaTime) override;

	const FVector& GetPlayerStartLocation() const;

	void SpawnEnemies(int32 amount);

// Events
public:
	UPROPERTY(EditAnywhere, Category = "LevelPrototype")
	FVector _defaultPlayerStartLocation = FVector(0.f, 5.f, 0.f);

private:
	void ShuffleSpawners(TArray<FVector>& Array);

	FSpawnMarker* ChooseRandomSpawner();

private:
	UPROPERTY()
	ALevelGridGenerator* _levelGridGenerator;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ALevelGridGenerator> _levelGridGeneratorClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ANPC> _enemyClass;
};
/*----------------------------------------------------------------------------------------------------*/