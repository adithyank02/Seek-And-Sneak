// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PropProximityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPropProximityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SEEKANDSNEAK_3D_API IPropProximityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Start(ACharacter* Player) = 0;

};
