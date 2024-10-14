// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/MainMenu/MainMenuController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

AMainMenuController::AMainMenuController()
{	
	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass(TEXT("/Game/Widgets/BP_MainMenuWidget.BP_MainMenuWidget_C"));

	if (WidgetClass.Succeeded())
	{
		MainMenuClass = WidgetClass.Class;
	}
}

void AMainMenuController::BeginPlay()
{
	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuClass);
		MainMenuWidget->AddToViewport();
		bShowMouseCursor = true;		    
	}
}
