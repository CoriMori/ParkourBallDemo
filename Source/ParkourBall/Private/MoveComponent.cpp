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
	StartRotation = GetOwner()->GetActorRotation();
	if (MoveDuration <= 0) MoveDuration = 1.0f; //default the move duration to 1 if it gets set to 0 or negative	
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Move(DeltaTime);
	Rotate(DeltaTime);
}

//Move the owner of this component based on the Move Offset
void UMoveComponent::Move(const float& DeltaTime)
{
	if (!CanMove) return;
	FVector MoveDirection = Velocity.GetSafeNormal();
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = StartLocation + MoveDirection * PlatformRange;
	float Speed = FVector::Distance(StartLocation, TargetLocation) / MoveDuration;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);

	if (ShouldReverse()) {
		if (CanReverse) {
			StartLocation = StartLocation + MoveDirection * PlatformRange;
			Velocity = -Velocity;
			HandleReverseIterations();
			
			if (DelayReverse && CanMove) {
				CanMove = false;
				FTimerDelegate DelayDelegate;
				DelayDelegate.BindUFunction(this, FName("SetCanMove"), true);
				GetOwner()->GetWorldTimerManager().SetTimer(ReverseDelayHandle, DelayDelegate, ReverseDelayDuration, false);
			}
		}
		else {
			CanMove = false; // stop trying to move if we're already reached the target location
		}
	}

}

void UMoveComponent::Rotate(const float& DeltaTime)
{
	if (!CanRotate) return;
	FRotator TargetRotation = RotationVelocity * RotationRange;
	//Rotate the Platform
	GetOwner()->AddActorLocalRotation(TargetRotation * DeltaTime);
}

bool UMoveComponent::ShouldReverse() const
{
	return GetDistanceMoved() >= PlatformRange;
}

float UMoveComponent::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetOwner()->GetActorLocation());
}

void UMoveComponent::HandleReverseIterations()
{
	if (ReverseIterations == -1) return; //always reverse
	
	if (ReverseIterations == 0) {
		CanMove = false;
		return;
	}
	ReverseIterations--;
}

