// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "BossNPC.h"
#include "../Player/SuitPlayer.h"
#include "../Player/SuitPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "../Player/Projectile.h"
#include "../Items/Pickup.h"
/*----------------------------------------------------------------------------------------------------*/
ABossNPC::ABossNPC(): Super()
{

}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void ABossNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void ABossNPC::BeginPlay()
{
	Super::BeginPlay();

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABossNPC::OnOverlapBegin);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ABossNPC::MoveToTarget(AActor* target)
{
	ASuitPlayer* player = Cast<ASuitPlayer>(target);
	if (player == nullptr)
	{
		return;
	}

	ASuitPlayerController* playerController = Cast<ASuitPlayerController>(player->GetController());
	if (playerController == nullptr)
	{
		return;
	}

	TurnTowardsTarget(target);

	Super::MoveToTarget(target);
}
/*----------------------------------------------------------------------------------------------------*/
void ABossNPC::OnArrivedToTarget(AActor* target)
{
	Super::OnArrivedToTarget(target);
}
/*----------------------------------------------------------------------------------------------------*/
void ABossNPC::AttackTarget(AActor* target)
{
	Super::AttackTarget(target);
}
/*----------------------------------------------------------------------------------------------------*/
void ABossNPC::OnDeathAnimationFinishedPlaying()
{
	if (_pickupClass)
	{
		APickup* pickup = GetWorld()->SpawnActor<APickup>(_pickupClass, GetActorLocation(), GetActorRotation());
	}

	Super::OnDeathAnimationFinishedPlaying();
}
/*----------------------------------------------------------------------------------------------------*/
void ABossNPC::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (AProjectile* projectile = Cast<AProjectile>(otherActor))
	{
		//Destroy();
	}
}
/*----------------------------------------------------------------------------------------------------*/
