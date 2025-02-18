// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WinHUD.generated.h"

/**
 * 
 */
UCLASS()
class PARKOURBALL_API AWinHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> WinWidgetClass;

	void OnWin();

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUserWidget> WinWidget;
	
};
