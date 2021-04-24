// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "SuitPlayer.h"
#include "PaperFlipbookComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Camera/PlayerCameraManager.h>
#include "../Camera/PixelCamera.h"
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
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::Attack()
{

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