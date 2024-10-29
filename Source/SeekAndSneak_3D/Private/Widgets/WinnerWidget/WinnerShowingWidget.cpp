// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WinnerWidget/WinnerShowingWidget.h"
#include "Widgets/GameEndWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Interface/Controller/ControllerInterface.h"

UWinnerShowingWidget::UWinnerShowingWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UGameEndWidget>WidgetClass(TEXT("/Game/Widgets/Menu/BP_GameEndWidget.BP_GameEndWidget_C"));
	if (WidgetClass.Succeeded())
	{
		GameEndWidgetClass = WidgetClass.Class;
	}
}

void UWinnerShowingWidget::NativeConstruct()
{
	AddEndGameChildWidget();

	if (IControllerInterface* Interface = Cast<IControllerInterface>(GetOwningPlayer()))
	{
		MatchWinnerCharacterType = Interface->GetWinnerCharacterType();
	}
	SetAnnouncingText();
}

void UWinnerShowingWidget::SetAnnouncingText()
{
	FString AnnouncingString;
	if (MatchWinnerCharacterType == ECharacterType::HunterCharacter)
	{
		AnnouncingString = HunterWinningText;
	}
	else
	{
		AnnouncingString = PropWinningText;
	}
	WinnerAnnouncingText->SetText(FText::FromString(AnnouncingString));
}

void UWinnerShowingWidget::AddEndGameChildWidget()
{
	GameEndWidget = CreateWidget<UGameEndWidget>(GetOwningPlayer(), GameEndWidgetClass);
	if (GameEndWidget)WidgetSwitcher->AddChild(GameEndWidget);
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UWinnerShowingWidget::ChangWidgetSwitcherIndex(int Index)
{
	WidgetSwitcher->SetActiveWidgetIndex(Index);

}
