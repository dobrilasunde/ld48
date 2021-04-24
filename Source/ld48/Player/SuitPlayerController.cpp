// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "SuitPlayerController.h"
#include "SuitPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <algorithm>
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent == nullptr)
	{
		return;
	}

	InputComponent->BindAction("Up", EInputEvent::IE_Pressed, this, &ASuitPlayerController::InputComponent_OnUpPressed);
	InputComponent->BindAction("Down", EInputEvent::IE_Pressed, this, &ASuitPlayerController::InputComponent_OnDownPressed);
	InputComponent->BindAction("Left", EInputEvent::IE_Pressed, this, &ASuitPlayerController::InputComponent_OnLeftPressed);
	InputComponent->BindAction("Right", EInputEvent::IE_Pressed, this, &ASuitPlayerController::InputComponent_OnRightPressed);

	InputComponent->BindAction("Up", EInputEvent::IE_Released, this, &ASuitPlayerController::InputComponent_OnUpReleased);
	InputComponent->BindAction("Down", EInputEvent::IE_Released, this, &ASuitPlayerController::InputComponent_OnDownReleased);
	InputComponent->BindAction("Left", EInputEvent::IE_Released, this, &ASuitPlayerController::InputComponent_OnLeftReleased);
	InputComponent->BindAction("Right", EInputEvent::IE_Released, this, &ASuitPlayerController::InputComponent_OnRightReleased);

	InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ASuitPlayerController::InputComponent_OnAttackPressed);
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::OnPossess(APawn* possesedPawn)
{
	Super::OnPossess(possesedPawn);

	if (possesedPawn != nullptr)
	{
		_owningPlayer = possesedPawn;

		_movementComponent = Cast<UCharacterMovementComponent>(_owningPlayer->GetMovementComponent());

		Reset();

		_isInGame = true;
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	_isInGame = false;

	SetPlayerState(EMovablePawnState::None);
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::SetPlayerDirection(EMovablePawnDirection playerDirection)
{
	if (_playerDirection == playerDirection)
	{
		return;
	}

	_playerDirection = playerDirection;

	OnPlayerDirectionChanged();
}
/*----------------------------------------------------------------------------------------------------*/
EMovablePawnDirection ASuitPlayerController::GetPlayerDirection() const
{
	return _playerDirection;
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::SetPlayerState(EMovablePawnState playerState)
{
	if (_playerState == playerState)
	{
		return;
	}

	_playerState = playerState;

	OnPlayerStateChanged();
}
/*----------------------------------------------------------------------------------------------------*/

EMovablePawnState ASuitPlayerController::GetPlayerState() const
{
	return _playerState;
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::OnPlayerDirectionChanged()
{
	ASuitPlayer* player = Cast<ASuitPlayer>(_owningPlayer);
	if (player == nullptr)
	{
		return;
	}

	player->SetFlipbook(_playerState, _playerDirection);
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::OnPlayerStateChanged()
{

}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::InputComponent_OnUpPressed()
{
	_movementUp = 1.f;
	AddVerticalMovementInput(EMovementInput::Up);

	UpdateMovementVector();
	UpdateDirection();
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::InputComponent_OnDownPressed()
{
	_movementDown = 1.f;
	AddVerticalMovementInput(EMovementInput::Down);

	UpdateMovementVector();
	UpdateDirection();
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::InputComponent_OnLeftPressed()
{
	_movementLeft = 1.f;
	AddHorizontalMovementInput(EMovementInput::Left);

	UpdateMovementVector();
	UpdateDirection();
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::InputComponent_OnRightPressed()
{
	_movementRight = 1.f;
	AddHorizontalMovementInput(EMovementInput::Right);

	UpdateMovementVector();
	UpdateDirection();
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::InputComponent_OnUpReleased()
{
	_movementUp = 0.f;
	RemoveVerticalMovementInput(EMovementInput::Up);

	UpdateMovementVector();
	UpdateDirection();
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::InputComponent_OnDownReleased()
{
	_movementDown = 0.f;
	RemoveVerticalMovementInput(EMovementInput::Down);

	UpdateMovementVector();
	UpdateDirection();
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::InputComponent_OnLeftReleased()
{
	_movementLeft = 0.f;
	RemoveHorizontalMovementInput(EMovementInput::Left);

	UpdateMovementVector();
	UpdateDirection();
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::InputComponent_OnRightReleased()
{
	_movementRight = 0.f;
	RemoveHorizontalMovementInput(EMovementInput::Right);

	UpdateMovementVector();
	UpdateDirection();
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::InputComponent_OnAttackPressed()
{

}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::AddVerticalMovementInput(const EMovementInput& input)
{
	RemoveVerticalMovementInput(input);
	_verticalMovementInputs.push_front(input);
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::RemoveVerticalMovementInput(const EMovementInput& input)
{
	_verticalMovementInputs.erase(std::remove(_verticalMovementInputs.begin(), _verticalMovementInputs.end(), input), _verticalMovementInputs.end());
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::AddHorizontalMovementInput(const EMovementInput& input)
{
	RemoveHorizontalMovementInput(input);
	_horizontalMovementInputs.push_front(input);
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::RemoveHorizontalMovementInput(const EMovementInput& input)
{
	_horizontalMovementInputs.erase(std::remove(_horizontalMovementInputs.begin(), _horizontalMovementInputs.end(), input), _horizontalMovementInputs.end());
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::UpdateMovementVector()
{
	EMovementInput lastVerticalInput = _verticalMovementInputs.empty() ? EMovementInput::None : _verticalMovementInputs.front();
	EMovementInput lastHorizontalInput = _horizontalMovementInputs.empty() ? EMovementInput::None : _horizontalMovementInputs.front();

	_movementVector.X = lastHorizontalInput == EMovementInput::Left || lastHorizontalInput == EMovementInput::Right ? _movementRight - _movementLeft : 0.f;
	_movementVector.Z = lastVerticalInput == EMovementInput::Up || lastVerticalInput == EMovementInput::Down ? _movementUp - _movementDown : 0.f;
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::UpdateDirection()
{
	// Get player direction
	EMovementInput lastMovementInput = _horizontalMovementInputs.empty() ? EMovementInput::None : _horizontalMovementInputs.front();
	if (lastMovementInput == EMovementInput::None)
	{
		return;
	}

	switch (lastMovementInput)
	{
		case EMovementInput::Up:
		{
			SetPlayerDirection(EMovablePawnDirection::Back);
			break;
		}
		case EMovementInput::Down:
		{
			SetPlayerDirection(EMovablePawnDirection::Front);
			break;
		}
		case EMovementInput::Left:
		{
			SetPlayerDirection(EMovablePawnDirection::Left);
			break;
		}
		case EMovementInput::Right:
		{
			SetPlayerDirection(EMovablePawnDirection::Right);
			break;
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ASuitPlayerController::Reset()
{
	_playerDirection = EMovablePawnDirection::Left;
	_owningPlayer->SetActorRotation(FRotator::ZeroRotator);
	SetPlayerState(EMovablePawnState::Idle);
}
/*----------------------------------------------------------------------------------------------------*/