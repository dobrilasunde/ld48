// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "Projectile.h"
#include "../NPC/NPC.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "SuitPlayer.h"
#include "SuitPlayerController.h"
/*----------------------------------------------------------------------------------------------------*/
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	_projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	_sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = _sphereComponent;

	_flipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	_flipbookComponent->SetupAttachment(RootComponent);
}
/*----------------------------------------------------------------------------------------------------*/
UPaperFlipbookComponent* AProjectile::GetFlipbook() const
{
	return _flipbookComponent;
}
/*----------------------------------------------------------------------------------------------------*/
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void AProjectile::BeginPlay()
{
	Super::BeginPlay();


	if (_sphereComponent)
	{
		_sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	}

	if (ANPC* owner = Cast<ANPC>(GetOwner()))
	{
		SetInstigator(owner);
		owner->OnDestroyed.AddUObject(this, &AProjectile::OnOwnerDestroyed);
	}
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void AProjectile::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor == nullptr && otherActor == this && otherComp == nullptr)
	{
		return;
	}

	if (APawn* pawn = Cast<APawn>(otherActor))
	{
		if (pawn == GetInstigator())
		{
			return;
		}
	}

	if (ANPC* npc = Cast<ANPC>(otherActor))
	{
		EMovablePawnDirection attackDirection = (npc->GetActorLocation().X - GetActorLocation().X) >= 0.0f ? EMovablePawnDirection::Right : EMovablePawnDirection::Left;
		npc->ApplyDamage(attackDirection);
		Destroy();
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AProjectile::OnOwnerDestroyed()
{
	Destroy();
}
/*----------------------------------------------------------------------------------------------------*/
