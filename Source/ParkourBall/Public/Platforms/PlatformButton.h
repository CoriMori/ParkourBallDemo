// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformButton.generated.h"

class UBoxComponent;
class APuzzlePlatform;
UCLASS()
class PARKOURBALL_API APlatformButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformButton();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UBoxComponent> CollisionComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TArray<APuzzlePlatform*> LinkedPlatforms; //platforms that will be effected by this button

	bool ButtonHit = false;

	UPROPERTY(EditAnywhere)
	float ButtonResetDealy = 1.0f;

	UFUNCTION()
	void ToggleButtonHit();
};
