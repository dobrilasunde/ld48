// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include <Components/ChildActorComponent.h>
#include "LevelGridCell.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UENUM(BlueprintType)
enum class ECellEdgeType : uint8
{
	Wall,
	Passage
};
/*----------------------------------------------------------------------------------------------------*/
struct FSpawnMarker
{
	FVector SpawnLocation = FVector::ZeroVector;
	bool IsSpawned = false;
	int32 Weight = 1;
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

	UPROPERTY(EditDefaultsOnly)
	ADoor* _doorLeft;
	UPROPERTY(EditDefaultsOnly)
	ADoor* _doorRight;
	UPROPERTY(EditDefaultsOnly)
	ADoor* _doorTop;
	UPROPERTY(EditDefaultsOnly)
	ADoor* _doorBottom;

	UFUNCTION(BlueprintCallable)
	void SetDoor(ADoor* door);

public:
	ALevelGridCell();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	void SetLeftEdgeType(ECellEdgeType type);
	void SetRightEdgeType(ECellEdgeType type);
	void SetTopEdgeType(ECellEdgeType type);
	void SetBottomEdgeType(ECellEdgeType type);

	const FTransform& GetPlayerStart() const;

	TArray<FSpawnMarker>& GetSpawnLocations();

	void SetSpawnWeight(int32 weight);
	int32 GetSpawnWeight() const;

	void ActivateDoors();

private:
	UPaperSpriteComponent* _leftEdgeComp_Wall;
	UPaperSpriteComponent* _rightEdgeComp_Wall;
	UPaperSpriteComponent* _TopEdgeComp_Wall;
	UPaperSpriteComponent* _bottomEdgeComp_Wall;

	UPaperSpriteComponent* _leftEdgeComp_Passage;
	UPaperSpriteComponent* _rightEdgeComp_Passage;
	UPaperSpriteComponent* _topEdgeComp_Passage;
	UPaperSpriteComponent* _bottomEdgeComp_Passage;

	ECellEdgeType _leftEdgeType = ECellEdgeType::Wall;
	ECellEdgeType _rightEdgeType = ECellEdgeType::Wall;
	ECellEdgeType _topEdgeType = ECellEdgeType::Wall;
	ECellEdgeType _bottomEdgeType = ECellEdgeType::Wall;

	UPROPERTY(EditAnywhere)
	USceneComponent* _playerStartPosition;

	TArray<FSpawnMarker> _spawnLocations;

	UPROPERTY(VisibleAnywhere)
	int32 _spawnWeight = 1;

private:
	void CollectComponents();
};
/*----------------------------------------------------------------------------------------------------*/