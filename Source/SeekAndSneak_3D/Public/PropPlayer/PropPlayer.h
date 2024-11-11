// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "PlayerState/MotionState/MotionStateAbstract.h"
#include "PlayerState/InputState/InputStateAbstract.h"

#include "Interface/Player/PropPlayerInterface.h"

#include "Feature/Prop/ScanningProps/ScanProps.h"

#include "NiagaraSystem.h"

#include "PropPlayer.generated.h"



DECLARE_DELEGATE(FOnPlayerMeshChange);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropGetDamaged, float);

UCLASS()
class SEEKANDSNEAK_3D_API APropPlayer : public ACharacter , public IPropPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APropPlayer();
	

	void SetPlayerMesh(UStaticMesh* NewMesh) override; 
	UStaticMesh* GetPlayerMesh() override;
	void SetCapsuleSize(float Radius, float Height) override;
	void PlayerGetDamaged(float DamageCaused)override;
	TArray<UStaticMesh*>GetMorphableMeshArray()override;


	APropPlayer* GetPropPlayerRef()override;

	FOnPlayerMeshChange PropMeshChanged;

	FOnPropGetDamaged PropPlayerDamaged;

private:

	//Smart Pointer For Handle The Memory Management
	TMap<MotionEnum,TUniquePtr<MotionStateAbstract>>MotinStateLibrary;

	TMap<InputStateEnum,TUniquePtr<InputStateAbstract>>InputStateLibrary;

	TUniquePtr<ScanProps>ScanPropClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* TPSCamera;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;

	//Prop Character Health
	float PropHealth;

	bool bMorphMeshArrayPassed;

	UPROPERTY(EditDefaultsOnly)
	TArray<UStaticMesh*>MorphMeshArray;

private:

	FTimerHandle ScanningPropsTimer;

	void StartScanningProps();

	void ScanningPropsForMorphing();
 
	const int ScanningPropInitialTimer= 5; 

	void SetScanningProp();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Movement Function
	void MoveFunction(const FInputActionValue& InputValue);
	void LookFunction(const FInputActionValue& InputValue);

	void StartJumpFunction();
	void StopJumpFunction();


//------------------------------------------------------>>>>> PropMorph 
	FTimerHandle MorphCoolDownTimer;

	float MorphCoolDownTime;

	UPROPERTY(EditDefaultsOnly, Category = "Prop Player")
	float MorphMaxCoolDownTime;

	void MorphObjectFunction();
	void UpdateMorphCoolDownTime();     /*For Counting The CoolDown Timer*/

	UFUNCTION(Server,Reliable)
	void MorphObject_Server();

	UFUNCTION(NetMulticast,Reliable)
	void MorphObject_Multicast();
//------------------------------------------------------->>>>>

//------------------------------------------------------->>>>> Clone PropMesh

	UPROPERTY(EditDefaultsOnly)
	float TotalCloneCount;
	float ClonedCount;

	void PropCloneFunction();

	UFUNCTION(Server,Reliable)
	void PropClone_Server();

	UFUNCTION(NetMulticast,Reliable)
	void PropClone_Multicast();

//-------------------------------------------------------->>>>> Clone PropMesh

//--------------------------------------------------------->>>>> Smoke Bomb

	UNiagaraSystem* SmokeBombParticle;
	UNiagaraSystem* PlayerCaughtParticle;

	void SmokeBombFunction();

	UFUNCTION(Server , Reliable)
	void SmokeBombOnServer();

	UFUNCTION(NetMulticast , Reliable)
	void SmokeBombOnMulticast();

//------------------------------------------------------->>>>> Smoke Bomb

	void OnPropPlayerCaught();

	UFUNCTION(Server,Reliable)
	void OnPlayerCaught_Server(AController* PlayerController);

	UFUNCTION(NetMulticast,Reliable)
	void OnPlayerCaught_Multicast(AController* PlayerController);


};
