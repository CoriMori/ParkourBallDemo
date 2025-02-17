// Fill out your copyright notice in the Description page of Project Settings.


#include "WinHUD.h"
#include "Blueprint/UserWidget.h"

void AWinHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WinWidgetClass) {
		WinWidget = CreateWidget<UUserWidget>(GetWorld(), WinWidgetClass);

		if (WinWidget) {
			WinWidget->AddToViewport();
		}
	}

}

void AWinHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AWinHUD::OnWin()
{
	WinWidget->SetVisibility(ESlateVisibility::Collapsed);
	DisableInput(GetOwningPlayerController());
}
