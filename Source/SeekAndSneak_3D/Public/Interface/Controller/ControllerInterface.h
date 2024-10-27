// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Others/EnumClass/CharacterTypeEnum.h"
#include "ControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SEEKANDSNEAK_3D_API IControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetControllerInputBinding(ECharacterType CharacterType) = 0; 
	virtual void InitializePreMatchUI() = 0; 
	virtual ECharacterType GetCharacterType() = 0; 
};
