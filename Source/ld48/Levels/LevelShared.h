// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "LevelShared.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UENUM()
enum class ELevelName : uint8
{
	None,
	LevelOffice,
	LevelOfficeElevator,
	LevelGarage,
	LevelElevator,
	LevelStairs,
	FinalLevel,
	Count UMETA(Hidden)
};
/*----------------------------------------------------------------------------------------------------*/
UENUM()
enum class EWall : uint8
{
	Top,
	Right,
	Bottom,
	Left,
	Count UMETA(Hidden)
};
/*----------------------------------------------------------------------------------------------------*/
UENUM()
enum class ETileState : uint8
{
	None,
	Path,
	Start,
	End,
	Count UMETA(Hidden)
};
/*----------------------------------------------------------------------------------------------------*/