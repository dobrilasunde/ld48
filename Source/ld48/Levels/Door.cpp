// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "Door.h"
#include "PaperSpriteComponent.h"
#include <Components/BoxComponent.h>
#include "LevelManager.h"
#include "../ld48WorldSettings.h"
#include "../Player/SuitPlayer.h"
/*----------------------------------------------------------------------------------------------------*/
ADoor::ADoor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	_doorSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Door Sprite"));
	_doorSprite->SetupAttachment(RootComponent);

	_lockedDoorsSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Locked Door Sprite"));
	_lockedDoorsSprite->SetupAttachment(RootComponent);

	_boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	_boxComponent->SetupAttachment(RootComponent);
}
/*----------------------------------------------------------------------------------------------------*/
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	if (_boxComponent != nullptr)
	{
		_boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	}

	ChooseRandomTargetLevel();

	if (Ald48WorldSettings* worldSettings = Cast<Ald48WorldSettings>(GetWorldSettings()))
	{
		if (ALevelManager* levelManager = worldSettings->GetLevelManager())
		{
			_isLocked = levelManager->IsLevelLocked(_targetLevel);
		}
	}

	OnIsLockedChanged();

	_isActive = false;
	GetWorldTimerManager().SetTimer(_isActiveTimerHandle, this, &ADoor::Activate, _activationTime);
}
/*----------------------------------------------------------------------------------------------------*/
void ADoor::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	GetWorldTimerManager().ClearTimer(_isActiveTimerHandle);

	Super::EndPlay(endPlayReason);
}
/*----------------------------------------------------------------------------------------------------*/
void ADoor::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (_isLocked || !_isActive)
	{
		return;
	}

	if (!otherActor->IsA<ASuitPlayer>())
	{
		return;
	}

	if (UBoxComponent* box = Cast<UBoxComponent>(otherComp))
	{
		// Ignore player's box. This sucks but it's easier.
		return;
	}

	Open();
}
/*----------------------------------------------------------------------------------------------------*/
void ADoor::OnIsLockedChanged()
{
	_lockedDoorsSprite->SetVisibility(_isLocked);
}
/*----------------------------------------------------------------------------------------------------*/
void ADoor::Open()
{
	Ald48WorldSettings* worldSetings = Cast<Ald48WorldSettings>(GetWorldSettings());
	if (worldSetings == nullptr)
	{
		return;
	}

	ALevelManager* levelManager = worldSetings->GetLevelManager();
	if (levelManager == nullptr)
	{
		return;
	}

	levelManager->SetCurrentLevel(_targetLevel);
}
/*----------------------------------------------------------------------------------------------------*/
void ADoor::Activate()
{
	_isActive = true;
}
/*----------------------------------------------------------------------------------------------------*/
void ADoor::ChooseRandomTargetLevel()
{
	if (_targetLevelsWithSpawnChance.Num() == 0)
	{
		return;
	}

	float chanceSum = 0.0f;
	for (const TPair<ELevelName, float>& pair : _targetLevelsWithSpawnChance)
	{
		chanceSum += pair.Value;
	}

	float randomNumber = FMath::RandRange(0.0f, chanceSum);
	for (const TPair<ELevelName, float>& pair : _targetLevelsWithSpawnChance)
	{
		if (pair.Value > randomNumber)
		{
			_targetLevel = pair.Key;
			return;
		}
		else
		{
			randomNumber -= pair.Value;
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/