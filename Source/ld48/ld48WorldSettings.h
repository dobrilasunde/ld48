// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "GameFramework/WorldSettings.h"
#include "ld48WorldSettings.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class ALevelGridGenerator;
class ALevelManager;
class AAudioManager;
/*----------------------------------------------------------------------------------------------------*/
/**
 * 
 */
UCLASS(config = game, notplaceable)
class LD48_API Ald48WorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:
	Ald48WorldSettings();

	ALevelManager* GetLevelManager() const;
	AAudioManager* GetAudioManager() const;

private:
	UPROPERTY(EditAnywhere)
	ALevelManager* _levelManager;

	UPROPERTY(EditAnywhere)
	AAudioManager* _audioManager;
};
/*----------------------------------------------------------------------------------------------------*/