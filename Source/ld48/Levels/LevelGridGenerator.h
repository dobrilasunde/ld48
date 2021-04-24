// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "LevelShared.h"
#include <vector>
#include "LevelGridGenerator.generated.h"
/*----------------------------------------------------------------------------------------------------*/
struct FCell
{
	ETileState TileState = ETileState::None;
	ELevelGridCellOpened LevelGridCellOpening = ELevelGridCellOpened::None;

	std::vector<FCell*> Adjacent;
	FCell* Parent;
	float f;
	float g;
	float h;
	bool InOpenSet;
	bool InClosedSet;
	bool Blocked;
};
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ALevelGridGenerator : public AActor
{
	GENERATED_BODY()

public:
	ALevelGridGenerator();

	FCell* GetStartCell() const;
	FCell* GetEndCell() const;

	bool FindPath(FCell* start,FCell* goal);
	void UpdatePathTiles(FCell* start);

	const std::vector<std::vector<FCell>>& GetGrid() const;

public:
	UPROPERTY(EditAnywhere)
	int32 RowNum = 4;
	UPROPERTY(EditAnywhere)
	int32 ColNum = 4;

private:
	void GenerateStartEndCell();

	EWall ChooseRandomWall();

private:
	std::vector<std::vector<FCell>> _grid;

	FCell* _startCell = nullptr;
	FCell* _endCell = nullptr;
};
/*----------------------------------------------------------------------------------------------------*/