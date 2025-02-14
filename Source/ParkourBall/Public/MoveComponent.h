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
	void SetCanMove(bool Value) { CanMove = Value; }

	bool GetCanReverse() const { return CanReverse; }
	void SetCanReverse(bool Value) { CanReverse = Value; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Move(const float& DeltaTime);
	FVector StartLocation;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Platform Velocity"))
	FVector Velocity = FVector(1.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Platform Range"))
	float PlatformRange = 100.0f;
	
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Move Duration"))
	float MoveDuration = 1.0f;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Can Move"))
	bool CanMove = false;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Can Reverse"))
	bool CanReverse = false;

	bool ShouldReverse() const;

	float GetDistanceMoved() const;
		
};
