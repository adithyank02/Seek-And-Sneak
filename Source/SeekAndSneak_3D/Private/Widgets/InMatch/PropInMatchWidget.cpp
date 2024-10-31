// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InMatch/PropInMatchWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/PauseGameWidget.h"

#include "PropPlayer/PropPlayer.h"
#include "Interface/Player/PropPlayerInterface.h"

#include "GameState/PropHuntGameState.h"

#include "Kismet/KismetSystemLibrary.h"

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

			Interface->GetPropHuntGameState()->OnHunterPlayerCountChange.AddUObject(this, &UPropInMatchWidget::OnHunterPlayerTotalCountChange);
			Interface->GetPropHuntGameState()->OnPropPlayerCountChange.AddUObject(this, &UPropInMatchWidget::OnPropPlayerTotalCountChange);
		}
	}

	//Adding Widget To Widget Switcher
	if (PauseGameWidgetClass)
	{
		PauseGameWidget = CreateWidget<UPauseGameWidget>(GetOwningPlayer(), PauseGameWidgetClass);
		if (PauseGameWidget)
		{
			WidgetSwitcher->AddChild(PauseGameWidget);
		}
	}

	//Binding With Prop Player Health
	if (IPropPlayerInterface* PlayerInterface = Cast<IPropPlayerInterface>(GetOwningPlayer()->GetPawn()))
	{
		PlayerInterface->GetPropPlayerRef()->PropPlayerDamaged.AddUObject(this, &UPropInMatchWidget::SetPlayerHealthOnDamage);

		TotalPercentage = 1.0f;
		PlayerHealthBar->SetPercent(TotalPercentage);
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

void UPropInMatchWidget::SetPlayerHealthOnDamage(float DamageCaused)
{
	float InPercentage = DamageCaused * 0.1;
	TotalPercentage -= InPercentage;
	PlayerHealthBar->SetPercent(TotalPercentage);
}

void UPropInMatchWidget::OnHunterPlayerTotalCountChange(int HunterPlayerCount)
{
	HunterTotalAliveCount->SetText(FText::AsNumber(HunterPlayerCount));
}

void UPropInMatchWidget::OnPropPlayerTotalCountChange(int PropPlayerCount)
{
	PropTotalAliveCount->SetText(FText::AsNumber(PropPlayerCount));
}

