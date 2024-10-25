// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameplayGameMode.h"

#include "PropPlayer/PropPlayer.h"
#include "PlayerController/PropPlayerController.h"


#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

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
		GetWorld()->GetTimerManager().SetTimer(SpawnPropCharacterTimer, this, &AGameplayGameMode::SetUpPropCharacter, 2);
	}
}

void AGameplayGameMode::SetUpPropCharacter()
{
	//Only Using Copy Of Controllers
	TArray<AController*>CopyArray = JoinedPlayerController;

	int TotalNumberOfPlayer = JoinedPlayerController.Num();

	//Getting The Count To Spawn -- PropCount < Hunter Count
	int PropCharacterSpawnCount = TotalNumberOfPlayer / 2 ;

	int SpawnTranformIndex = 0;

	//Setting The Character To Spawn Any Way
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int Itr = 1; Itr <= PropCharacterSpawnCount; Itr++)
	{
		//Getting Random Index For Selecting Random Player
		int Index = GetRandomIndex(0, TotalNumberOfPlayer-1);

		if (APropPlayerController* PropController = Cast <APropPlayerController>(CopyArray[Index]))
		{
			if (APropPlayer* PropCharacter = GetWorld()->SpawnActor<APropPlayer>(PropCharacterClass, PropCharacterSpawnTranform[Index], SpawnParams))
			{
				PropController->Possess(PropCharacter);
				PropController->Client_SetInputBinding();

				//Removing For Not To Spawn Same Player Twice
				CopyArray.RemoveAt(Index);
				TotalNumberOfPlayer--;
				//Next Spawn Index
				SpawnTranformIndex++;
			}
		}
	}

}

int AGameplayGameMode::GetRandomIndex(int Min, int Max)
{
	return FMath::RandRange(Min,Max);
}
