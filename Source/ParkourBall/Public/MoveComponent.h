// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARKOURBALL_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

	bool GetCanMove() const { return CanMove; }
	
	UFUNCTION()
	void SetCanMove(bool Value) { CanMove = Value; }

	bool GetCanReverse() const { return CanReverse; }
	void SetCanReverse(bool Value) { CanReverse = Value; }

	bool GetCanRotate() const { return CanRotate; }
	void SetCanRotate(bool Value) { CanRotate = Value; }

	int32 GetReverseIterations() const { return ReverseIterations; }
	void SetReverseIterations(int32 Value) { ReverseIterations = Value; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Move(const float& DeltaTime);

	void Rotate(const float& DeltaTime);

	FVector StartLocation;
	UPROPERTY(EditAnywhere, Category = "Platform Movement", meta = (DisplayName = "Platform Velocity"))
	FVector Velocity = FVector(1.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Platform Movement", meta = (DisplayName = "Platform Range"))
	float PlatformRange = 100.0f;
	
	UPROPERTY(EditAnywhere, Category = "Platform Movement", meta = (DisplayName = "Move Duration"))
	float MoveDuration = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Platform Movement", meta = (DisplayName = "Delay Reverse"))
	bool DelayReverse = false;

	UPROPERTY(EditAnywhere, Category = "Platform Movement", meta = (DisplayName = "Delay Duration"))
	float ReverseDelayDuration = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Platform Movement", meta = (DisplayName = "Reverse Iterations"))
	int32 ReverseIterations = -1;

	UPROPERTY(EditAnywhere, Category = "Platform Settings", meta = (DisplayName = "Can Move"))
	bool CanMove = false;

	UPROPERTY(EditAnywhere, Category = "Platform Settings", meta = (DisplayName = "Can Reverse"))
	bool CanReverse = false;

	UPROPERTY(EditAnywhere, Category = "Platform Settings", meta = (DisplayName = "Can Rotate"))
	bool CanRotate = false;




	FRotator StartRotation;

	UPROPERTY(EditAnywhere, Category = "Platform Rotation", meta = (DisplayName = "Rotation Velocity"))
	FRotator RotationVelocity = FRotator(0.0f, 1.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Platform Rotation", meta = (DisplayName = "Rotation Range"))
	float RotationRange = 10.0f;

	bool ShouldReverse() const;

	float GetDistanceMoved() const;

	void HandleReverseIterations();

	FTimerHandle ReverseDelayHandle;
		
};
