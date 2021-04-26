// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "Pickup.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UPaperSpriteComponent;
class USphereComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API APickup : public AActor
{
	GENERATED_BODY()

public:
	APickup();

	UPaperSpriteComponent* GetSpriteComponent() const;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

private:
	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* _spriteComponent;

	UPROPERTY(EditAnywhere)
	USphereComponent* _sphereComponent;

	UPROPERTY(EditAnywhere)
	int32 _ammo = 10;
};
/*----------------------------------------------------------------------------------------------------*/