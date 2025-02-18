// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzlePlatform.generated.h"

class UBoxComponent;
class UMoveComponent;
UCLASS()
class PARKOURBALL_API APuzzlePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzlePlatform();

	virtual void HandleButtonTrigger();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UMoveComponent* GetMoveComp() { return MoveComp; }

	int32 StartingReverseIterations = -1;

	//Will reset Reverse Iterations when linked button is hit
	UPROPERTY(EditAnywhere)
	bool IsElevator = false;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> CollisionComp;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMoveComponent> MoveComp;
};
