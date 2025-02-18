// Fill out your copyright notice in the Description page of Project Settings.


#include "Platforms/PuzzlePlatform.h"
#include "Components/BoxComponent.h"
#include "CustomComponents/MoveComponent.h"

// Sets default values
APuzzlePlatform::APuzzlePlatform()
{
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	SetRootComponent(CollisionComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	Mesh->SetupAttachment(GetRootComponent());

	MoveComp = CreateDefaultSubobject<UMoveComponent>("Platform Movement Component");
}

void APuzzlePlatform::HandleButtonTrigger()
{
	if (MoveComp->GetReverseIterations() == 0 && IsElevator) {
		MoveComp->SetReverseIterations(StartingReverseIterations);
	}
	MoveComp->SetCanMove(true);
}

// Called when the game starts or when spawned
void APuzzlePlatform::BeginPlay()
{
	Super::BeginPlay();

	StartingReverseIterations = MoveComp->GetReverseIterations();
}

