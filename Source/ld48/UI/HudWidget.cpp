// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "HudWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
/*----------------------------------------------------------------------------------------------------*/
UHudWidget::UHudWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}
/*----------------------------------------------------------------------------------------------------*/
void UHudWidget::SetHealthProgressBar(float value)
{
	if (_healthProgressBar != nullptr)
	{
		_healthProgressBar->SetPercent(value);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void UHudWidget::SetAmmoCount(int32 count)
{
	if (_ammoText != nullptr)
	{
		_ammoText->SetText(FText::FromString(FString::Printf(TEXT("ammo: %d"), count)));
	}
}
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/