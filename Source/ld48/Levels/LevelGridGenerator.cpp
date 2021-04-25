// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "LevelGridGenerator.h"
#include <algorithm>
/*----------------------------------------------------------------------------------------------------*/
ALevelGridGenerator::ALevelGridGenerator()
{
	
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void ALevelGridGenerator::BeginPlay()
{
	Initialize();

	FVector rootLocation = GetActorLocation();

	FString str = ".\n";
	for (int32 y = 0; y < RowNum; ++y)
	{
		FString row;
		for (int32 x = 0; x < ColNum; ++x)
		{
			const FCell& cell = _grid[y][x];
			if (cell.TileState == ETileState::Path || 
				cell.TileState == ETileState::Start ||
				cell.TileState == ETileState::End)
			{
				FVector cellLocation = rootLocation + FVector(CellBaseSize.X * x, 0.f, CellBaseSize.Z * y);
				if (ALevelGridCell* cellActor = SpawnCell(cellLocation, GetRandomCellClass()))
				{
				}
				row += "x";
			}
			else
			{
				row += "o";
			}
		}

		str += row;
		str += "\n";
	}

	UE_LOG(LogTemp, Log, TEXT("\n%s"), *str);
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridGenerator::Initialize()
{
	_grid.resize(RowNum);
	for (size_t i = 0; i < _grid.size(); ++i)
	{
		_grid[i].resize(ColNum);
	}

	//create tile grid
	for (size_t i = 0; i < RowNum; ++i)
	{
		for (size_t j = 0; j < ColNum; ++j)
		{
			FCell newCell;
			//generating h(x)
			newCell.h = FMath::RandRange(0, 100);
			newCell.x = j;
			newCell.y = i;
			_grid[i][j] = newCell;
		}
	}

	GenerateStartEndCell();
	if (_startCell != nullptr)
	{
		_startCell->TileState = ETileState::Start;
	}
	if (_endCell != nullptr)
	{
		_endCell->TileState = ETileState::End;
	}

	//adding adjacent tiles to the vector
	for (int32 i = 0; i < RowNum; ++i)
	{
		for (int32 j = 0; j < ColNum; ++j)
		{
			if (i > 0)
			{
				_grid[i][j].Adjacent.push_back(&_grid[i - 1][j]);
			}
			if (i < RowNum - 1)
			{
				_grid[i][j].Adjacent.push_back(&_grid[i + 1][j]);
			}
			if (j > 0)
			{
				_grid[i][j].Adjacent.push_back(&_grid[i][j - 1]);
			}
			if (j < ColNum - 1)
			{
				_grid[i][j].Adjacent.push_back(&_grid[i][j + 1]);
			}
		}
	}

	bool succ = FindPath(GetEndCell(), GetStartCell());
	UE_LOG(LogTemp, Log, TEXT("success = %d"), succ);
	if (!succ)
	{
		return;
	}

	UpdatePathTiles(GetStartCell());
	DetermineOpenedCellSides();
}
/*----------------------------------------------------------------------------------------------------*/
FCell* ALevelGridGenerator::GetStartCell() const
{
	return _startCell;
}
/*----------------------------------------------------------------------------------------------------*/
FCell* ALevelGridGenerator::GetEndCell() const
{
	return _endCell;
}
/*----------------------------------------------------------------------------------------------------*/
bool ALevelGridGenerator::FindPath(FCell* start, FCell* goal)
{
	if (start == nullptr || goal == nullptr)
	{
		return false;
	}

	for (int32 i = 0; i < RowNum; ++i)
	{
		for (int32 j = 0; j < ColNum; ++j)
		{
			_grid[i][j].g = 0.0f;
			_grid[i][j].InOpenSet = false;
			_grid[i][j].InClosedSet = false;
		}
	}

	std::vector<FCell*> openSet;

	FCell* current = start;
	current->InClosedSet = true;

	const float DISTANCE_WEIGHT = 0.0f;

	do
	{
		for (FCell* neighbour : current->Adjacent)
		{
			if (neighbour->Blocked)
			{
				continue;
			}

			if (!neighbour->InClosedSet)
			{
				if (!neighbour->InOpenSet)
				{
					neighbour->Parent = current;
					//g(x) is the parent's g + cost of traversing the edge in the tree (actual path cost)
					neighbour->g = current->g + 1;
					neighbour->f = (1.f - DISTANCE_WEIGHT) * neighbour->h + DISTANCE_WEIGHT * neighbour->g;
					openSet.emplace_back(neighbour);
					neighbour->InOpenSet = true;
				}
				else
				{
					//compute g(x) cost if current becomes the parent
					float newG = current->g + 1;
					if (newG < neighbour->g)
					{
						//adopt this node
						neighbour->Parent = current;
						neighbour->g = newG;
						neighbour->f = (1.f - DISTANCE_WEIGHT) * neighbour->h + DISTANCE_WEIGHT * neighbour->g;
					}
				}
			}
		}

		if (openSet.empty())
		{
			break;
		}

		auto iter = std::min_element(openSet.begin(), openSet.end(), [](FCell* a, FCell* b) { return a->f < b->f; });

		current = *iter;
		openSet.erase(iter);
		current->InOpenSet = false;
		current->InClosedSet = true;
	} while (current != goal);

	return current == goal;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridGenerator::UpdatePathTiles(FCell* start)
{
	FCell* t = start->Parent;
	while (t != GetEndCell())
	{
		t->TileState = ETileState::Path;	
		t = t->Parent;
	}
}
/*----------------------------------------------------------------------------------------------------*/
const std::vector<std::vector<FCell>>& ALevelGridGenerator::GetGrid() const
{
	return _grid;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridGenerator::GenerateStartEndCell()
{
	EWall randomStartCellWall = ChooseRandomWall();

	int32 randomStartRow = FMath::RandRange(0, RowNum - 1);
	int32 randomStartCol = FMath::RandRange(0, ColNum - 1);

	int32 randomEndRow = FMath::RandRange(0, RowNum - 1);
	int32 randomEndCol = FMath::RandRange(0, ColNum - 1);

	switch (randomStartCellWall)
	{
	case EWall::Top:
		_startCell = &_grid[0][randomStartCol];
		_endCell = &_grid[RowNum - 1][randomEndCol];
		break;
	case EWall::Right:
		_startCell = &_grid[randomStartRow][ColNum - 1];
		_endCell = &_grid[randomEndRow][0];
		break;
	case EWall::Bottom:
		_startCell = &_grid[RowNum - 1][randomStartCol];
		_endCell = &_grid[0][randomEndCol];
		break;
	case EWall::Left:
		_startCell = &_grid[randomStartRow][0];
		_endCell = &_grid[randomEndRow][ColNum - 1];
		break;
	default:
		break;
	}
}
/*----------------------------------------------------------------------------------------------------*/
EWall ALevelGridGenerator::ChooseRandomWall()
{
	EWall RandomWall;
	RandomWall = EWall(FMath::RandRange(0, (uint8)EWall::Count - 1));
	
	return RandomWall;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridGenerator::DetermineOpenedCellSides()
{
	FCell* Cell = GetStartCell();
	if (Cell == nullptr)
	{
		return;
	}

	while (Cell != GetEndCell())
	{
		int32 i = Cell->y;
		int32 j = Cell->x;

		if (i < 0 || j < 0 || i >= RowNum || j >= ColNum)
		{
			return;
		}

		FCell* topCell = (i - 1 >= 0) ? &_grid[i - 1][j] : nullptr;
		FCell* bottomCell = (i + 1 < RowNum) ? &_grid[i + 1][j] : nullptr;
		FCell* leftCell = (j - 1 >= 0) ? &_grid[i][j - 1] : nullptr;
		FCell* rightCell = (j + 1 < ColNum) ? &_grid[i][j + 1] : nullptr;

		if (topCell && (topCell->TileState == ETileState::Path || topCell->TileState == ETileState::Start || topCell->TileState == ETileState::End))
		{
			Cell->IsTopOpen = true;
		}
		if (bottomCell && (bottomCell->TileState == ETileState::Path || bottomCell->TileState == ETileState::Start || bottomCell->TileState == ETileState::End))
		{
			Cell->IsBottomOpen = true;
		}
		if (leftCell && (leftCell->TileState == ETileState::Path || leftCell->TileState == ETileState::Start || leftCell->TileState == ETileState::End))
		{
			Cell->IsLeftOpen = true;
		}
		if (rightCell && (rightCell->TileState == ETileState::Path || rightCell->TileState == ETileState::Start || rightCell->TileState == ETileState::End))
		{
			Cell->IsRightOpen = true;
		}
		
		Cell = Cell->Parent;
	}
}
/*----------------------------------------------------------------------------------------------------*/
TSubclassOf<ALevelGridCell> ALevelGridGenerator::GetRandomCellClass() const
{
	if (PossibleCellClasses.Num() == 0)
	{
		return nullptr;
	}

	return PossibleCellClasses[FMath::RandRange(0, PossibleCellClasses.Num() - 1)];
}
/*----------------------------------------------------------------------------------------------------*/
ALevelGridCell* ALevelGridGenerator::SpawnCell(FVector location, TSubclassOf<ALevelGridCell> clazz)
{
	if (clazz == nullptr)
	{
		return nullptr;
	}

	return GetWorld()->SpawnActor<ALevelGridCell>(clazz, FTransform(location));
}
/*----------------------------------------------------------------------------------------------------*/