// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Others/Create Widget/CreateWidgetAbstract.h"

class UCharacterPreMatchWidget;

/**
 * 
 */
class SEEKANDSNEAK_3D_API CreatePreMatchWidget : public CreateWidgetAbstract
{
public:
	CreatePreMatchWidget();
	~CreatePreMatchWidget();

private:

	/*Abstract Function*/
	void Begin(APlayerController* PlayerController, ECharacterType CharacterType)override;
	void End()override;

protected:

	//For Storing Widget Ref
	UCharacterPreMatchWidget* PreMatchWidget;

	//Widget Class For Creating
	TSubclassOf<class UCharacterPreMatchWidget>PreMatchWidgetClass;
};
