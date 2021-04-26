// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ldjam48HUD.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UHudWidget;
class UUserWidget;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API Aldjam48HUD : public AHUD
{
	GENERATED_BODY()

public:
	Aldjam48HUD();
	
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UHudWidget* GetHudWidget() const;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> _hudWidgetClass;
	
	UHudWidget* _hudWidget;
};
/*----------------------------------------------------------------------------------------------------*/