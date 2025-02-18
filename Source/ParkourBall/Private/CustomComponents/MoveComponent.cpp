// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/MoveComponent.h"

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
	Rotate(DeltaTime);
}

//Move the owner of this component based on the Move Offset
void UMoveComponent::Move(const float& DeltaTime)
{
	if (!CanMove) return;
	//determine where to move to
	FVector MoveDirection = Velocity.GetSafeNormal();
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = StartLocation + MoveDirection * PlatformRange;
	float Speed = FVector::Distance(StartLocation, TargetLocation) / MoveDuration;

	//move to new location
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);

	//handle what happens at the end of the movement range
	if (AtEndOfRange()) {
		if (CanReverse) {
			StartLocation = StartLocation + MoveDirection * PlatformRange; //update the start location to be the last target location
			Velocity = -Velocity; //reverse the velocity
			HandleReverseIterations(); //handle the reverse iterations
			
			//handle reverse delay
			if (DelayReverse && CanMove) {
				CanMove = false; //toggle movement off

				//start timer
				FTimerDelegate DelayDelegate;
				DelayDelegate.BindUFunction(this, FName("SetCanMove"), true); //toggle movement back on when timer finishes
				GetOwner()->GetWorldTimerManager().SetTimer(ReverseDelayHandle, DelayDelegate, ReverseDelayDuration, false);
			}
		}
		else {
			CanMove = false; // stop trying to move if we're already reached the target location
		}
	}

}

//Rotate the owner of this component based on the Rotation Velocity
void UMoveComponent::Rotate(const float& DeltaTime)
{
	if (!CanRotate) return;
	FRotator TargetRotation = RotationVelocity * RotationMultiplier;
	//Rotate the Platform
	GetOwner()->AddActorLocalRotation(TargetRotation * DeltaTime);
}

bool UMoveComponent::AtEndOfRange() const
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

