// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "ZombieNPC.h"
#include "../Player/SuitPlayer.h"
#include "../Player/SuitPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "../Player/Projectile.h"
#include "../Items/Pickup.h"
/*----------------------------------------------------------------------------------------------------*/
AZombieNPC::AZombieNPC(): Super()
{

}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void AZombieNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void AZombieNPC::BeginPlay()
{
	Super::BeginPlay();
}
/*----------------------------------------------------------------------------------------------------*/
void AZombieNPC::MoveToTarget(AActor* target)
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
void AZombieNPC::OnArrivedToTarget(AActor* target)
{
	Super::OnArrivedToTarget(target);
}
/*----------------------------------------------------------------------------------------------------*/
void AZombieNPC::AttackTarget(AActor* target)
{
	Super::AttackTarget(target);
}
/*----------------------------------------------------------------------------------------------------*/
void AZombieNPC::OnDeathAnimationFinishedPlaying()
{
	if (_pickupClass)
	{
		int32 randomNumber = FMath::RandRange(0, 100);
		if (randomNumber < _dropChance * 100)
		{
			APickup* pickup = GetWorld()->SpawnActor<APickup>(_pickupClass, GetActorLocation(), GetActorRotation());
		}
	}

	Super::OnDeathAnimationFinishedPlaying();
}
/*----------------------------------------------------------------------------------------------------*/
