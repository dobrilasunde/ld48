// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UProgressBar;
class UOverlay;
class UImage;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UHudWidget(const FObjectInitializer& ObjectInitializer);

	void SetHealthProgressBar(float value);

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* _healthProgressBar;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UOverlay* _healthOverlay;
};
/*----------------------------------------------------------------------------------------------------*/