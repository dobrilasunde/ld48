// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "LevelShared.h"
#include <vector>
#include "LevelGridCell.h"
#include <string>
#include "LevelGridGenerator.generated.h"
/*----------------------------------------------------------------------------------------------------*/
struct FCell
{
	ETileState TileState = ETileState::None;

	bool IsLeftOpen = false;
	bool IsRightOpen = false;
	bool IsTopOpen = false;
	bool IsBottomOpen = false;

	std::vector<FCell*> Adjacent;
	FCell* Parent = nullptr;
	float f = 0.0f;
	float g = 0.0f;
	float h = 0.0f;
	bool InOpenSet = false;
	bool InClosedSet = false;
	bool Blocked = false;

	int32 x = -1;
	int32 y = -1;

	int32 TileNumber = 1;
};
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ALevelGridGenerator : public AActor
{
	GENERATED_BODY()

public:
	ALevelGridGenerator();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	const FVector& GetPlayerStartLocation() const;

	TArray<FSpawnMarker>& GetAllSpawnMarkers();
	
	const TArray<ALevelGridCell*>& GetSpawnedCells() const;

	void SaveSpawnMarkers();

public:
	UPROPERTY(EditDefaultsOnly)
	int32 RowNum = 4;
	UPROPERTY(EditDefaultsOnly)
	int32 ColNum = 4;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ALevelGridCell>> PossibleCellClasses;
	UPROPERTY(EditDefaultsOnly)
	FVector CellBaseSize = FVector::ZeroVector;

private:
	void Initialize();

	FCell* GetStartCell() const;
	FCell* GetEndCell() const;

	bool FindPath(FCell* start, FCell* goal);
	void UpdatePathTiles(FCell* start);

	const std::vector<std::vector<FCell>>& GetGrid() const;

	void GenerateStartEndCell();

	EWall ChooseRandomWall();

	void DetermineOpenedCellSides();

	TSubclassOf<ALevelGridCell> GetRandomCellClass() const;
	ALevelGridCell* SpawnCell(FVector location, TSubclassOf<ALevelGridCell> clazz);

	
private:
	std::vector<std::vector<FCell>> _grid;

	FCell* _startCell = nullptr;
	FCell* _endCell = nullptr;

	UPROPERTY()
	TArray<ALevelGridCell*> SpawnedCells;

	UPROPERTY()
	FVector _playerStartLocation = FVector::ZeroVector;

	TArray<FSpawnMarker> _allSpawnMarkers;
};
/*----------------------------------------------------------------------------------------------------*/