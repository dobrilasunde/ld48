// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "SuitPlayer.h"
#include "../Camera/PixelCamera.h"
#include <Camera/PlayerCameraManager.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "PaperFlipbookComponent.h"
#include "../NPC/NPC.h"
#include "SuitPlayerController.h"
#include <Camera/CameraShake.h>
#include "PlayerGunComponent.h"
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

	_gunComponent = CreateDefaultSubobject<UPlayerGunComponent>(TEXT("GunComponent"));
	_gunComponent->SetupAttachment(RootComponent);
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
void ASuitPlayer::OnMeleeAttackAnimationFinishedPlaying()
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
void ASuitPlayer::MeleeAttack(EMovablePawnDirection attackDirection)
{
	if (_meleeAttackHitBox == nullptr)
	{
		return;
	}

	TArray<AActor*> overlappingActors;
	_meleeAttackHitBox->GetOverlappingActors(overlappingActors);
	for (AActor* overlappingActor : overlappingActors)
	{
		if (ANPC* npc = Cast<ANPC>(overlappingActor))
		{
			if (npc->GetHealth() > 0.f)
			{
				npc->ApplyDamage(attackDirection);
				ShakeCamera();
				return;
			}
		}
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, *overlappingActor->GetName());
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::Shoot(EMovablePawnDirection attackDirection)
{
	if (_gunComponent != nullptr)
	{
		FVector direction = GetActorForwardVector();
		if (attackDirection == EMovablePawnDirection::Left)
		{
			direction *= -1.f;
		}

		_gunComponent->Shoot(direction);
	}
}
/*----------------------------------------------------------------------------------------------------*/
UPaperFlipbookComponent* ASuitPlayer::GetMeleeAttackFlipbookComponent() const
{
	return _meleeAttackFlipbookComponent;
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::ApplyDamage(float damage)
{
	if (!_canTakeDamage)
	{
		return;
	}

	if (_spriteMatInst != nullptr)
	{
		_spriteMatInst->SetScalarParameterValue("BlinkIntensity", 1.f);
	}

	_canTakeDamage = false;

	GetWorldTimerManager().SetTimer(_invulnerabilityTimer, this, &ASuitPlayer::OnInvulnerabilityTimer, _invulnerabilityOnDamageDuration);
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void ASuitPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		if (APixelCamera* cam = Cast<APixelCamera>(camManager->GetViewTarget()))
		{
			cam->SetTargetActor(this);
		}
	}

	if (UPaperFlipbookComponent* flipbook = GetSprite())
	{
		if (_spriteMaterial != nullptr)
		{
			_spriteMatInst = UMaterialInstanceDynamic::Create(_spriteMaterial, this);
			flipbook->SetMaterial(0, _spriteMatInst);
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
void ASuitPlayer::ShakeCamera()
{
	if (_verticalCameraShake == nullptr || _horizontalCameraShake == nullptr)
	{
		return;
	}

	ASuitPlayerController* PlayerController = Cast<ASuitPlayerController>(GetController());
	if (PlayerController == nullptr)
	{
		return;
	}

	APlayerCameraManager* PlayerCameraManager = PlayerController->PlayerCameraManager;
	if (PlayerCameraManager == nullptr)
	{
		return;
	}

	if (PlayerController->GetPlayerDirection() == EMovablePawnDirection::Left || PlayerController->GetPlayerDirection() == EMovablePawnDirection::Right)
	{
		PlayerCameraManager->PlayCameraShake(_horizontalCameraShake, 1.0f);
	}
	else
	{
		PlayerCameraManager->PlayCameraShake(_verticalCameraShake, 1.0f);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::OnInvulnerabilityTimer()
{
	_canTakeDamage = true;

	if (_spriteMatInst != nullptr)
	{
		_spriteMatInst->SetScalarParameterValue("BlinkIntensity", 0.f);
	}
}
/*----------------------------------------------------------------------------------------------------*/