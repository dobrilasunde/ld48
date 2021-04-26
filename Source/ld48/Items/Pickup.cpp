// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "Pickup.h"
#include "../NPC/NPC.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include <PaperSpriteComponent.h>
#include "../Player/SuitPlayer.h"
/*----------------------------------------------------------------------------------------------------*/
APickup::APickup()
{
	_sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = _sphereComponent;

	_spriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	_spriteComponent->SetupAttachment(RootComponent);
}
/*----------------------------------------------------------------------------------------------------*/
UPaperSpriteComponent* APickup::GetSpriteComponent() const
{
	return _spriteComponent;
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void APickup::BeginPlay()
{
	Super::BeginPlay();

	if (_sphereComponent)
	{
		_sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
	}
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void APickup::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor == nullptr && otherActor == this && otherComp == nullptr)
	{
		return;
	}

	if (ANPC* pawn = Cast<ANPC>(otherActor))
	{
		if (pawn == GetInstigator())
		{
			return;
		}
	}

	if (ASuitPlayer* player = Cast<ASuitPlayer>(otherActor))
	{
		player->AddAmmo(_ammo);
		Destroy();
	}
}
/*----------------------------------------------------------------------------------------------------*/