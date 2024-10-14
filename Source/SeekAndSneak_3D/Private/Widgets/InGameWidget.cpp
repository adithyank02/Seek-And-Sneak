// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InGameWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "HunterPlayer/HunterPlayer.h"

void UInGameWidget::NativeConstruct()
{
	/*Finding The Hunter Player And Retreving The UObject Class Instance (PropProximity)*/
	AActor* PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AHunterPlayer::StaticClass());
	if (IHunterPlayerInterface* PlayerInterface = Cast<IHunterPlayerInterface>(PlayerActor))
	{		
		PlayerInterface->GetPropProximityInstance()->ProximityNotifierDelegate.BindUObject(this, &UInGameWidget::OnProximityChange);
	}
}

void UInGameWidget::OnProximityChange(EProximityRange CurrentRange)
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

void UInGameWidget::UpdateProximityTextAndColor(const FText Text, const FLinearColor Color)
{
	PropProximityText->SetText(Text);
	PropProximityText->SetColorAndOpacity(Color);
}
