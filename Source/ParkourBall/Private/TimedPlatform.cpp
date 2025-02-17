// Fill out your copyright notice in the Description page of Project Settings.


#include "TimedPlatform.h"
#include "MoveComponent.h"

ATimedPlatform::ATimedPlatform()
{
	if (TimerDuration <= 0.0f) TimerDuration = 1.0f; //prevent timer duration from being less than 0
}

void ATimedPlatform::HandleButtonTrigger()
{
	if (TimerActive) return;
	if (ShouldToggleMovement) {
		ToggleCanMove();
		GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &ATimedPlatform::ToggleCanMove, TimerDuration, false);
	}

	if (ShouldToggleRotation) {
		ToggleCanRotate();
		GetWorldTimerManager().SetTimer(RotateTimerHandle, this, &ATimedPlatform::ToggleCanRotate, TimerDuration, false);
	}
}

void ATimedPlatform::ToggleCanMove()
{
	ToggleTimerActive();
	GetMoveComp()->SetCanMove(!GetMoveComp()->GetCanMove());
}

void ATimedPlatform::ToggleCanRotate()
{
	ToggleTimerActive();
	GetMoveComp()->SetCanRotate(!GetMoveComp()->GetCanRotate());
}

void ATimedPlatform::ToggleTimerActive()
{
	TimerActive = !TimerActive;
}
