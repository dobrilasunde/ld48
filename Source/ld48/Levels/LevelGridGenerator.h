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
	bool IsPath = false;
	ELevelGridCellOpened LevelGridCellOpening = ELevelGridCellOpened::None;
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

private:
	void GenerateStartCell();
	void GenerateEndCell();


private:
	int32 _rowNum = 4;
	int32 _colNum = 4;

	std::vector<std::vector<FCell>> _grid;

	FCell* _startCell;
	FCell* _endCell;
};
/*----------------------------------------------------------------------------------------------------*/