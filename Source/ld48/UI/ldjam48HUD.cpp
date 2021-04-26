// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "ldjam48HUD.h"
#include "HudWidget.h"
/*----------------------------------------------------------------------------------------------------*/
Aldjam48HUD::Aldjam48HUD()
{
}
/*----------------------------------------------------------------------------------------------------*/
void Aldjam48HUD::DrawHUD()
{
	Super::DrawHUD();
}
/*----------------------------------------------------------------------------------------------------*/
void Aldjam48HUD::BeginPlay()
{
	Super::BeginPlay();

	if (_hudWidgetClass != nullptr)
	{
		_hudWidget = CreateWidget<UHudWidget>(GetWorld(), _hudWidgetClass);
		if (_hudWidget != nullptr)
		{
			_hudWidget->AddToViewport();
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void Aldjam48HUD::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (_hudWidget == nullptr)
	{
		return;
	}
}
/*----------------------------------------------------------------------------------------------------*/
UHudWidget* Aldjam48HUD::GetHudWidget() const
{
	return _hudWidget;
}
/*----------------------------------------------------------------------------------------------------*/