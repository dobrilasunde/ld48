// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "LevelGridGenerator.h"
/*----------------------------------------------------------------------------------------------------*/
ALevelGridGenerator::ALevelGridGenerator()
{
	_grid.resize(_rowNum);
	for (size_t i = 0; i < _grid.size(); ++i)
	{
		_grid[i].resize(_colNum);
	}

	//create tile grid
	for (size_t i = 0; i < _rowNum; ++i)
	{
		for (size_t j = 0; j < _colNum; ++j)
		{
			FCell newCell;
			_grid[i][j] = newCell;
		}
	}

	GenerateStartCell();
	GenerateEndCell();


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
void ALevelGridGenerator::GenerateStartCell()
{
	
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridGenerator::GenerateEndCell()
{

}
/*----------------------------------------------------------------------------------------------------*/