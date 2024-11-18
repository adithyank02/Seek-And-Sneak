// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InMatch/PropInMatchWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/PauseGameWidget.h"

#include "PropPlayer/PropPlayer.h"
#include "Interface/Player/PropPlayerInterface.h"

#include "GameState/PropHuntGameState.h"

#include "Kismet/KismetSystemLibrary.h"

UPropInMatchWidget::UPropInMatchWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
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

	//Binding With Function With  Player Delegate
	if (IPropPlayerInterface* PlayerInterface = Cast<IPropPlayerInterface>(GetOwningPlayer()->GetPawn()))
	{
		APropPlayer* PlayerRef = PlayerInterface->GetPropPlayerRef();
		PlayerRef->PropPlayerDamaged.AddUObject(this, &UPropInMatchWidget::SetPlayerHealthOnDamage);
		TotalPercentage = 1.0f;
		PlayerHealthBar->SetPercent(TotalPercentage);

		PlayerRef->PropWidgetUpdate.BindUObject(this, &UPropInMatchWidget::OnWidgetUpdate);
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

void UPropInMatchWidget::OnWidgetUpdate(ECharacterWidgetUpdate UpdateType, bool IsReset)
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Hello World"));
	switch (UpdateType)
	{
	case ECharacterWidgetUpdate::OnMorphUpdate: IsReset ? MorphAbilityImage->SetOpacity(1) : MorphAbilityImage->SetOpacity(0.5);
		break;
	case ECharacterWidgetUpdate::OnCloneUpdate: IsReset ? CloneAbilityImage->SetOpacity(1) : CloneAbilityImage->SetOpacity(0.5);
		break;
	case ECharacterWidgetUpdate::OnSmokeBombUpdate: SmokeBombAbilityImage->SetOpacity(0.5);
		break;
	}
}

