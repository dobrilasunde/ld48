// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "LevelGridCell.h"
#include <PaperSpriteComponent.h>
#include <Components/SceneComponent.h>
/*----------------------------------------------------------------------------------------------------*/
ALevelGridCell::ALevelGridCell()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	_playerStartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerStartPosition"));
	_playerStartPosition->SetupAttachment(RootComponent);
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::BeginPlay()
{
	Super::BeginPlay();

	CollectComponents();
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetLeftEdgeType(ECellEdgeType type)
{
	if (_leftEdgeComp_Wall == nullptr || _leftEdgeComp_Passage == nullptr)
	{
		return;
	}

	if (type == ECellEdgeType::Wall)
	{
		_leftEdgeComp_Wall->SetHiddenInGame(false);
		_leftEdgeComp_Wall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		_leftEdgeComp_Passage->SetHiddenInGame(true);
	}
	else if (type == ECellEdgeType::Passage)
	{
		_leftEdgeComp_Wall->SetHiddenInGame(true);
		_leftEdgeComp_Wall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		_leftEdgeComp_Passage->SetHiddenInGame(false);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetRighttEdgeType(ECellEdgeType type)
{
	if (_rightEdgeComp_Wall == nullptr || _rightEdgeComp_Passage == nullptr)
	{
		return;
	}

	if (type == ECellEdgeType::Wall)
	{
		_rightEdgeComp_Wall->SetHiddenInGame(false);
		_rightEdgeComp_Wall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		_rightEdgeComp_Passage->SetHiddenInGame(true);
	}
	else if (type == ECellEdgeType::Passage)
	{
		_rightEdgeComp_Wall->SetHiddenInGame(true);
		_rightEdgeComp_Wall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		_rightEdgeComp_Passage->SetHiddenInGame(false);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetTopEdgeType(ECellEdgeType type)
{
	if (_TopEdgeComp_Wall == nullptr || _topEdgeComp_Passage == nullptr)
	{
		return;
	}

	if (type == ECellEdgeType::Wall)
	{
		_TopEdgeComp_Wall->SetHiddenInGame(false);
		_TopEdgeComp_Wall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		_topEdgeComp_Passage->SetHiddenInGame(true);
	}
	else if (type == ECellEdgeType::Passage)
	{
		_TopEdgeComp_Wall->SetHiddenInGame(true);
		_TopEdgeComp_Wall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		_topEdgeComp_Passage->SetHiddenInGame(false);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetBottomEdgeType(ECellEdgeType type)
{
	if (_bottomEdgeComp_Wall == nullptr || _bottomEdgeComp_Passage == nullptr)
	{
		return;
	}

	if (type == ECellEdgeType::Wall)
	{
		_bottomEdgeComp_Wall->SetHiddenInGame(false);
		_bottomEdgeComp_Wall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		_bottomEdgeComp_Passage->SetHiddenInGame(true);
	}
	else if (type == ECellEdgeType::Passage)
	{
		_bottomEdgeComp_Wall->SetHiddenInGame(true);
		_bottomEdgeComp_Wall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		_bottomEdgeComp_Passage->SetHiddenInGame(false);
	}
}
/*----------------------------------------------------------------------------------------------------*/
const FTransform& ALevelGridCell::GetPlayerStart() const
{
	return _playerStartPosition->GetComponentToWorld();
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
		else if (compName == BottomEdgeName_Wall) _bottomEdgeComp_Wall = spriteComp;

		else if (compName == LeftEdgeName_Passage) _leftEdgeComp_Passage = spriteComp;
		else if (compName == RightEdgeName_Passage) _rightEdgeComp_Passage = spriteComp;
		else if (compName == TopEdgeName_Passage) _topEdgeComp_Passage = spriteComp;
		else if (compName == BottomEdgeName_Passage) _bottomEdgeComp_Passage = spriteComp;
	}
}
/*----------------------------------------------------------------------------------------------------*/