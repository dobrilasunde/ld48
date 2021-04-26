// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CinematicShared.h"
#include "CinematicTrigger.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ACinematicTrigger : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	ECinematicEventType CinematicEvent;

	UPROPERTY(EditAnywhere)
	float Duration;

public:
	virtual void NotifyActorBeginOverlap(AActor* otherActor);

};
/*----------------------------------------------------------------------------------------------------*/