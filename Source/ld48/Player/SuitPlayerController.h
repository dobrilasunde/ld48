// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "GameFramework/PlayerController.h"
#include "../Misc/MovablePawnsShared.h"
#include <deque>
#include "SuitPlayerController.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UCharacterMovementComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ASuitPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	virtual void Tick(float deltaSeconds) override;

	virtual void OnPossess(APawn* possesedPawn) override;

	virtual void OnUnPossess() override;

public:
	void SetPlayerDirection(EMovablePawnDirection playerDirection);
	EMovablePawnDirection GetPlayerDirection() const;

	void SetPlayerState(EMovablePawnState playerState);
	EMovablePawnState GetPlayerState() const;

private:
	void OnPlayerDirectionChanged();
	void OnPlayerStateChanged();

	void InputComponent_OnUpPressed();
	void InputComponent_OnDownPressed();
	void InputComponent_OnLeftPressed();
	void InputComponent_OnRightPressed();

	void InputComponent_OnUpReleased();
	void InputComponent_OnDownReleased();
	void InputComponent_OnLeftReleased();
	void InputComponent_OnRightReleased();

	void InputComponent_OnMeleeAttackPressed();

	void AddVerticalMovementInput(const EMovementInput& input);
	void RemoveVerticalMovementInput(const EMovementInput& input);
	void AddHorizontalMovementInput(const EMovementInput& input);
	void RemoveHorizontalMovementInput(const EMovementInput& input);

	void UpdateMovementVector();
	void UpdateDirection();

	void MovePlayer();

	void Reset();

	void AttackScan();

	UFUNCTION()
	void OnMeleeAttackAnimationFinishedPlaying();
	
private:
	UPROPERTY()
	APawn* _owningPlayer;

	UPROPERTY()
	UCharacterMovementComponent* _movementComponent;

	bool _isInGame = false;

	float _movementUp = 0.f;
	float _movementDown = 0.f;
	float _movementLeft = 0.f;
	float _movementRight = 0.f;

	FVector _movementVector = FVector::ZeroVector;

	std::deque<EMovementInput> _verticalMovementInputs;
	std::deque<EMovementInput> _horizontalMovementInputs;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	EMovablePawnDirection _playerDirection;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	EMovablePawnState _playerState;

private:
	UPROPERTY(EditAnywhere)
	float _attackDelay = 0.25f;

	float _attackDelayTimer = 0.0f;
};
/*----------------------------------------------------------------------------------------------------*/