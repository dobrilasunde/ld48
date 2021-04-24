// Copyright Epic Games, Inc. All Rights Reserved.
/*----------------------------------------------------------------------------------------------------*/
#include "ld48WorldSettings.h"
/*----------------------------------------------------------------------------------------------------*/
Ald48WorldSettings::Ald48WorldSettings()
{

}
/*----------------------------------------------------------------------------------------------------*/
ALevelManager* Ald48WorldSettings::GetLevelManager() const
{
	return _levelManager;
}
/*----------------------------------------------------------------------------------------------------*/
ALevelGridGenerator* Ald48WorldSettings::GetLevelGridGenerator() const
{
	return _levelGridGenerator;
}
/*----------------------------------------------------------------------------------------------------*/