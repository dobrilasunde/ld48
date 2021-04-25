// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "LevelGridCell.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UENUM(BlueprintType)
enum class ECellEdgeType : uint8
{
	Wall,
	Passage
};
/*----------------------------------------------------------------------------------------------------*/
class UPaperSpriteComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ALevelGridCell : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FString LeftEdgeName_Wall		= "LeftEdgeName_Wall";
	UPROPERTY(EditDefaultsOnly)
	FString RightEdgeName_Wall		= "RightEdgeName_Wall";
	UPROPERTY(EditDefaultsOnly)
	FString TopEdgeName_Wall		= "TopEdgeName_Wall";
	UPROPERTY(EditDefaultsOnly)
	FString BottomEdgeName_Wall		= "BottomEdgeName_Wall";

	UPROPERTY(EditDefaultsOnly)
	FString LeftEdgeName_Passage	= "LeftEdgeName_Passage";
	UPROPERTY(EditDefaultsOnly)
	FString RightEdgeName_Passage	= "RightEdgeName_Passage";
	UPROPERTY(EditDefaultsOnly)
	FString TopEdgeName_Passage		= "TopEdgeName_Passage";
	UPROPERTY(EditDefaultsOnly)
	FString BottomEdgeName_Passage	= "BottomEdgeName_Passage";

public:
	virtual void BeginPlay() override;

	void SetLeftEdgeType(ECellEdgeType type);
	void SetRighttEdgeType(ECellEdgeType type);
	void SetTopEdgeType(ECellEdgeType type);
	void SetBottomEdgeType(ECellEdgeType type);

private:
	UPaperSpriteComponent* _leftEdgeComp_Wall;
	UPaperSpriteComponent* _rightEdgeComp_Wall;
	UPaperSpriteComponent* _TopEdgeComp_Wall;
	UPaperSpriteComponent* _bottomEdgeComp_Wall;

	UPaperSpriteComponent* _leftEdgeComp_Passage;
	UPaperSpriteComponent* _rightEdgeComp_Passage;
	UPaperSpriteComponent* _topEdgeComp_Passage;
	UPaperSpriteComponent* _bottomEdgeComp_Passage;

private:
	void CollectComponents();
};
/*----------------------------------------------------------------------------------------------------*/