// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interface/Player/HunterPlayerInterface.h"
#include "HunterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UHunterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:

	void NativeInitializeAnimation()override;
    void NativeUpdateAnimation(float DeltaTime)override;

	UPROPERTY()
	TScriptInterface<IHunterPlayerInterface>PlayerInterface;

protected:

	ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	float Direction;
	UPROPERTY(BlueprintReadOnly)
	float Pitch;

	UPROPERTY(BlueprintReadOnly)
	bool CanPlayerRun;

	FVector Velocity;
	FRotator AimRotation;
};
