// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InMatch/HunterInMatchWidget.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/PauseGameWidget.h"

#include "HunterPlayer/HunterPlayer.h"
#include "GameState/PropHuntGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UHunterInMatchWidget::UHunterInMatchWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UPauseGameWidget>WidgetClass(TEXT("/Game/Widgets/Menu/BP_PauseGameWidget.BP_PauseGameWidget_C"));
	if (WidgetClass.Succeeded())
	{
		PauseGameWidgetClass = WidgetClass.Class;
	}
}

void UHunterInMatchWidget::NativeConstruct()
{
	AGameState* PropHuntGameState = GetWorld()->GetGameState<AGameState>();
	if (PropHuntGameState)
	{
		if (IGameStateInterface* Interface = Cast<IGameStateInterface>(PropHuntGameState))
		{
			//Binding The GameState MatchTimer Delegate
			Interface->GetPropHuntGameState()->OnInMatchTimerChange.AddUObject(this, &UHunterInMatchWidget::SetTextOnMatchTimerUpdate);

			Interface->GetPropHuntGameState()->OnHunterPlayerCountChange.AddUObject(this, &UHunterInMatchWidget::OnHunterPlayerTotalCountChange);
			Interface->GetPropHuntGameState()->OnPropPlayerCountChange.AddUObject(this, &UHunterInMatchWidget::OnPropPlayerTotalCountChange);

		}
	}

	/*Finding The Hunter Player And Retreving The UObject Class Instance (PropProximity)*/
	if (IHunterPlayerInterface* PlayerInterface = Cast<IHunterPlayerInterface>(GetOwningPlayer()->GetPawn()))
	{
		PlayerInterface->GetPropProximityInstance()->ProximityNotifierDelegate.BindUObject(this, &UHunterInMatchWidget::OnProximityChange);
	}

	//Adding Widget To Widget Switcher
	if (PauseGameWidgetClass)
	{
		PauseGameWidget = CreateWidget<UPauseGameWidget>(this, PauseGameWidgetClass);
		if(PauseGameWidget)
		{
			WidgetSwitcher->AddChild(PauseGameWidget);
		}
	}
	
}

void UHunterInMatchWidget::SetTextOnMatchTimerUpdate(int32 TimerValue)
{
	//Converting Seconds Value Into Minutes And Seconds
	Minutes = TimerValue / 60;
	Seconds = TimerValue % 60;

	InMatchTimerText_Minutes->SetText(FText::AsNumber(Minutes));
	InMatchTimerText_Seconds->SetText(FText::AsNumber(Seconds));
}

void UHunterInMatchWidget::OnProximityChange(EProximityRange CurrentRange)
{
	switch (CurrentRange)
	{
	case EProximityRange::Hot:UpdateProximityTextAndColor(HotText, HotTextColor);
		break;
	case EProximityRange::Warm:UpdateProximityTextAndColor(WarmText, WarmTextColor);
		break;
	case EProximityRange::Cool:UpdateProximityTextAndColor(CoolText, CoolTextColor);
		break;
	case EProximityRange::Cold:UpdateProximityTextAndColor(ColdText, ColdTextColor);
		break;
	}

}

void UHunterInMatchWidget::ChangeIndexOnWidgetSwitcher(int Index)
{
	WidgetSwitcher->SetActiveWidgetIndex(Index);
}

/*--------------------------------------------------------------------------------------*/

void UHunterInMatchWidget::OnHunterPlayerTotalCountChange(int HunterPlayerCount)
{
	HunterTotalAliveCount->SetText(FText::AsNumber(HunterPlayerCount));
}

void UHunterInMatchWidget::OnPropPlayerTotalCountChange(int PropPlayerCount)
{
	PropTotalAliveCount->SetText(FText::AsNumber(PropPlayerCount));
}

/*-------------------------------------------------------------------------------------------*/

///void UHunterInMatchWidget::OnPropPlayerCaught(int HunterCount, int PropCount)
//{
//	HunterTotalAliveCount->SetText(FText::AsNumber(HunterCount));
//	PropTotalAliveCount->SetText(FText::AsNumber(PropCount));
//}

void UHunterInMatchWidget::UpdateProximityTextAndColor(const FText Text, const FLinearColor Color)
{
	PropProximityText->SetText(Text);
	PropProximityText->SetColorAndOpacity(Color);
}
