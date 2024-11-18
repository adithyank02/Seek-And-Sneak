// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class ECharacterWidgetUpdate : uint8
{
	//Prop
	OnMorphUpdate,
	OnCloneUpdate,
	OnSmokeBombUpdate,

	//Hunter
	OnGrenadeUpdate
};