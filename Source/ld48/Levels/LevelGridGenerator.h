// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "LevelShared.h"
#include <vector>
#include "LevelGridCell.h"
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

	int32 x = -1;
	int32 y = -1;

public:
	std::string ToString() const 
	{
		return "test";
	}
};
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class LD48_API ALevelGridGenerator : public AActor
{
	GENERATED_BODY()

public:
	ALevelGridGenerator();

	virtual void BeginPlay() override;

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


	TSubclassOf<ALevelGridCell> GetRandomCellClass() const;
	void SpawnCell(FVector location, TSubclassOf<ALevelGridCell> clazz);

private:
	std::vector<std::vector<FCell>> _grid;

	FCell* _startCell = nullptr;
	FCell* _endCell = nullptr;
};
/*----------------------------------------------------------------------------------------------------*/