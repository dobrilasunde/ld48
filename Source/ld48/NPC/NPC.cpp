// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "NPC.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbook.h"
#include "../Levels/LevelManager.h"
#include <Components/AudioComponent.h>
#include "../Player/SuitPlayer.h"
#include "../Player/SuitPlayerController.h"
#include "../ld48WorldSettings.h"
#include <DrawDebugHelpers.h>
/*----------------------------------------------------------------------------------------------------*/
ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;

	_attackFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("AttackFlipbook"));
	_attackFlipbook->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_attackFlipbook->Stop();
	_attackFlipbook->SetLooping(false);
	_attackFlipbook->SetHiddenInGame(true);

	_attackHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitBox"));
	_attackHitBox->SetupAttachment(_attackFlipbook);

	_deathFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("DeathFlipbookComponent"));
	_deathFlipbookComponent->SetupAttachment(RootComponent);
	_deathFlipbookComponent->Stop();
	_deathFlipbookComponent->SetLooping(false);
	_deathFlipbookComponent->SetHiddenInGame(true);

	_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	_audioComponent->SetupAttachment(RootComponent);

	if (UCharacterMovementComponent* characterMovement = GetCharacterMovement())
	{
		characterMovement->bRunPhysicsWithNoController = true;
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::SnapLocation()
{
	const float unitsPerPixel = 1.f / _pixelsPerUnit;

	FVector location = GetActorLocation();
	location.X = FMath::GridSnap(location.X, unitsPerPixel);
	location.Z = FMath::GridSnap(location.Z, unitsPerPixel);
	SetActorLocation(location);
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::SetLastMovementVector(FVector movementVector)
{
	if (_lastMovementVector == movementVector)
	{
		return;
	}

	FVector oldMovementVector = _lastMovementVector;
	_lastMovementVector = movementVector;

	OnLastMovementVectorChanged(oldMovementVector);
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::OnLastMovementVectorChanged(FVector oldMovementVector)
{
	if (_lastMovementVector.X < 0.0f)
	{
		SetLastMovementInput(EMovementInput::Left);
	}
	else if (_lastMovementVector.X > 0.0f)
	{
		SetLastMovementInput(EMovementInput::Right);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::SetLastMovementInput(EMovementInput movementInput)
{
	if (_lastMovementInput == movementInput)
	{
		return;
	}

	_lastMovementInput = movementInput;
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::UpdateFlipbook()
{
	if (_lastMovementInput == EMovementInput::None)
	{
		return;
	}

	switch (_lastMovementInput)
	{
		case EMovementInput::Up:
		{
			SetNPCDirection(EMovablePawnDirection::Back);
			break;
		}
		case EMovementInput::Down:
		{
			SetNPCDirection(EMovablePawnDirection::Front);
			break;
		}
		case EMovementInput::Left:
		{
			SetNPCDirection(EMovablePawnDirection::Left);
			break;
		}
		case EMovementInput::Right:
		{
			SetNPCDirection(EMovablePawnDirection::Right);
			break;
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::OnDamageTaken()
{
	_hitEffectValue = _hitEffectStrength;
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::ApplyKnockback(EMovablePawnDirection direction)
{
	FVector newLocation = GetActorLocation();
	if (direction == EMovablePawnDirection::Left)
	{
		newLocation.X = newLocation.X - _knockbackOnHit;
		SetActorLocation(newLocation);
	}
	else if (direction == EMovablePawnDirection::Right)
	{
		newLocation.X = newLocation.X + _knockbackOnHit;
		SetActorLocation(newLocation);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::TickHitEffects(float deltaTime)
{
	if (_spriteMaterialInstance != nullptr)
	{
		_spriteMaterialInstance->SetScalarParameterValue(TEXT("AdditiveBrightness"), _hitEffectValue);
	}

	_hitEffectValue = FMath::Max(0.f, _hitEffectValue - _hitEffectDecaySpeed * deltaTime);
}
/*----------------------------------------------------------------------------------------------------*/
APawn* ANPC::FindPlayerPawn() const
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);
	if (pc == nullptr)
	{
		return nullptr;
	}

	return pc->GetPawn();
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::OnDeathAnimationFinishedPlaying()
{
	if (Ald48WorldSettings* ws = Cast<Ald48WorldSettings>(GetWorldSettings()))
	{
		if (ALevelManager* levelManager = ws->GetLevelManager())
		{
			levelManager->OnEnemyDied();
		}
	}

	Destroy();
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::OnAttackAnimationFinishedPlaying()
{
	if (_attackFlipbook)
	{
		_attackFlipbook->SetHiddenInGame(true);
	}

	if (UPaperFlipbookComponent* flipbook = GetSprite())
	{
		flipbook->SetHiddenInGame(false);
	}

	SetNPCState(EMovablePawnState::Idle);
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::OnAudioTimer()
{
	if (_sounds.Num() > 0)
	{
		_audioComponent->SetSound(_sounds[FMath::RandRange(0, _sounds.Num() - 1)]);
		_audioComponent->Play();
		GetWorldTimerManager().SetTimer(_soundsTimer, this, &ANPC::OnAudioTimer, FMath::FRandRange(4.f, 8.f));
	}
}
/*----------------------------------------------------------------------------------------------------*/
UPaperFlipbookComponent* ANPC::GetAttackFlipbook() const
{
	return _attackFlipbook;
}
/*----------------------------------------------------------------------------------------------------*/
APawn* ANPC::GetTargetPlayer() const
{
	return _targetPlayer.Get();
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void ANPC::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	TickHitEffects(deltaTime);

	if (_targetPlayer != nullptr)
	{
		FVector TraceStart = GetActorLocation();
		FVector TraceEnd = _targetPlayer->GetActorLocation();
		if (FVector::Dist(TraceStart, TraceEnd) > _minTargetDetectionDistance)
		{
			return;
		}

		FHitResult hitResult;
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(hitResult, TraceStart, TraceEnd, ECC_Visibility);
		if (!bSuccess)
		{
			MoveToTarget(_targetPlayer.Get());
		}

		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor(238, 0, 238), false);	
	}

	if (_npcState != EMovablePawnState::Attacking)
	{
		float currentAccelerationX = GetCharacterMovement()->GetCurrentAcceleration().X;
		float currentAccelerationZ = GetCharacterMovement()->GetCurrentAcceleration().Z;

		if (currentAccelerationX != 0.f || currentAccelerationZ != 0)
		{
			SetNPCState(EMovablePawnState::Walking);
		}
		else if (currentAccelerationX == 0.f && currentAccelerationZ == 0)
		{
			SetNPCState(EMovablePawnState::Idle);
		}
	}

	_attackDelayTimer += deltaTime;

	if (_npcState == EMovablePawnState::Idle)
	{
		_attackWindUpTimer += deltaTime;
	}
	else
	{
		_attackWindUpTimer = 0.0f;
	}

	//SnapLocation();
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::SetNPCState(EMovablePawnState npcState)
{
	if (_npcState == npcState)
	{
		return;
	}

	_npcState = npcState;

	OnNPCStateChanged();
}
/*----------------------------------------------------------------------------------------------------*/
EMovablePawnState ANPC::GetNPCState() const
{
	return _npcState;
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::OnNPCStateChanged()
{
	SetFlipbook(_npcState, _npcDirection);
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::SetNPCDirection(EMovablePawnDirection npcDirection)
{
	if (_npcDirection == npcDirection)
	{
		return;
	}

	_npcDirection = npcDirection;

	OnNPCDirectionChanged();
}
/*----------------------------------------------------------------------------------------------------*/
EMovablePawnDirection ANPC::GetNPCDirection() const
{
	return _npcDirection;
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::OnNPCDirectionChanged()
{
	SetFlipbook(_npcState, _npcDirection);
}
/*----------------------------------------------------------------------------------------------------*/
EMovablePawnDirection ANPC::GetStartingNPCDirection() const
{
	return _npcStartingDirection;
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::SetFlipbook(EMovablePawnState npcState, EMovablePawnDirection npcDirection)
{
	UPaperFlipbookComponent* flipbook = GetSprite();
	if (flipbook == nullptr)
	{
		return;
	}

	if (_npcState == EMovablePawnState::Idle)
	{
		switch (_npcDirection)
		{
			case EMovablePawnDirection::Right:
			{
				if (_idleRightFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_idleRightFlipbook);
					flipbook->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
					//flipbook->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
				}
				break;
			}
			case EMovablePawnDirection::Left:
			{
				if (_idleLeftFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_idleLeftFlipbook);
					flipbook->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
					//flipbook->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
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
	else if (_npcState == EMovablePawnState::Walking)
	{
		switch (_npcDirection)
		{
			case EMovablePawnDirection::Right:
			{
				if (_walkRightFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_walkRightFlipbook);
					flipbook->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
					//flipbook->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
				}
				break;
			}
			case EMovablePawnDirection::Left:
			{
				if (_walkLeftFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_walkLeftFlipbook);
					flipbook->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
					//flipbook->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
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
	else if (_npcState == EMovablePawnState::Attacking)
	{
		if (_npcDirection == EMovablePawnDirection::Left)
		{
			_attackFlipbook->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
		}
		else if (_npcDirection == EMovablePawnDirection::Right)
		{
			_attackFlipbook->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
		}

		flipbook->SetHiddenInGame(true);
		_attackFlipbook->SetHiddenInGame(false);
		_attackFlipbook->PlayFromStart();
	}
	else if (_npcState == EMovablePawnState::Dying)
	{
		if (_deathFlipbookComponent != nullptr && GetSprite() != nullptr)
		{
			flipbook->SetHiddenInGame(true);
			_attackFlipbook->SetHiddenInGame(true);
			_deathFlipbookComponent->SetHiddenInGame(false);
			_deathFlipbookComponent->PlayFromStart();
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::Reset()
{
	SetLastMovementVector(GetActorLocation());
	SetNPCDirection(_npcStartingDirection);
	SetActorRotation(FRotator::ZeroRotator);
	SetNPCState(EMovablePawnState::Idle);
}
/*----------------------------------------------------------------------------------------------------*/
/*virtual*/
void ANPC::MoveToTarget(AActor* target)
{
	if (_npcState == EMovablePawnState::Dying)
	{
		return;
	}

	if (target == nullptr)
	{
		return;
	}
	
	APaperCharacter* targetCharacter = Cast<APaperCharacter>(target);
	if (targetCharacter == nullptr)
	{
		return;
	}

	FVector npcLocation = GetActorLocation();
	float npcCollisionRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();

	FVector targetLocation = targetCharacter->GetActorLocation();
	float targetCollisionRadius = targetCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
	
	FVector direction = targetLocation - npcLocation;

	float distance = direction.Size();
	if (distance < npcCollisionRadius + targetCollisionRadius + _targetRadius)
	{
		OnArrivedToTarget(target);
		return;
	}

	AddMovementInput(direction);
	SetLastMovementVector(direction);
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
/*virtual*/
void ANPC::OnArrivedToTarget(AActor* target)
{
	if (target == nullptr)
	{
		return;
	}

	if (_attackHitBox == nullptr)
	{
		return;
	}

	if (_attackWindUpTimer < _attackWindUp)
	{
		return;
	}

	TArray<AActor*> overlappingActors;
	_attackHitBox->GetOverlappingActors(overlappingActors);

	if (overlappingActors.Contains(target) && _npcState == EMovablePawnState::Idle)
	{
		AttackTarget(target);
	}
}
/*----------------------------------------------------------------------------------------------------*/
/*virtual*/
void ANPC::AttackTarget(AActor* target)
{
	if (_npcState == EMovablePawnState::Attacking)
	{
		return;
	}

	if (_attackDelayTimer < _attackDelay)
	{
		return;
	}

	if (target == nullptr)
	{
		return;
	}

	if (ASuitPlayer* targetCharacter = Cast<ASuitPlayer>(target))
	{
		targetCharacter->ApplyDamage(_npcDirection, _attackDamage);
	}

	//ResetMovement();
	SetNPCState(EMovablePawnState::Attacking);

	_attackDelayTimer = 0.0f;

	OnNPCAttackedTarget.Broadcast(target);
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::ApplyDamage(EMovablePawnDirection direction)
{
	if (_health <= 0.0f)
	{
		return;
	}

	SetHealth(_health - _damageOnHit);
	
	if (_applyKnockback)
	{
		ApplyKnockback(direction);
	}

	OnDamageTaken();
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::SetHealth(float health)
{
	if (_health == health)
	{
		return;
	}

	_health = health;

	OnHealthChanged();
}
/*----------------------------------------------------------------------------------------------------*/
float ANPC::GetHealth() const
{
	return _health;
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::OnHealthChanged()
{
	if (_health <= 0.0f)
	{
		SetNPCState(EMovablePawnState::Dying);

		if (Ald48WorldSettings* ws = Cast<Ald48WorldSettings>(GetWorldSettings()))
		{
			if (ALevelManager* levelManager = ws->GetLevelManager())
			{
				levelManager->Event_OnNPCDied();
			}
		}

		UGameplayStatics::PlaySoundAtLocation(this, _audioComponent->Sound, GetActorLocation());
	}
}
/*----------------------------------------------------------------------------------------------------*/
float ANPC::GetDamageOnHit() const
{
	return _damageOnHit;
}
/*----------------------------------------------------------------------------------------------------*/
float ANPC::GetAttackDamage() const
{
	return _attackDamage;
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::TurnTowardsTarget(AActor* target)
{
	FVector targetLocation = target->GetActorLocation();
	FVector location = GetActorLocation();
	FVector direction = targetLocation - location;

	if (direction.X > 0.f)
	{
		SetNPCDirection(EMovablePawnDirection::Right);
	}
	else if (direction.X < 0.f)
	{
		SetNPCDirection(EMovablePawnDirection::Left);
	}
}
/*----------------------------------------------------------------------------------------------------*/
EMovablePawnDirection ANPC::GetOppositeDirection(EMovablePawnDirection direction)
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
/*override*/
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	_targetPlayer = FindPlayerPawn();

	Reset();

	if (_spriteMaterial != nullptr)
	{
		_spriteMaterialInstance = UMaterialInstanceDynamic::Create(_spriteMaterial, this);
		if (UPaperFlipbookComponent* flipbookComp = GetSprite())
		{
			for (int32 i = 0; i < flipbookComp->GetNumMaterials(); ++i)
			{
				flipbookComp->SetMaterial(i, _spriteMaterialInstance);
			}
		}
	}

	if (_deathFlipbookComponent)
	{
		_deathFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ANPC::OnDeathAnimationFinishedPlaying);
	}


	if (_attackFlipbook)
	{
		_attackFlipbook->OnFinishedPlaying.AddDynamic(this, &ANPC::OnAttackAnimationFinishedPlaying);
	}

	_attackDelayTimer = _attackDelay;

	GetWorldTimerManager().SetTimer(_soundsTimer, this, &ANPC::OnAudioTimer, FMath::FRandRange(4.f, 6.f));
}
/*----------------------------------------------------------------------------------------------------*/
void ANPC::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	OnDestroyed.Broadcast();
}
/*----------------------------------------------------------------------------------------------------*/
