// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetOwner()->GetActorLocation();
	if (MoveDuration <= 0) MoveDuration = 1.0f; //default the move duration to 1 if it gets set to 0 or negative
	
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Move(DeltaTime);
}

//Move the owner of this component based on the Move Offset
void UMoveComponent::Move(const float& DeltaTime)
{
	if (!CanMove) return;
	FVector MoveDirection = Velocity.GetSafeNormal();
	if (ShouldReverse()) {
		StartLocation = StartLocation + MoveDirection * PlatformRange;
		Velocity = -Velocity;
		MoveDirection = Velocity.GetSafeNormal();
	}
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = StartLocation + MoveDirection * PlatformRange;
	float Speed = FVector::Distance(StartLocation, TargetLocation) / MoveDuration;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);

}

bool UMoveComponent::ShouldReverse() const
{
	return GetDistanceMoved() >= PlatformRange;
}

float UMoveComponent::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetOwner()->GetActorLocation());
}

