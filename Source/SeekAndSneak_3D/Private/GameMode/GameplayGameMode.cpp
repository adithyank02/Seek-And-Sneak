// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameplayGameMode.h"
#include "GameFramework/GameState.h"

#include "HunterPlayer/HunterPlayer.h"
#include "PropPlayer/PropPlayer.h"

#include "Interface/Controller/ControllerInterface.h"
#include "Others/EnumClass/CharacterTypeEnum.h"

#include "Interface/GameState/GameStateInterface.h"


#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

/*------------InterFunction--------------*/
void AGameplayGameMode::PreMatchTimerEnded()
{
	AGameState* PropHuntGameState = GetGameState<AGameState>();
	if (IGameStateInterface* GameStateInterface = Cast<IGameStateInterface>(PropHuntGameState))
	{
		GameStateInterface->StartInMatchTimer(InMatchTimeInSec); 
	
		//Calling To Create The InMatch UI Widget
	 for (TScriptInterface<IControllerInterface>& Interface : ControllerInterfaceArray)
	 {
	 	Interface->InitializeInMatchUI();
	 }

	 //Gving The Team Info Into Game State
	 GameStateInterface->SetTeamInfo(JoinedPlayerController.Num() - PropPlayerControllerArray.Num(), PropPlayerControllerArray.Num());
	}
	
}

void AGameplayGameMode::OnMatchEnded()
{
	if (!bMatchEnded)
	{
		for (TScriptInterface<IControllerInterface>& Interface : ControllerInterfaceArray)
		{
			Interface->CallEndMatch(ECharacterType::PropCharacter);
		}
	}
}

void AGameplayGameMode::OnPropPlayerCaught(AController* PropController)
{

	//Informing The GameState To Update On Prop Team Info
	if (IGameStateInterface* GameStateInterface = Cast<IGameStateInterface>(GetGameState<AGameState>()))
	{
		GameStateInterface->UpdatePropTeamInfo();
	}

	//Finding The Controller Responsible For Caught Player
	for (auto Cntrl : PropPlayerControllerArray)
	{
		if (Cntrl == PropController)
		{
			PropPlayerControllerArray.RemoveSingle(Cntrl);
			break;
		}
	}

	if (!bMatchEnded)
	{
		//Informing To EndGame When All Prop Get Caught
		if (PropPlayerControllerArray.Num() == 0)
		{
			for (TScriptInterface<IControllerInterface>& Interface : ControllerInterfaceArray)
			{
				//Hunter Won The Game
				Interface->CallEndMatch(ECharacterType::HunterCharacter);
				bMatchEnded = true;
			}
		}
	}
}


void AGameplayGameMode::OnPostLogin(AController* NewController)
{
	Super::OnPostLogin(NewController);

	//Storing The Player For Implementing Team Split Logic
	JoinedPlayerController.Add(NewController);
}

void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		//Adding A Delay To Ensure All Player Join And Stored
		FTimerHandle SpawnPropCharacterTimer;
		GetWorld()->GetTimerManager().SetTimer(SpawnPropCharacterTimer, this, &AGameplayGameMode::SetUpPropCharacter, FirstDeley);
	}
}

void AGameplayGameMode::SetUpPropCharacter()
{
	//Only Using Copy Of Controllers
	TArray<AController*>CopyArray = JoinedPlayerController;

	int TotalNumberOfPlayer = JoinedPlayerController.Num();

	//Getting The Count To Spawn -- PropCount < Hunter Count
	int PropCharacterSpawnCount = TotalNumberOfPlayer / 2 ;	

	int PropSpawnTransformIndex = 0;

	//Setting The Character To Spawn Any Way
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int Itr = 1; Itr <= PropCharacterSpawnCount; Itr++)
	{
		//Getting Random Index For Selecting Random Player
		int Index = GetRandomIndex(0, TotalNumberOfPlayer - 1);

		//int Index = 0;

		if (IControllerInterface* Interface = Cast <IControllerInterface>(CopyArray[Index]))
		{
			//Storing Controller Interface
			StoreControllerInterface(CopyArray[Index], Interface);

			if (ACharacter* PlayerCharacter = GetWorld()->SpawnActor<ACharacter>(PropCharacterClass, PropCharacterSpawnTranform[PropSpawnTransformIndex], SpawnParams))
			{
				CopyArray[Index]->Possess(PlayerCharacter);
				//Setting Input Binding For Prop Character
				Interface->SetControllerInputBinding(ECharacterType::PropCharacter);

				//Storing The Prop Controllers
				PropPlayerControllerArray.Add(CopyArray[Index]);

				//Removing For Not To Spawn Same Player Twice
				CopyArray.RemoveAt(Index);
				TotalNumberOfPlayer--;
				//Next Spawn Index
				PropSpawnTransformIndex++;

			  
			}
		}
	}
	SetupHunterCharacter(CopyArray);
	
}

void AGameplayGameMode::SetupHunterCharacter(TArray<AController*> RemainingController)
{
	int HunterSpawnTransformIndex = 0; 

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (auto PController : RemainingController)
	{
		if (IControllerInterface* Interface = Cast <IControllerInterface>(PController))
		{
			//Storing Controller Interface
			StoreControllerInterface(PController, Interface);

			if (ACharacter* PlayerCharacter = GetWorld()->SpawnActor<ACharacter>(HunterCharacterClass, HunterCharacterSpawnTranform[HunterSpawnTransformIndex], SpawnParams))
			{
				PController->Possess(PlayerCharacter);
				//Setting Input Binding For Hunter Character
				Interface->SetControllerInputBinding(ECharacterType::HunterCharacter);

				//Next Spawn Index
				HunterSpawnTransformIndex++;
			}
		}
	}
	AGameState* PropHuntGameState = GetGameState<AGameState>();
	if (IGameStateInterface* GameStateInterface = Cast<IGameStateInterface>(PropHuntGameState))
	{
		GameStateInterface->StartPreMatchTimer(PreMatchTimeInSec);
	}
	CallPreMatchWidget();
}

void AGameplayGameMode::CallPreMatchWidget()
{
	for (TScriptInterface<IControllerInterface>& Interface : ControllerInterfaceArray)
	{
		Interface->InitializePreMatchUI();
	}
}

// ----------------Helper Functon ------------------- // 

void AGameplayGameMode::StoreControllerInterface(AController* PlayerController, IControllerInterface* InterfaceRef)
{
	TScriptInterface<IControllerInterface>Interface;
	Interface.SetObject(PlayerController);
	Interface.SetInterface(InterfaceRef);
	ControllerInterfaceArray.Add(Interface);
}


int AGameplayGameMode::GetRandomIndex(int Min, int Max)
{
	return FMath::RandRange(Min,Max);
}
