// Fill out your copyright notice in the Description page of Project Settings.


#include "Platforms/PlatformButton.h"
#include "Components/BoxComponent.h"
#include "Player/ThrowableProjectile.h"
#include "Platforms/PuzzlePlatform.h"

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
	if (ButtonHit) return;
	if (LinkedPlatforms.Num() == 0) return;

	ToggleButtonHit();
	//set a timer to delay button reactivation
	FTimerHandle ButtonResetHandle;
	GetWorldTimerManager().SetTimer(ButtonResetHandle, this, &APlatformButton::ToggleButtonHit, ButtonResetDealy, false);

	//trigger the button event for all linked platforms
	if (OtherActor->IsA(AThrowableProjectile::StaticClass())) {
		for (APuzzlePlatform* p : LinkedPlatforms) {
			p->HandleButtonTrigger();
		}
	}
}

// Called when the game starts or when spawned
void APlatformButton::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformButton::ToggleButtonHit()
{
	ButtonHit = !ButtonHit;
}


