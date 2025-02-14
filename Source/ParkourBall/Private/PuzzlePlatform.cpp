// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatform.h"
#include "Components/BoxComponent.h"
#include "MoveComponent.h"

// Sets default values
APuzzlePlatform::APuzzlePlatform()
{
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	SetRootComponent(CollisionComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	Mesh->SetupAttachment(GetRootComponent());

	MoveComp = CreateDefaultSubobject<UMoveComponent>("Platform Movement Component");


}

// Called when the game starts or when spawned
void APuzzlePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

