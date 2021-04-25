// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "LevelPrototype.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class ALevelGridGenerator;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ALevelPrototype : public AActor
{
	GENERATED_BODY()

public:
	ALevelPrototype();

	void BeginPlay() override;
	void Tick(float deltaTime) override;

	const FVector& GetPlayerStartLocation() const;

// Events
public:


private:
	UPROPERTY(EditAnywhere, Category = "LevelPrototype")
	FVector _playerStartLocation = FVector(0.f, 5.f, 0.f);

	UPROPERTY()
	ALevelGridGenerator* _levelGridGenerator;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ALevelGridGenerator> _levelGridGeneratorClass;
};
/*----------------------------------------------------------------------------------------------------*/