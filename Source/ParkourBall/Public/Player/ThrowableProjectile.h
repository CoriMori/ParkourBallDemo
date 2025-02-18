// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PARKOURBALL_API AThrowableProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowableProjectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UFUNCTION()
	void OnRelease(FVector Velocity); //handle what happens when the throwable is released

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TObjectPtr<USoundBase> HitSound; //Sound the will be played when the throwable collides with something
	
	UPROPERTY(EditDefaultsOnly, Category = Gameplay, meta=(DisplayName="SFX Bounce Delay"))
	float SFXBounceDelay = 0.15f;
	
	UFUNCTION()
	void SetSoundPlaying(bool Value) { IsSoundPlaying = Value;}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly);
	float ThrowForce = 3000.0f;

private:
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	TObjectPtr<USphereComponent> CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	bool IsSoundPlaying = false;

};
