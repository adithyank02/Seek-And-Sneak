// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InMatch/HunterInMatchWidget.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/PauseGameWidget.h"
#include "Kismet/GameplayStatics.h"
#include "HunterPlayer/HunterPlayer.h"

#include "GameState/PropHuntGameState.h"

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

	APropHuntGameState* PropHuntGameState = GetWorld()->GetGameState<APropHuntGameState>();
	if (PropHuntGameState)
	{
		if (IGameStateInterface* Interface = Cast<IGameStateInterface>(PropHuntGameState))
		{
			//Binding The GameState MatchTimer Delegate
			Interface->GetPropHuntGameState()->OnInMatchTimerChange.AddUObject(this, &UHunterInMatchWidget::SetTextOnMatchTimerUpdate);
			PropHuntGameState->OnPropPlayerCountChange.AddUObject(this, &UHunterInMatchWidget::OnPropPlayerCaught);

			Interface->GetTeamInfo(HunterPlayerCount, PropPlayerCount);
			HunterTotalAliveCount->SetText(FText::AsNumber(HunterPlayerCount));
			PropTotalAliveCount->SetText(FText::AsNumber(PropPlayerCount));
		}
	}

	/*Finding The Hunter Player And Retreving The UObject Class Instance (PropProximity)*/
	AActor* PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AHunterPlayer::StaticClass());
	if (IHunterPlayerInterface* PlayerInterface = Cast<IHunterPlayerInterface>(PlayerActor))
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

void UHunterInMatchWidget::OnPropPlayerCaught()
{
	PropPlayerCount--;
	PropTotalAliveCount->SetText(FText::AsNumber(PropPlayerCount));
}

void UHunterInMatchWidget::UpdateProximityTextAndColor(const FText Text, const FLinearColor Color)
{
	PropProximityText->SetText(Text);
	PropProximityText->SetColorAndOpacity(Color);
}
