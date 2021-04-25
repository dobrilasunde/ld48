// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "SuitPlayer.h"
#include "../Camera/PixelCamera.h"
#include <Camera/PlayerCameraManager.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "PaperFlipbookComponent.h"
/*----------------------------------------------------------------------------------------------------*/
ASuitPlayer::ASuitPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	_meleeAttackFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MeleeAttackFlipbook"));
	_meleeAttackFlipbookComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_meleeAttackFlipbookComponent->Stop();
	_meleeAttackFlipbookComponent->SetLooping(false);
	_meleeAttackFlipbookComponent->SetHiddenInGame(true);

	_meleeAttackHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeHitBox"));
	_meleeAttackHitBox->SetupAttachment(_meleeAttackFlipbookComponent);
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::SetFlipbook(EMovablePawnState playerState, EMovablePawnDirection playerDirection)
{
	UPaperFlipbookComponent* flipbook = GetSprite();
	if (flipbook == nullptr)
	{
		return;
	}

	if (playerState == EMovablePawnState::Idle)
	{
		switch (playerDirection)
		{
		case EMovablePawnDirection::Right:
		{
			if (_idleRightFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_idleRightFlipbook);
				flipbook->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
			}
			break;
		}
		case EMovablePawnDirection::Left:
		{
			if (_idleLeftFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_idleLeftFlipbook);
				flipbook->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
			}
			break;
		}
		case EMovablePawnDirection::Back:
		{
			if (_idleUpFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_idleUpFlipbook);
			}
			break;
		}
		case EMovablePawnDirection::Front:
		{
			if (_idleDownFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_idleDownFlipbook);
			}
			break;
		}
		}
	}
	else if (playerState == EMovablePawnState::Walking)
	{
		switch (playerDirection)
		{
		case EMovablePawnDirection::Right:
		{
			if (_walkRightFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_walkRightFlipbook);
				flipbook->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
			}
			break;
		}
		case EMovablePawnDirection::Left:
		{
			if (_walkLeftFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_walkLeftFlipbook);
				flipbook->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
			}
			break;
		}
		case EMovablePawnDirection::Back:
		{
			if (_walkUpFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_walkUpFlipbook);
			}
			break;
		}
		case EMovablePawnDirection::Front:
		{
			if (_walkDownFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_walkDownFlipbook);
			}
			break;
		}
		}
	}
	else if (playerState == EMovablePawnState::Attacking)
	{
		if (playerDirection == EMovablePawnDirection::Left)
		{
			_meleeAttackFlipbookComponent->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
		}
		else if (playerDirection == EMovablePawnDirection::Right)
		{
			_meleeAttackFlipbookComponent->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
		}

		flipbook->SetHiddenInGame(true);
		_meleeAttackFlipbookComponent->SetHiddenInGame(false);
		_meleeAttackFlipbookComponent->PlayFromStart();
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::MeleeAttack()
{
	if (_meleeAttackFlipbookComponent)
	{
		_meleeAttackFlipbookComponent->SetHiddenInGame(true);
	}

	if (UPaperFlipbookComponent* flipbook = GetSprite())
	{
		flipbook->SetHiddenInGame(false);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::StartWalk()
{

}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::StopWalk()
{

}
/*----------------------------------------------------------------------------------------------------*/
UPaperFlipbookComponent* ASuitPlayer::GetMeleeAttackFlipbookComponent() const
{
	return _meleeAttackFlipbookComponent;
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void ASuitPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		AActor* a = camManager->GetViewTarget();
		if (a == nullptr)
		{
			;
		}
		if (APixelCamera* cam = Cast<APixelCamera>(a))
		{
			cam->SetTargetActor(this);
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void ASuitPlayer::PossessedBy(AController* newController)
{
	Super::PossessedBy(newController);

	if (APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		AActor* a = camManager->GetViewTarget();
		if (a == nullptr)
		{
			;
		}
		if (APixelCamera* cam = Cast<APixelCamera>(a))
		{
			cam->SetTargetActor(this);
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float unitsPerPixel = 1.f / _pixelsPerUnit;

	FVector location = GetActorLocation();
	location.X = FMath::GridSnap(location.X, unitsPerPixel);
	location.Z = FMath::GridSnap(location.Z, unitsPerPixel);
	SetActorLocation(location);
}
/*----------------------------------------------------------------------------------------------------*/