// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformButton.h"
#include "Components/BoxComponent.h"
#include "ThrowableProjectile.h"
#include "PuzzlePlatform.h"

// Sets default values
APlatformButton::APlatformButton()
{
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->OnComponentHit.AddDynamic(this, &APlatformButton::OnHit);
	SetRootComponent(CollisionComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	Mesh->SetupAttachment(CollisionComp);
}

void APlatformButton::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(AThrowableProjectile::StaticClass())) {
		LinkedPlatform->HandleButtonTrigger();
	}
}

// Called when the game starts or when spawned
void APlatformButton::BeginPlay()
{
	Super::BeginPlay();
	
}


