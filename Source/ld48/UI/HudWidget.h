// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "../Items/CinematicShared.h"
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
	void SetAmmoCount(int32 count);

	void OnCinematicEvent(FCinematicEventData cinematicEvent);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	FText GetTextForCinematicEvent(ECinematicEventType eventType) const;

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* _healthProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* _ammoText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* _cinematicText;

	UPROPERTY(EditDefaultsOnly)
	TMap<ECinematicEventType, FText> _textPerCinematicEvent;

private:
	float _currentEventDuration = -1.f;
	TArray<ECinematicEventType> _playedEvents;
};
/*----------------------------------------------------------------------------------------------------*/