// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "CinematicTrigger.h"
#include "../Player/SuitPlayer.h"
/*----------------------------------------------------------------------------------------------------*/
void ACinematicTrigger::NotifyActorBeginOverlap(AActor* otherActor)
{
	if (ASuitPlayer* player = Cast<ASuitPlayer>(otherActor))
	{
		FCinematicEventData data;
		data.Type = CinematicEvent;
		data.Duration = Duration;
		player->OnCinematicEvent(data);
	}
}
/*----------------------------------------------------------------------------------------------------*/