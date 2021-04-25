// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "LevelPrototype.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"
#include "Engine/CollisionProfile.h"
#include "LevelGridGenerator.h"
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
void ALevelPrototype::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}
/*----------------------------------------------------------------------------------------------------*/
const FVector& ALevelPrototype::GetPlayerStartLocation() const
{
	return _playerStartLocation;
}
/*----------------------------------------------------------------------------------------------------*/
