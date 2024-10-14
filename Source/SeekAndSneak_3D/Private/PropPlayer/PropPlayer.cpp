// Fill out your copyright notice in the Description page of Project Settings.


#include "PropPlayer/PropPlayer.h"
#include "Components/CapsuleComponent.h"

#include "PlayerState/MotionState/PlayerMove/PlayerMove.h"
#include "PlayerState/MotionState/PlayerLook/PlayerLook.h"

#include "PlayerState/InputState/Prop/OnPropMorph.h"
#include "PlayerState/InputState/Prop/OnPropClone.h"

#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

#include "NiagaraFunctionLibrary.h"


void APropPlayer::SetPlayerMesh(UStaticMesh* NewMesh)
{
	PlayerMesh->SetStaticMesh(NewMesh);
}


UStaticMesh* APropPlayer::GetPlayerMesh()
{
	return PlayerMesh->GetStaticMesh();
}
//Re sizing The Prop Collsion Component
void APropPlayer::SetCapsuleSize(float Radius, float Height)
{
	GetCapsuleComponent()->SetCapsuleRadius(Radius);
	GetCapsuleComponent()->SetCapsuleHalfHeight(Height);
}

// Sets default values
APropPlayer::APropPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	TPSCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actual Mesh"));
	PlayerMesh->SetupAttachment(GetMesh());
	
	MotinStateLibrary.Add(MotionEnum::OnMove,MakeUnique<PlayerMove>());
	MotinStateLibrary.Add(MotionEnum::OnLook,MakeUnique<PlayerLook>());

	InputStateLibrary.Add(InputStateEnum::OnPropMorph,MakeUnique<OnPropMorph>());
	InputStateLibrary.Add(InputStateEnum::OnPropClone, MakeUnique<OnPropClone>());

	MorphMaxCoolDownTime = 15.0f;
	TotalCloneCount = 5.0f;

	//Load The Bomb Particle
	SmokeBombParticle = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/NiagraParticle/NS_SmokeBomb.NS_SmokeBomb"));

}


// Called when the game starts or when spawned
void APropPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	if (SmokeBombParticle)UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Good"));
	else UKismetSystemLibrary::PrintString(GetWorld(), TEXT("H"), true, true, FLinearColor::Red);


}

// Called every frame
void APropPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APropPlayer::MoveFunction(const FInputActionValue& InputValue)
{
	MotinStateLibrary[MotionEnum::OnMove]->Begin(this, InputValue);
}

void APropPlayer::LookFunction(const FInputActionValue& InputValue)
{
	MotinStateLibrary[MotionEnum::OnLook]->Begin(this, InputValue);
}

void APropPlayer::StartJumpFunction()
{
	Jump();
}

void APropPlayer::StopJumpFunction()
{
	StopJumping();
}



//---------------------------------------------------------------------------------------------->>>>> ( Prop Morph Function )
void APropPlayer::MorphObjectFunction()
{
	if (MorphCoolDownTime == 0)
	{
		if (HasAuthority())
		{
			MorphObject_Multicast();
		}
		else
		{
			MorphObject_Server();
		}
		MorphCoolDownTime = MorphMaxCoolDownTime;
		ClonedCount = 0;
		GetWorld()->GetTimerManager().SetTimer(MorphCoolDownTimer, this, &APropPlayer::UpdateMorphCoolDownTime, 1, true);
	}
}

void APropPlayer::MorphObject_Server_Implementation()
{
	MorphObject_Multicast();
}

void APropPlayer::MorphObject_Multicast_Implementation()
{
	InputStateLibrary[InputStateEnum::OnPropMorph]->Begin(this);
}

void APropPlayer::UpdateMorphCoolDownTime()
{
	MorphCoolDownTime--;
	if (MorphCoolDownTime == 0)GetWorld()->GetTimerManager().ClearTimer(MorphCoolDownTimer);
}

//----------------------------------------------------------------------------------------------->>>>>

//----------------------------------------------------------------------------------------------->>>>> ( Prop Clone Function )
void APropPlayer::PropCloneFunction()
{
	if (ClonedCount < TotalCloneCount)
	{
		if (HasAuthority())
		{
			PropClone_Multicast();
		}
		else
		{
			PropClone_Server();
		}
		ClonedCount++;
	}
}

void APropPlayer::PropClone_Server_Implementation()
{
	PropClone_Multicast();
}
void APropPlayer::PropClone_Multicast_Implementation()
{
	InputStateLibrary[InputStateEnum::OnPropClone]->Begin(this);
}
//---------------------------------------------------------------------------------------------->>>>> ( Prop Clone Function )

//---------------------------------------------------------------------------------------------->>>>> ( Prop Smoke Bomb )

void APropPlayer::SmokeBombFunction()
{
	if (HasAuthority())
	{
		SmokeBombOnMulticast();
	}
	else
	{
		SmokeBombOnServer();
	}
}

void APropPlayer::SmokeBombOnServer_Implementation()
{
	SmokeBombOnMulticast();
}

void APropPlayer::SmokeBombOnMulticast_Implementation()
{
	if (SmokeBombParticle)UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SmokeBombParticle, GetActorLocation(), 
		                  FRotator(0.0f), FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);
}
