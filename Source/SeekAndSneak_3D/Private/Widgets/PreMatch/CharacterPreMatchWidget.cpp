// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PreMatch/CharacterPreMatchWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "GameState/PropHuntGameState.h"
#include "Interface/Controller/ControllerInterface.h"
#include "Interface/GameState/GameStateInterface.h"


void UCharacterPreMatchWidget::NativeConstruct()
{
	AGameState* PropHuntGameState =  GetWorld()->GetGameState<AGameState>();
	if (PropHuntGameState)
	{
		if (IGameStateInterface* Interface = Cast<IGameStateInterface>(PropHuntGameState))
		{
			//Binding The GameState MatchTimer Delegate
			Interface->GetPropHuntGameState()->OnMatchTimerChange.AddUObject(this, &UCharacterPreMatchWidget::SetTextOnMatchTimerUpdate);
		}
	}


	 PropPowerUpImage_1->SetVisibility(ESlateVisibility::Hidden);
     PropPowerUpImage_2->SetVisibility(ESlateVisibility::Hidden);
     PropPowerUpImage_3->SetVisibility(ESlateVisibility::Hidden);
     PropPowerUpText_1->SetVisibility(ESlateVisibility::Hidden);
     PropPowerUpText_2->SetVisibility(ESlateVisibility::Hidden);
     PropPowerUpText_3->SetVisibility(ESlateVisibility::Hidden); 

	SetCharacterType();

	SetWidgetText();
}

//Storing The Character Type Player
void UCharacterPreMatchWidget::SetCharacterType()
{
	if (IControllerInterface* ControllerInterface = Cast<IControllerInterface>(GetOwningPlayer()))
	{
		PlayerCharacter = ControllerInterface->GetCharacterType();
	}
}

//Delegate Binded Function
void UCharacterPreMatchWidget::SetTextOnMatchTimerUpdate(int32 MatchTimer)
{
	PreMatchTimer->SetText(FText::AsNumber(MatchTimer));

}

//Setting Widget Components According To Character
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
		ShowingTimeText = FString("HIDING TIME ENDS IN");

		//Showing the power up inputs to prop since they have movement at beginning
		PropPowerUpImage_1->SetVisibility(ESlateVisibility::Visible);
		PropPowerUpImage_2->SetVisibility(ESlateVisibility::Visible);
		PropPowerUpImage_3->SetVisibility(ESlateVisibility::Visible);
		PropPowerUpText_1->SetVisibility(ESlateVisibility::Visible);
		PropPowerUpText_2->SetVisibility(ESlateVisibility::Visible);
		PropPowerUpText_3->SetVisibility(ESlateVisibility::Visible);
	}
	CharacterTypeText->SetText(FText::FromString(CharacterText));
	CharacterObjectiveText->SetText(FText::FromString(CharacterObjective));
	ShowTimerText->SetText(FText::FromString(ShowingTimeText));
}
