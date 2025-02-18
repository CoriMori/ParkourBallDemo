// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ThrowableProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AThrowableProjectile::AThrowableProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AThrowableProjectile::OnHit);		// set up a notification for when this component hits something blocking
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;


	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 0.0f;
	ProjectileMovement->MaxSpeed = 0.0f;

	// Die after 5 seconds by default
	InitialLifeSpan = 5.0f;
}

void AThrowableProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitSound != nullptr && !IsSoundPlaying) {
		SetSoundPlaying(true);
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

		//add timer to prevent sfx overlap
		FTimerHandle ThrowableSFXHandle;
		FTimerDelegate ThrowableSFXDel;
		ThrowableSFXDel.BindUFunction(this, FName("SetSoundPlaying"), false);
		GetWorldTimerManager().SetTimer(ThrowableSFXHandle, ThrowableSFXDel, SFXBounceDelay, false);
	}
	// Only add impulse if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		//Destroy();
	}
}

void AThrowableProjectile::OnRelease(FVector Velocity)
{
	ProjectileMovement->bSimulationEnabled = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->Velocity = Velocity * 3000.0f;
	ProjectileMovement->Activate();

}

// Called when the game starts or when spawned
void AThrowableProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


