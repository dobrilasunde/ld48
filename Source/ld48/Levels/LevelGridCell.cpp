// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "LevelGridCell.h"
#include <PaperSpriteComponent.h>
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::BeginPlay()
{
	Super::BeginPlay();

	CollectComponents();
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetLeftEdgeType(ECellEdgeType type)
{
	if (_leftEdgeComp_Wall || _leftEdgeComp_Passage)
	{
		return;
	}

	if (type == ECellEdgeType::Wall)
	{
		_leftEdgeComp_Wall->SetActive(true);
		_leftEdgeComp_Passage->SetActive(false);
	}
	else if (type == ECellEdgeType::Passage)
	{
		_leftEdgeComp_Wall->SetActive(false);
		_leftEdgeComp_Passage->SetActive(true);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetRighttEdgeType(ECellEdgeType type)
{
	if (_rightEdgeComp_Wall || _rightEdgeComp_Passage)
	{
		return;
	}

	if (type == ECellEdgeType::Wall)
	{
		_rightEdgeComp_Wall->SetActive(true);
		_rightEdgeComp_Passage->SetActive(false);
	}
	else if (type == ECellEdgeType::Passage)
	{
		_rightEdgeComp_Wall->SetActive(false);
		_rightEdgeComp_Passage->SetActive(true);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetTopEdgeType(ECellEdgeType type)
{
	if (_TopEdgeComp_Wall || _topEdgeComp_Passage)
	{
		return;
	}

	if (type == ECellEdgeType::Wall)
	{
		_TopEdgeComp_Wall->SetActive(true);
		_topEdgeComp_Passage->SetActive(false);
	}
	else if (type == ECellEdgeType::Passage)
	{
		_TopEdgeComp_Wall->SetActive(false);
		_topEdgeComp_Passage->SetActive(true);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetBottomEdgeType(ECellEdgeType type)
{
	if (_bottomEdgeComp_Wall|| _bottomEdgeComp_Passage)
	{
		return;
	}

	if (type == ECellEdgeType::Wall)
	{
		_bottomEdgeComp_Wall->SetActive(true);
		_bottomEdgeComp_Passage->SetActive(false);
	}
	else if (type == ECellEdgeType::Passage)
	{
		_bottomEdgeComp_Wall->SetActive(false);
		_bottomEdgeComp_Passage->SetActive(true);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::CollectComponents()
{
	TArray<UPaperSpriteComponent*> components;
	GetComponents<UPaperSpriteComponent>(components);

	for (UPaperSpriteComponent* spriteComp : components)
	{
		if (spriteComp == nullptr)
		{
			continue;
		}

		const FString compName = spriteComp->GetName();

		if (compName == LeftEdgeName_Wall) _leftEdgeComp_Wall = spriteComp;
		else if (compName == RightEdgeName_Wall) _rightEdgeComp_Wall = spriteComp;
		else if (compName == TopEdgeName_Wall) _TopEdgeComp_Wall = spriteComp;
		else if (compName == TopEdgeName_Wall) _bottomEdgeComp_Wall = spriteComp;

		else if (compName == LeftEdgeName_Passage) _leftEdgeComp_Passage = spriteComp;
		else if (compName == RightEdgeName_Passage) _rightEdgeComp_Passage = spriteComp;
		else if (compName == TopEdgeName_Passage) _topEdgeComp_Passage = spriteComp;
		else if (compName == TopEdgeName_Passage) _bottomEdgeComp_Passage = spriteComp;
	}
}
/*----------------------------------------------------------------------------------------------------*/