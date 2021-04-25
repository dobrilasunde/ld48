// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperCharacter.h"
#include "../Misc/MovablePawnsShared.h"
#include "SuitPlayer.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UBoxComponent;
class UPaperFlipbook;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ASuitPlayer : public APaperCharacter
{
	GENERATED_BODY()

public:
	ASuitPlayer();

	void SetFlipbook(EMovablePawnState playerState, EMovablePawnDirection playerDirection);

	void MeleeAttack();
	void StartWalk();
	void StopWalk();

	UPaperFlipbookComponent* GetMeleeAttackFlipbookComponent() const;

// ACharacter
public:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* newController) override;

protected:
	virtual void Tick(float DeltaTime) override;

private:
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

	UPROPERTY(EditAnywhere, Category = "Player|Flipbook")
	UPaperFlipbook* _deathFlipbook;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* _meleeAttackFlipbookComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* _meleeAttackHitBox;

private:
	UPROPERTY(EditAnywhere, Category = "Suit")
	float _pixelsPerUnit = 1.f;
};
/*----------------------------------------------------------------------------------------------------*/