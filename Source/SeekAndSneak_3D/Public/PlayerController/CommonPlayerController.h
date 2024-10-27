// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/Controller/ControllerInterface.h"

#include "Others/Create Widget/CreateWidgetAbstract.h"

#include "InputMappingContext.h"
#include "InputAction.h"

#include "Others/EnumClass/CharacterTypeEnum.h"
#include "CommonPlayerController.generated.h"



/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API ACommonPlayerController : public APlayerController , public IControllerInterface
{
	GENERATED_BODY()

protected:

	void SetControllerInputBinding(ECharacterType CharacterType)override;
	void InitializePreMatchUI()override;
	void InitializeInMatchUI() override;
	ECharacterType GetCharacterType()override;

	ACommonPlayerController();

private:

	void BeginPlay()override;

	ECharacterType OwnerCharacterType;

	void BindHunterPlayerInputs();
	void BindPropPlayerInputs();

	void RemoveUnwantedRef();

	void RemoveHunterInputRef();
	void RemovePropInputRef();

    UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCharacterPreMatchWidget>HunterPreMatchWidgetClass;

	//Mapping Responsible For Storing Widget Class 
	TMap<EWidgetType,TUniquePtr<CreateWidgetAbstract>>WidgetLibrary;

public:

	//Binding Input In All Clients
	UFUNCTION(Client,Reliable)
	void SetClientInputBinding(ECharacterType CharacterType);

protected:

	//Client Function For Setting PreMatch Widget
	UFUNCTION(Client,Reliable)
	void SetClientPreMatchWidget();

	//Clinet Function For Setting InMatch Widget
	UFUNCTION(Client,Reliable)
	void SetClientInMatchWidget();


private:

	void SetHunterInMatchMappingContext();


/*---------------------------------Hunter Player Controller Inputs---------------------------------------- */


	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* HunterPreMatchMappingContext;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* HunterInMatchMappingContext;

	//InputAction For Ground Movement --WSAD
	UPROPERTY(EditDefaultsOnly)
	UInputAction* HunterJogAction;

	//InputAction For Look Movement --MouseXY
	UPROPERTY(EditDefaultsOnly)
	UInputAction* HunterLookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HunterSprintAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HunterFireWeaponAction;


	/*---------------------------------Prop Player Controller Inputs---------------------------------------- */
	
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* PropMappingContext;

	//InputAction For Ground Movement --WSAD
	UPROPERTY(EditDefaultsOnly)
	UInputAction* PropMoveAction;

	//InputAction For Look Movement --MouseXY
	UPROPERTY(EditDefaultsOnly)
	UInputAction* PropLookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* PropJumpAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* PropMorphAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* PropCloneAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* PropSmokeBombAction;
};