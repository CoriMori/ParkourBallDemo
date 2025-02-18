// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WinHUD.h"
#include "Blueprint/UserWidget.h"

void AWinHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WinWidgetClass) {
		WinWidget = CreateWidget<UUserWidget>(GetWorld(), WinWidgetClass);

		if (WinWidget) {
			WinWidget->AddToViewport();
			WinWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

}

void AWinHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AWinHUD::OnWin()
{
	WinWidget->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetFirstPlayerController()->SetPause(true);
}
