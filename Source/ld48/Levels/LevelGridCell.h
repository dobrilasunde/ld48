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
class USceneComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ALevelGridCell : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FString LeftEdgeName_Wall		= "LeftEdge_Wall";
	UPROPERTY(EditDefaultsOnly)
	FString RightEdgeName_Wall		= "RightEdge_Wall";
	UPROPERTY(EditDefaultsOnly)
	FString TopEdgeName_Wall		= "TopEdge_Wall";
	UPROPERTY(EditDefaultsOnly)
	FString BottomEdgeName_Wall		= "BottomEdge_Wall";

	UPROPERTY(EditDefaultsOnly)
	FString LeftEdgeName_Passage	= "LeftEdge_Passage";
	UPROPERTY(EditDefaultsOnly)
	FString RightEdgeName_Passage	= "RightEdge_Passage";
	UPROPERTY(EditDefaultsOnly)
	FString TopEdgeName_Passage		= "TopEdge_Passage";
	UPROPERTY(EditDefaultsOnly)
	FString BottomEdgeName_Passage	= "BottomEdge_Passage";

public:
	ALevelGridCell();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	void SetLeftEdgeType(ECellEdgeType type);
	void SetRighttEdgeType(ECellEdgeType type);
	void SetTopEdgeType(ECellEdgeType type);
	void SetBottomEdgeType(ECellEdgeType type);

	const FTransform& GetPlayerStart() const;

	const TArray<FVector>& GetSpawnLocations() const;
private:
	UPaperSpriteComponent* _leftEdgeComp_Wall;
	UPaperSpriteComponent* _rightEdgeComp_Wall;
	UPaperSpriteComponent* _TopEdgeComp_Wall;
	UPaperSpriteComponent* _bottomEdgeComp_Wall;

	UPaperSpriteComponent* _leftEdgeComp_Passage;
	UPaperSpriteComponent* _rightEdgeComp_Passage;
	UPaperSpriteComponent* _topEdgeComp_Passage;
	UPaperSpriteComponent* _bottomEdgeComp_Passage;

	UPROPERTY(EditAnywhere)
	USceneComponent* _playerStartPosition;

	TArray<FVector> _spawnLocations;

private:
	void CollectComponents();
};
/*----------------------------------------------------------------------------------------------------*/