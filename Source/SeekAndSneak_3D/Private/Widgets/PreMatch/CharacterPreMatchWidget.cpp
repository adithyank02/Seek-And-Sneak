// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PreMatch/CharacterPreMatchWidget.h"
#include "Components/TextBlock.h"

#include "GameState/PropHuntGameState.h"
#include "Interface/Controller/ControllerInterface.h"
#include "Interface/GameState/GameStateInterface.h"

#include "Kismet/KismetSystemLibrary.h"

void UCharacterPreMatchWidget::NativeConstruct()
{
	AGameState* PropHuntGameState =  GetWorld()->GetGameState<AGameState>();
	if (PropHuntGameState)
	{
		if (IGameStateInterface* Interface = Cast<IGameStateInterface>(PropHuntGameState))
		{
			Interface->GetPropHuntGameState()->OnMatchTimerChange.AddUObject(this, &UCharacterPreMatchWidget::SetTextOnMatchTimerUpdate);

			PropHuntGameStateInterface.SetObject(PropHuntGameState);
			PropHuntGameStateInterface.SetInterface(Interface);

			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Stored Game"));
		}
	}

	SetCharacterType();

	SetWidgetText();
}

void UCharacterPreMatchWidget::SetCharacterType()
{
	if (IControllerInterface* ControllerInterface = Cast<IControllerInterface>(GetOwningPlayer()))
	{
		PlayerCharacter = ControllerInterface->GetCharacterType();
	}
}

void UCharacterPreMatchWidget::SetTextOnMatchTimerUpdate(int32 MatchTimer)
{
	PreMatchTimer->SetText(FText::AsNumber(MatchTimer));

}

void UCharacterPreMatchWidget::SetWidgetText()
{
	FString CharacterText;
	FString CharacterObjective;
	FString ShowingTimeText;

	if (PlayerCharacter == ECharacterType::HunterCharacter)
	{
		CharacterText = FString("Hunter");
		CharacterObjective = FString("Find And Destroy The Props Before Time Finish");
		ShowingTimeText = FString("MATCH STARTS IN");
	}
	else
	{
        CharacterText = FString("Prop");
        CharacterObjective = FString("Hide from the hunter and survive till the end");
		ShowingTimeText = FString("PROP HIDING TIME");
	}
	CharacterTypeText->SetText(FText::FromString(CharacterText));
	CharacterObjectiveText->SetText(FText::FromString(CharacterObjective));
	ShowTimerText->SetText(FText::FromString(ShowingTimeText));
}
