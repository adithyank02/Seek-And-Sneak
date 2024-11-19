// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InMatch/HunterInMatchWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/PauseGameWidget.h"

#include "HunterPlayer/HunterPlayer.h"
#include "GameState/PropHuntGameState.h"

#include "Kismet/GameplayStatics.h"

UHunterInMatchWidget::UHunterInMatchWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

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

		PlayerInterface->GetHunterPlayerRef()->WidgetUpdate.BindUObject(this, &UHunterInMatchWidget::OnGrenadeUpdate);
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

void UHunterInMatchWidget::OnGrenadeUpdate(ECharacterWidgetUpdate UpdateType)
{
	ThrowGrenadeAbilityImage->SetOpacity(0.5);
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

void UHunterInMatchWidget::UpdateProximityTextAndColor(const FText Text, const FLinearColor Color)
{
	PropProximityText->SetText(Text);
	PropProximityText->SetColorAndOpacity(Color);
}
