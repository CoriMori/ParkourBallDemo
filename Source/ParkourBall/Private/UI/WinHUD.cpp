// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WinHUD.h"
#include "Blueprint/UserWidget.h"

void AWinHUD::BeginPlay()
{
	Super::BeginPlay();

	//create the win widget if we have one set
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

//show the win screen and freeze the player
void AWinHUD::OnWin()
{
	if (!WinWidget) return;
	WinWidget->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetFirstPlayerController()->SetPause(true);
}
