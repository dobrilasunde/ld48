// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "../Misc/MovablePawnsShared.h"
#include "Projectile.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UPaperFlipbookComponent;
class UProjectileMovementComponent;
class USphereComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

	UPaperFlipbookComponent* GetFlipbook() const;

	virtual void Tick(float DeltaTime) override;
	void SetDirection(EMovablePawnDirection direction);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnOwnerDestroyed();

private:
	UPROPERTY(EditAnywhere)
	float _damage = 0.1f;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* _projectileMovementComponent;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* _flipbookComponent;

	UPROPERTY(EditAnywhere)
	USphereComponent* _sphereComponent;

	UPROPERTY(VisibleAnywhere)
	EMovablePawnDirection _direction;
};
/*----------------------------------------------------------------------------------------------------*/