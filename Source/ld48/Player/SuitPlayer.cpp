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
#include "../UI/ldjam48HUD.h"
#include "../UI/HudWidget.h"
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

	if (_meleeAttackHitBox == nullptr)
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
				flipbook->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			}
			break;
		}
		case EMovablePawnDirection::Left:
		{
			if (_idleLeftFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_idleLeftFlipbook);
				flipbook->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
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
				flipbook->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			}
			break;
		}
		case EMovablePawnDirection::Left:
		{
			if (_walkLeftFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_walkLeftFlipbook);
				flipbook->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
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
			_meleeAttackFlipbookComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
		else if (playerDirection == EMovablePawnDirection::Right)
		{
			_meleeAttackFlipbookComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
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
void ASuitPlayer::ApplyDamage(EMovablePawnDirection direction, float damage)
{
	if (_isInvincible)
	{
		return;
	}

	ASuitPlayerController* PlayerController = Cast<ASuitPlayerController>(GetController());
	if (PlayerController == nullptr)
	{
		return;
	}

	/*if(GetOppositeDirection(direction) == PlayerController->GetPlayerDirection())
	{
		return;
	}*/

	SetHealth(_health - damage);

	OnDamageTaken();
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::SetHealth(float health)
{
	if (_health == health)
	{
		return;
	}

	_health = health;
	_health = FMath::Clamp(_health, 0.0f, 1.0f);

	OnHealthChanged();
}
/*----------------------------------------------------------------------------------------------------*/
float ASuitPlayer::GetHealth() const
{
	return _health;
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::UpdateUI()
{
	ASuitPlayerController* playerController = Cast<ASuitPlayerController>(GetController());
	if (playerController == nullptr)
	{
		return;
	}

	if (Aldjam48HUD* hud = Cast<Aldjam48HUD>(playerController->GetHUD()))
	{
		if (UHudWidget* hudWidget = hud->GetHudWidget())
		{
			hudWidget->SetHealthProgressBar(_health);

			if (_gunComponent != nullptr)
			{
				hudWidget->SetAmmoCount(_gunComponent->GetAmmoCount());
			}
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::SetInvincible(bool value)
{
	_isInvincible = value;

	if (_spriteMatInst != nullptr)
	{
		float blinkIntensity = value ? 1.f : 0.f;
		_spriteMatInst->SetScalarParameterValue("BlinkIntensity", blinkIntensity);
	}
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

	UpdateUI();
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
	SetInvincible(false);
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::OnHealthChanged()
{
	UpdateUI();

	if (_health <= 0.0f)
	{

	}
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayer::OnDamageTaken()
{
	if (!_isInvincible)
	{
		SetInvincible(true);
		GetWorldTimerManager().SetTimer(_invulnerabilityTimer, this, &ASuitPlayer::OnInvulnerabilityTimer, _invulnerabilityOnDamageDuration);
	}
}
/*----------------------------------------------------------------------------------------------------*/
EMovablePawnDirection ASuitPlayer::GetOppositeDirection(EMovablePawnDirection direction)
{
	switch (direction)
	{
		case EMovablePawnDirection::Back:
		{
			return EMovablePawnDirection::Front;
		}
		case EMovablePawnDirection::Front:
		{
			return EMovablePawnDirection::Back;
		}
		case EMovablePawnDirection::Left:
		{
			return EMovablePawnDirection::Right;
		}
		case EMovablePawnDirection::Right:
		{
			return EMovablePawnDirection::Left;
		}
		default:
		{
			break;
		}
	}

	return EMovablePawnDirection::Left;
}
/*----------------------------------------------------------------------------------------------------*/