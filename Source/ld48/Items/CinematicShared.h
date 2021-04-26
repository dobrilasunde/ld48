// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CinematicShared.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UENUM()
enum class ECinematicEventType : uint8
{
	None,
	Office,
	Elevator
};
/*----------------------------------------------------------------------------------------------------*/
struct FCinematicEventData
{
	ECinematicEventType Type = ECinematicEventType::None;
	float Duration = 0.f;
};
/*----------------------------------------------------------------------------------------------------*/
