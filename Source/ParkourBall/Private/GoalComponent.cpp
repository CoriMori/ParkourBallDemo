// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalComponent.h"
#include "WinHUD.h"

// Sets default values for this component's properties
UGoalComponent::UGoalComponent()
{

}


// Called when the game starts
void UGoalComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UGoalComponent::HandleWin()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AWinHUD* HUD = Cast<AWinHUD>(PlayerController->GetHUD());
	HUD->OnWin();
}


