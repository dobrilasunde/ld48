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
void UHudWidget::OnCinematicEvent(FCinematicEventData cinematicEvent)
{
	if (_playedEvents.Contains(cinematicEvent.Type))
	{
		return;
	}

	_playedEvents.Add(cinematicEvent.Type);

	if (_cinematicText != nullptr)
	{
		_cinematicText->SetVisibility(ESlateVisibility::Visible);
		_cinematicText->SetText(GetTextForCinematicEvent(cinematicEvent.Type));
	}

	_currentEventDuration = cinematicEvent.Duration;
}
/*----------------------------------------------------------------------------------------------------*/
void UHudWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	_currentEventDuration -= InDeltaTime;

	if (_currentEventDuration <= 0.f)
	{
		if (_cinematicText != nullptr)
		{
			_cinematicText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
FText UHudWidget::GetTextForCinematicEvent(ECinematicEventType eventType) const
{
	if (const FText* textPtr = _textPerCinematicEvent.Find(eventType))
	{
		return *textPtr;
	}

	return FText::GetEmpty();
}
/*----------------------------------------------------------------------------------------------------*/
