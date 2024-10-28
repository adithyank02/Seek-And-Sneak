// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InMatch/PropInMatchWidget.h"
#include "Components/TextBlock.h"
#include "GameState/PropHuntGameState.h"

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
}

void UPropInMatchWidget::SetTextOnMatchTimerUpdate(int32 TimerValue)
{
	//Converting Seconds Value Into Minutes And Seconds
	Minutes = TimerValue / 60;
	Seconds = TimerValue % 60;

	InMatchTimerText_Minutes->SetText(FText::AsNumber(Minutes));
	InMatchTimerText_Seconds->SetText(FText::AsNumber(Seconds));
}
