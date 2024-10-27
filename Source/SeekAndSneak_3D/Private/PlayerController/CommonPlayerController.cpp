// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/CommonPlayerController.h"

#include "HunterPlayer/HunterPlayer.h"
#include "PropPlayer/PropPlayer.h"

#include "PlayerController/HunterPlayerController.h"
#include "PlayerController/PropPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Runtime/Engine/Public/TimerManager.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/PreMatch/CharacterPreMatchWidget.h"

#include "Others/Create Widget/ConcreteClass/CreatePreMatchWidget.h"


#include "Kismet/KismetSystemLibrary.h"


/*-----------------------------Interface Function--------------------------------*/
void ACommonPlayerController::SetControllerInputBinding(ECharacterType CharacterType)
{
	SetClientInputBinding(CharacterType);
}

void ACommonPlayerController::InitializePreMatchUI()
{
	SetClientPreMatchWidget();	
}

void ACommonPlayerController::InitializeInMatchUI()
{
	SetClientInMatchWidget();
}

ECharacterType ACommonPlayerController::GetCharacterType()
{
	return OwnerCharacterType;
}
/*----------------------------Interface Function---------------------------------*/

ACommonPlayerController::ACommonPlayerController()
{	
	WidgetLibrary.Add(EWidgetType::PreMatchWidget,MakeUnique<CreatePreMatchWidget>());
}

void ACommonPlayerController::BeginPlay()
{
	Super::BeginPlay();
}


void ACommonPlayerController::SetClientInputBinding_Implementation(ECharacterType CharacterType)
{
	if (IsLocalController())
	{
		//Setting Input Accoriding To Player Character
		if (CharacterType == ECharacterType::HunterCharacter)
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ACommonPlayerController::BindHunterPlayerInputs);
			RemovePropInputRef();
		}
		else if (CharacterType == ECharacterType::PropCharacter)
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ACommonPlayerController::BindPropPlayerInputs);
			RemoveHunterInputRef();
		}
		OwnerCharacterType = CharacterType;
	}
}

//For Removing Non Used Dependecies
void ACommonPlayerController::RemoveUnwantedRef()
{
	switch (OwnerCharacterType)
	{
	case ECharacterType::HunterCharacter: RemovePropInputRef();
		break;
	case ECharacterType::PropCharacter: RemoveHunterInputRef();
	}
}


//Deleting Ref Of Input That Don't Use
void ACommonPlayerController::RemoveHunterInputRef()
{
	HunterInMatchMappingContext = nullptr;
	HunterPreMatchMappingContext = nullptr;
	HunterJogAction = nullptr;
	HunterLookAction = nullptr;
	HunterSprintAction = nullptr;
	HunterFireWeaponAction = nullptr;

	delete HunterInMatchMappingContext;
	delete HunterPreMatchMappingContext;
	delete HunterJogAction;
	delete HunterLookAction;
	delete HunterSprintAction;
	delete HunterFireWeaponAction;
}

void ACommonPlayerController::RemovePropInputRef()
{
	PropMappingContext = nullptr;
	PropMoveAction = nullptr;
	PropLookAction = nullptr;
	PropJumpAction = nullptr;
	PropMorphAction = nullptr;
	PropCloneAction = nullptr;
	PropSmokeBombAction = nullptr;

	delete PropMappingContext;
	delete PropMoveAction;
	delete PropLookAction;
	delete PropJumpAction;
	delete PropMorphAction;
	delete PropCloneAction;
	delete PropSmokeBombAction;
}

/*------------------Client Rpc---------------------*/


void ACommonPlayerController::SetClientPreMatchWidget_Implementation()
{
	//Creating Pre Match Widget
	if(IsLocalController())WidgetLibrary[EWidgetType::PreMatchWidget]->Begin(this, OwnerCharacterType);	
}

void ACommonPlayerController::SetClientInMatchWidget_Implementation()
{
	if (IsLocalController())
	{
		//Changing The MappingContext Of Hunter Player Of GamePlay
		if (OwnerCharacterType == ECharacterType::HunterCharacter)
		{
			SetHunterInMatchMappingContext();
		}
		//Removing The PreMatch Widget
		WidgetLibrary[EWidgetType::PreMatchWidget]->End();
	}

}
//Mapping Context With Full Controlls Enabled
void ACommonPlayerController::SetHunterInMatchMappingContext()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		//Setting Up The Mapping Context
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(HunterInMatchMappingContext, 0);
	}
}


/*--------------------------------------------------- Binding Input And Function ------------------------------------------------------------------*/

void ACommonPlayerController::BindHunterPlayerInputs()  //Hunter Input Bindings
{
	//Only Applied By The LocalPlayer
	if (IsLocalController())
	{
		SetInputMode(FInputModeGameOnly());

		if (UEnhancedInputComponent* EnhancedInput = Cast <UEnhancedInputComponent>(this->InputComponent))
		{
			if (AHunterPlayer* HunterPlayer = Cast<AHunterPlayer>(GetPawn()))
			{
				//Binding InputAction And The Correspoding Functions
				EnhancedInput->BindAction(HunterJogAction, ETriggerEvent::Triggered, HunterPlayer, &AHunterPlayer::PlayerJogFunction);
				EnhancedInput->BindAction(HunterLookAction, ETriggerEvent::Triggered, HunterPlayer, &AHunterPlayer::LookFunction);

				EnhancedInput->BindAction(HunterSprintAction, ETriggerEvent::Triggered, HunterPlayer, &AHunterPlayer::StartSprintFunction);
				EnhancedInput->BindAction(HunterSprintAction, ETriggerEvent::Completed, HunterPlayer, &AHunterPlayer::StopSprintFunction);

				EnhancedInput->BindAction(HunterFireWeaponAction, ETriggerEvent::Started, HunterPlayer, &AHunterPlayer::StartFiringWeapon);
				EnhancedInput->BindAction(HunterFireWeaponAction, ETriggerEvent::Completed, HunterPlayer, &AHunterPlayer::StopFiringWeapon);

				UKismetSystemLibrary::PrintString(GetWorld(), GetPawn()->GetName(), true, true, FLinearColor::Black, 10);

			}
			//Setting The Pre Match MappingContext For Until The Prop Hide In Game
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				//Setting Up The Mapping Context
				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(HunterPreMatchMappingContext, 0);
			}
		}
	}
}

void ACommonPlayerController::BindPropPlayerInputs()   //Prop Input Bindings
{
	if (IsLocalController())
	{
		SetInputMode(FInputModeGameOnly());

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			//Setting Up The Mapping Context
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PropMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInput = Cast <UEnhancedInputComponent>(this->InputComponent))
		{
			if (APropPlayer* PropPlayer = Cast<APropPlayer>(GetPawn()))
			{
				//Binding InputAction And The Correspoding Functions
				EnhancedInput->BindAction(PropMoveAction, ETriggerEvent::Triggered, PropPlayer, &APropPlayer::MoveFunction);
				EnhancedInput->BindAction(PropLookAction, ETriggerEvent::Triggered, PropPlayer, &APropPlayer::LookFunction);

				EnhancedInput->BindAction(PropJumpAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::StartJumpFunction);
				EnhancedInput->BindAction(PropJumpAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::StopJumpFunction);

				EnhancedInput->BindAction(PropMorphAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::MorphObjectFunction);

				EnhancedInput->BindAction(PropCloneAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::PropCloneFunction);

				EnhancedInput->BindAction(PropSmokeBombAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::SmokeBombFunction);

			}
		}

	}
}
