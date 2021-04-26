// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "LevelGridCell.h"
#include <PaperSpriteComponent.h>
#include <Components/SceneComponent.h>
#include <Engine/TargetPoint.h>
#include <Components/ChildActorComponent.h>
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetDoor(ADoor* door)
{
	UE_LOG(LogTemp, Log, TEXT(""));
}
/*----------------------------------------------------------------------------------------------------*/
ALevelGridCell::ALevelGridCell()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	_playerStartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerStartPosition"));
	_playerStartPosition->SetupAttachment(RootComponent);
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	CollectComponents();
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::BeginPlay()
{
	Super::BeginPlay();
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetLeftEdgeType(ECellEdgeType type)
{
	if (_leftEdgeComp_Wall == nullptr || _leftEdgeComp_Passage == nullptr)
	{
		return;
	}

	_leftEdgeType = type;

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
void ALevelGridCell::SetRightEdgeType(ECellEdgeType type)
{
	if (_rightEdgeComp_Wall == nullptr || _rightEdgeComp_Passage == nullptr)
	{
		return;
	}

	_rightEdgeType = type;

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

	_topEdgeType = type;

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

	_bottomEdgeType = type;

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
TArray<FSpawnMarker>& ALevelGridCell::GetSpawnLocations()
{
	return _spawnLocations;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::SetSpawnWeight(int32 weight)
{
	_spawnWeight = weight;

	for (FSpawnMarker& marker : _spawnLocations)
	{
		marker.Weight = weight;
	}
}
/*----------------------------------------------------------------------------------------------------*/
int32 ALevelGridCell::GetSpawnWeight() const
{
	return _spawnWeight;
}
/*----------------------------------------------------------------------------------------------------*/
void ALevelGridCell::ActivateDoors()
{
	if (_leftEdgeType == ECellEdgeType::Wall && _doorLeft != nullptr)
	{
		_doorLeft->Activate();
		_doorLeft->Open();
		return;
	}

	if (_rightEdgeType == ECellEdgeType::Wall && _doorRight != nullptr)
	{
		_doorRight->Activate();
		_doorRight->Open();
		return;
	}

	if (_topEdgeType == ECellEdgeType::Wall && _doorTop != nullptr)
	{
		_doorTop->Activate();
		_doorTop->Open();
		return;
	}

	if (_bottomEdgeType == ECellEdgeType::Wall && _doorBottom != nullptr)
	{
		_doorBottom->Activate();
		_doorBottom->Open();
		return;
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
		else if (compName == BottomEdgeName_Wall) _bottomEdgeComp_Wall = spriteComp;

		else if (compName == LeftEdgeName_Passage) _leftEdgeComp_Passage = spriteComp;
		else if (compName == RightEdgeName_Passage) _rightEdgeComp_Passage = spriteComp;
		else if (compName == TopEdgeName_Passage) _topEdgeComp_Passage = spriteComp;
		else if (compName == BottomEdgeName_Passage) _bottomEdgeComp_Passage = spriteComp;
	}

	TArray<UChildActorComponent*> childActors;
	GetComponents<UChildActorComponent>(childActors);

	for (int32 i = childActors.Num() - 1; i >= 0; --i)
	{
		if (childActors[i] == nullptr)
		{
			continue;
		}

		if (childActors[i]->GetChildActorClass().Get()->IsChildOf(ATargetPoint::StaticClass()))
		{
			FSpawnMarker spawnMarker;
			spawnMarker.SpawnLocation = childActors[i]->GetComponentTransform().GetLocation();
			_spawnLocations.Add(spawnMarker);
			childActors[i]->DestroyChildActor();
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/