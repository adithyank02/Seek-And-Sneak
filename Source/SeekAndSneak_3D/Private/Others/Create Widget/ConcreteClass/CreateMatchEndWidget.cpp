// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/Create Widget/ConcreteClass/CreateMatchEndWidget.h"
#include "Widgets/WinnerWidget/WinnerShowingWidget.h"

CreateMatchEndWidget::CreateMatchEndWidget()
{
	WinnerShowingWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/EndingWidget/BP_WinnerShowingWidget.BP_WinnerShowingWidget_C"));
}

CreateMatchEndWidget::~CreateMatchEndWidget()
{
}

void CreateMatchEndWidget::Begin(APlayerController* PlayerController, ECharacterType CharacterType)
{
	if (WinnerShowingWidgetClass)
	{
		WinnerWidget = CreateWidget<UWinnerShowingWidget>(PlayerController, WinnerShowingWidgetClass);
		WinnerWidget->AddToViewport();
	}
}

void CreateMatchEndWidget::End()
{
	WinnerWidget->RemoveFromParent();
}

void CreateMatchEndWidget::ChangeWidgetSwitcherIndex(int Index)
{
	//Switching To EndGameWidget
	if (WinnerWidget)WinnerWidget->ChangWidgetSwitcherIndex(Index);
}
