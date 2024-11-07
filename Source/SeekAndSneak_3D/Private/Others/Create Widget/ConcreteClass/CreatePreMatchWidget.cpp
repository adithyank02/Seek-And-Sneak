// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/Create Widget/ConcreteClass/CreatePreMatchWidget.h"
#include "Widgets/PreMatch/CharacterPreMatchWidget.h"
#include "Blueprint/UserWidget.h"

CreatePreMatchWidget::CreatePreMatchWidget()
{
	//Retreving BP Widget Class
	PreMatchWidgetClass = LoadClass<UCharacterPreMatchWidget>(nullptr, TEXT("/Game/Widgets/InMatch/BP_CharacterPreMatchWidget.BP_CharacterPreMatchWidget_C"));
}

CreatePreMatchWidget::~CreatePreMatchWidget()
{
}

void CreatePreMatchWidget::Begin(APlayerController* PlayerController, ECharacterType CharacterType)
{
	if (PreMatchWidgetClass && PlayerController->IsLocalController())
	{
		//Creating Widget
	    PreMatchWidget = CreateWidget<UCharacterPreMatchWidget>(PlayerController, PreMatchWidgetClass);
		if (PreMatchWidget)
		{
			PreMatchWidget->AddToViewport();
		}
		
	}

}

void CreatePreMatchWidget::End()
{
	if(PreMatchWidget)PreMatchWidget->RemoveFromParent();
	//RemovePointerRef();
}

void CreatePreMatchWidget::RemovePointerRef()
{
	PreMatchWidget = nullptr;
	delete PreMatchWidget;

	PreMatchWidgetClass = nullptr;
	delete PreMatchWidgetClass;
}
