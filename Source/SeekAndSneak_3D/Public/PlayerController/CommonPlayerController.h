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

	TMap<EWidgetType,TUniquePtr<CreateWidgetAbstract>>WidgetLibrary;

public:

	UFUNCTION(Client,Reliable)
	void SetClientInputBinding(ECharacterType CharacterType);


private:

/*---------------------------------Hunter Player Controller Inputs---------------------------------------- */

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* HunterPlayerMappingContext;

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
	UInputMappingContext* PropPlayerMappingContext;

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
