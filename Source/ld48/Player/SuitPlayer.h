// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperCharacter.h"
#include "../Misc/MovablePawnsShared.h"
#include "../Items/CinematicShared.h"
#include <Components/AudioComponent.h>
#include "SuitPlayer.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UBoxComponent;
class UMatineeCameraShake;
class UPaperFlipbook;
class UPlayerGunComponent;
class UMaterialInstanceDynamic;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ASuitPlayer : public APaperCharacter
{
	GENERATED_BODY()

public:
	ASuitPlayer();

	void SetFlipbook(EMovablePawnState playerState, EMovablePawnDirection playerDirection);
	void UpdateFlipbook();

	void StartWalk();
	void StopWalk();

	void MeleeAttack(EMovablePawnDirection attackDirection);
	void Shoot(EMovablePawnDirection attackDirection);
	void OnMeleeAttackAnimationFinishedPlaying();

	UPaperFlipbookComponent* GetMeleeAttackFlipbookComponent() const;

	void ApplyDamage(EMovablePawnDirection direction, float damage);
	void SetHealth(float health);
	float GetHealth() const;

	void UpdateUI();

	void SetInvincible(bool value);

	void AddAmmo(int32 ammoCount);

	void OnCinematicEvent(FCinematicEventData cinematicEvent);

	void SetHasGun(bool value);

// ACharacter
public:
	virtual void BeginPlay() override;

protected:
	virtual void Tick(float DeltaTime) override;

private:
	void ShakeCamera();

	UFUNCTION()
	void OnInvulnerabilityTimer();

	void OnHealthChanged();
	void OnDamageTaken();

	EMovablePawnDirection GetOppositeDirection(EMovablePawnDirection direction);

private:
	UPROPERTY(EditAnywhere)
	UPlayerGunComponent* _gunComponent;

private:
	UPROPERTY(EditAnywhere, Category = "Player|Audio")
	USoundBase* _gunAudio;

	UPROPERTY(EditAnywhere, Category = "Player|Audio")
	TArray<USoundBase*> _meleeAudios;

	UPROPERTY(EditAnywhere, Category = "Player|Material")
	UMaterialInterface* _spriteMaterial;

	UPROPERTY(EditAnywhere, Category = "Player|Damage")
	float _invulnerabilityOnDamageDuration = 0.f;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook")
	UPaperFlipbook* _idleDownFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook")
	UPaperFlipbook* _idleUpFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook")
	UPaperFlipbook* _idleLeftFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook")
	UPaperFlipbook* _idleRightFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook")
	UPaperFlipbook* _walkDownFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook")
	UPaperFlipbook* _walkUpFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook")
	UPaperFlipbook* _walkLeftFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook")
	UPaperFlipbook* _walkRightFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook|Gun")
	UPaperFlipbook* _gunIdleDownFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook|Gun")
	UPaperFlipbook* _gunIdleUpFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook|Gun")
	UPaperFlipbook* _gunIdleLeftFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook|Gun")
	UPaperFlipbook* _gunIdleRightFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook|Gun")
	UPaperFlipbook* _gunWalkDownFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook|Gun")
	UPaperFlipbook* _gunWalkUpFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook|Gun")
	UPaperFlipbook* _gunWalkLeftFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook|Gun")
	UPaperFlipbook* _gunWalkRightFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook|Gun")
	UPaperFlipbook* _deathFlipbook;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* _meleeAttackFlipbookComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* _walkAudioComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* _meleeAttackHitBox;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> _verticalCameraShake;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> _horizontalCameraShake;

private:
	UPROPERTY(EditAnywhere, Category = "Suit")
	float _pixelsPerUnit = 1.f;

private:
	UPROPERTY();
	UMaterialInstanceDynamic* _spriteMatInst;

	bool _isInvincible = false;

	FTimerHandle _invulnerabilityTimer;

	float _health = 1.0f;

	bool _hasGun = false;
};
/*----------------------------------------------------------------------------------------------------*/