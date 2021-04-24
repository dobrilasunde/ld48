// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperCharacter.h"
#include "../Misc/MovablePawnsShared.h"
#include "SuitPlayer.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UPaperFlipbook;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ASuitPlayer : public APaperCharacter
{
	GENERATED_BODY()

public:
	void SetFlipbook(EMovablePawnState playerState, EMovablePawnDirection playerDirection);

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
};
/*----------------------------------------------------------------------------------------------------*/