// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InMatch/PropInMatchWidget.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/PauseGameWidget.h"
#include "GameState/PropHuntGameState.h"

UPropInMatchWidget::UPropInMatchWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UPauseGameWidget>WidgetClass(TEXT("/Game/Widgets/Menu/BP_PauseGameWidget.BP_PauseGameWidget_C"));
	if (WidgetClass.Succeeded())
	{
		PauseGameWidgetClass = WidgetClass.Class;
	}
}

void UPropInMatchWidget::NativeConstruct()
{
	AGameState* PropHuntGameState = GetWorld()->GetGameState<AGameState>();
	if (PropHuntGameState)
	{
		if (IGameStateInterface* Interface = Cast<IGameStateInterface>(PropHuntGameState))
		{
			//Binding The GameState MatchTimer Delegate
			Interface->GetPropHuntGameState()->OnInMatchTimerChange.AddUObject(this, &UPropInMatchWidget::SetTextOnMatchTimerUpdate);
		}
	}

	//Adding Widget To Widget Switcher
	if (PauseGameWidgetClass)
	{
		PauseGameWidget = CreateWidget<UPauseGameWidget>(GetOwningPlayer(), PauseGameWidgetClass);
		//if (PauseGameWidget)
		//{
			WidgetSwitcher->AddChild(PauseGameWidget);
		//}
	}
}

void UPropInMatchWidget::SetTextOnMatchTimerUpdate(int32 TimerValue)
{
	//Converting Seconds Value Into Minutes And Seconds
	Minutes = TimerValue / 60;
	Seconds = TimerValue % 60;

	InMatchTimerText_Minutes->SetText(FText::AsNumber(Minutes));
	InMatchTimerText_Seconds->SetText(FText::AsNumber(Seconds));
}

void UPropInMatchWidget::ChangeIndexOnWidgetSwitcher(int Index)
{
	WidgetSwitcher->SetActiveWidgetIndex(Index);
}
