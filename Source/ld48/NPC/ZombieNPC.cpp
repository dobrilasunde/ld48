// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "ZombieNPC.h"
#include "../Player/SuitPlayer.h"
#include "../Player/SuitPlayerController.h"
#include "Components/CapsuleComponent.h"
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

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AZombieNPC::OnOverlapBegin);
	}
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
void AZombieNPC::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor == nullptr && otherActor == this && otherComp == nullptr)
	{
		return;
	}

	if (ASuitPlayer* player = Cast<ASuitPlayer>(otherActor))
	{
		if (ASuitPlayerController* playerController = Cast<ASuitPlayerController>(player->GetController()))
		{
			//playerController->ApplyDamage(GetNPCDirection(), GetAttackDamage());
			if (ANPC* owner = Cast<ANPC>(GetOwner()))
			{
				owner->OnNPCAttackedTarget.Broadcast(player);
			}
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/