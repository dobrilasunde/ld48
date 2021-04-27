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
	OfficeElevator,
	Garage1,
	Garage2,
	Garage3,
	Garage4,
	Garage5,
	Elevator1,
	Elevator2,
	Stairs,
	FinalLevel
};
/*----------------------------------------------------------------------------------------------------*/
struct FCinematicEventData
{
	ECinematicEventType Type = ECinematicEventType::None;
	float Duration = 0.f;
};
/*----------------------------------------------------------------------------------------------------*/
