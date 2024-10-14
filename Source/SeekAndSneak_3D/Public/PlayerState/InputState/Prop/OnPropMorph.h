// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/InputState/InputStateAbstract.h"
#include "Interface/Player/PropPlayerInterface.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

/**
 * 
 */
class SEEKANDSNEAK_3D_API OnPropMorph : public InputStateAbstract
{
public:
	OnPropMorph();
	~OnPropMorph();

	void Begin(ACharacter* Player)override;
	void End(ACharacter* Player)override;

private:

	UNiagaraSystem* NiagaraSystemOnMorph;
	FVector SystemLocation;

	FBoxSphereBounds MeshBounds;

	//Caching The Interface
	TScriptInterface<IPropPlayerInterface>PlayerInterface;

	//Trace Variables
	bool IsTraceHit;
	float TraceRadius;
	FVector StartPoint;
	FVector EndPoint;
	FHitResult TraceHitResult;
	FCollisionQueryParams TraceCollisionParams;

	//Helper Function For Breaking Down The Code

	/*Casting Line Trace*/
	void CastLineTrace(ACharacter* Player);
	/*Setting New Mesh To Player*/
	void SetNewMesh(ACharacter* Player , FHitResult& HitResult);

};
