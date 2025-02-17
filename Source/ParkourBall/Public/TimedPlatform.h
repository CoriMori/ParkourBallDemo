// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatform.h"
#include "TimedPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PARKOURBALL_API ATimedPlatform : public APuzzlePlatform
{
	GENERATED_BODY()

public:
	ATimedPlatform();

	virtual void HandleButtonTrigger() override;
	
	UFUNCTION()
	void ToggleCanMove();

	UFUNCTION()
	void ToggleCanRotate();

	UPROPERTY(EditAnywhere)
	float TimerDuration = 5.0f;

	UPROPERTY(EditAnywhere)
	bool ShouldToggleMovement = false;

	UPROPERTY(EditAnywhere)
	bool ShouldToggleRotation = false;

private:
	FTimerHandle MoveTimerHandle;
	FTimerHandle RotateTimerHandle;

	bool TimerActive = false;
	void ToggleTimerActive();
	
};
