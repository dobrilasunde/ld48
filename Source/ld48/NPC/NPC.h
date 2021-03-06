// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "../Misc/MovablePawnsShared.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperCharacter.h"
#include "NPC.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class APawn;
class UAudioComponent;
class UBoxComponent;
class UPaperFlipbook;
class UPaperFlipbookComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ANPC : public APaperCharacter
{
	GENERATED_BODY()

public:
	DECLARE_EVENT(ANPC, FOnDestroyed)
	FOnDestroyed OnDestroyed;

	DECLARE_EVENT_OneParam(ANPC, FOnNPCAttackedTarget, AActor*)
	FOnNPCAttackedTarget OnNPCAttackedTarget;

public:
	ANPC();

	UPaperFlipbookComponent* GetAttackFlipbook() const;
	APawn* GetTargetPlayer() const;

public:
	virtual void Tick(float DeltaTime) override;

	void SetNPCState(EMovablePawnState npcState);
	EMovablePawnState GetNPCState() const;
	void OnNPCStateChanged();

	void SetNPCDirection(EMovablePawnDirection npcDirection);
	EMovablePawnDirection GetNPCDirection() const;
	void OnNPCDirectionChanged();

	EMovablePawnDirection GetStartingNPCDirection() const;

	void SetFlipbook(EMovablePawnState npcState, EMovablePawnDirection npcDirection);

	void Reset();

	virtual void MoveToTarget(AActor* target);
	virtual void OnArrivedToTarget(AActor* target);
	virtual void AttackTarget(AActor* target);

	virtual void ApplyDamage(EMovablePawnDirection direction);
	void SetHealth(float health);
	float GetHealth() const;
	void OnHealthChanged();

	float GetDamageOnHit() const;
	float GetAttackDamage() const;

	void TurnTowardsTarget(AActor* target);

	EMovablePawnDirection GetOppositeDirection(EMovablePawnDirection direction);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

	UFUNCTION()
	virtual void OnDeathAnimationFinishedPlaying();

private:
	void SnapLocation();

	void SetLastMovementVector(FVector movementVector);
	void OnLastMovementVectorChanged(FVector oldMovementVector);
	void SetLastMovementInput(EMovementInput movementInput);

	void UpdateFlipbook();

	void OnDamageTaken();
	void ApplyKnockback(EMovablePawnDirection direction);

	void TickHitEffects(float deltaTime);

	APawn* FindPlayerPawn() const;

	UFUNCTION()
	void OnAttackAnimationFinishedPlaying();

	UFUNCTION()
	void OnAudioTimer();

protected:
	float _health = 1.0f;

	UPROPERTY(EditAnywhere)
	float _damageOnHit = 0.25f;

	UPROPERTY(EditAnywhere)
	bool _applyKnockback = true;

	UPROPERTY(EditAnywhere)
	float _attackDamage = 0.1f;

	UPROPERTY(EditAnywhere)
	float _attackDelay = 2.0f;

	float _attackDelayTimer = 0.0f;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* _spriteMaterial;
	UMaterialInstanceDynamic* _spriteMaterialInstance = nullptr;

	float _hitEffectValue = 0.f;

	UPROPERTY(EditAnywhere)
	float _knockbackOnHit = 5.0f;

	UPROPERTY(EditAnywhere)
	float _attackWindUp = 1.0f;

	float _attackWindUpTimer = 0.0f;

private:
	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<APawn> _targetPlayer;

	UPROPERTY(EditAnywhere)
	float _targetRadius = 2.0f;

	UPROPERTY(EditAnywhere, Category = "NPC")
	EMovablePawnDirection _npcStartingDirection = EMovablePawnDirection::Left;

	UPROPERTY(VisibleAnywhere, Category = "NPC")
	EMovablePawnState _npcState;

	UPROPERTY(VisibleAnywhere, Category = "NPC")
	EMovablePawnDirection _npcDirection;

	UPROPERTY(EditAnywhere)
	float _pixelsPerUnit = 1.f;

	UPROPERTY(EditAnywhere)
	UBoxComponent* _attackHitBox;

	UPROPERTY(EditAnywhere, Category = "NPC|HitEffect")
	float _hitEffectStrength = 5.f;

	UPROPERTY(EditAnywhere, Category = "NPC|HitEffect")
	float _hitEffectDecaySpeed = 10.f;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* _attackFlipbook;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* _deathFlipbookComponent;

	FVector _lastMovementVector;

	EMovementInput _lastMovementInput;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float _minTargetDetectionDistance = 100.0f;

	FTimerHandle _soundsTimer;

private:
	UPROPERTY(EditAnywhere, Category = "NPC|Flipbook")
	UPaperFlipbook* _idleDownFlipbook;

	UPROPERTY(EditAnywhere, Category = "NPC|Flipbook")
	UPaperFlipbook* _idleUpFlipbook;

	UPROPERTY(EditAnywhere, Category = "NPC|Flipbook")
	UPaperFlipbook* _idleLeftFlipbook;

	UPROPERTY(EditAnywhere, Category = "NPC|Flipbook")
	UPaperFlipbook* _idleRightFlipbook;

	UPROPERTY(EditAnywhere, Category = "NPC|Flipbook")
	UPaperFlipbook* _walkDownFlipbook;

	UPROPERTY(EditAnywhere, Category = "NPC|Flipbook")
	UPaperFlipbook* _walkUpFlipbook;

	UPROPERTY(EditAnywhere, Category = "NPC|Flipbook")
	UPaperFlipbook* _walkLeftFlipbook;

	UPROPERTY(EditAnywhere, Category = "NPC|Flipbook")
	UPaperFlipbook* _walkRightFlipbook;

	UPROPERTY(EditAnywhere, Category = "NPC")
	UAudioComponent* _audioComponent;

	UPROPERTY(EditAnywhere, Category = "NPC")
	TArray<USoundBase*> _sounds;
};
/*----------------------------------------------------------------------------------------------------*/