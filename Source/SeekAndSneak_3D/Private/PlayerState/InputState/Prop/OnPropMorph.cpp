// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/InputState/Prop/OnPropMorph.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

OnPropMorph::OnPropMorph()
{
	TraceRadius = 150.0f;

	NiagaraSystemOnMorph = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/NiagraParticle/NS_PoofSmoke.NS_PoofSmoke"));
}

OnPropMorph::~OnPropMorph()
{
	PlayerInterface = nullptr;
}

void OnPropMorph::Begin(ACharacter* Player)
{
	/* It Only Run Once*/
	if (PlayerInterface == nullptr)
	{
		if (IPropPlayerInterface* Interface = Cast<IPropPlayerInterface>(Player))
		{
			//Storing Player And Interface
			PlayerInterface.SetObject(Cast<UObject>(Player));
			PlayerInterface.SetInterface(Interface);
		}
		//Since The If Only Works At Once -- Setting The Self Ignorance
		TraceCollisionParams.AddIgnoredActor(Player);

		if (MorphableMeshArray.IsEmpty())
		{
			MorphableMeshArray = PlayerInterface->GetMorphableMeshArray();
		}		
	}
	CastLineTrace(Player);
	
}

void OnPropMorph::End(ACharacter* Player)
{

}

/*-----Helper Functions-----*/

void OnPropMorph::CastLineTrace(ACharacter* Player)
{
	StartPoint = Player->GetActorLocation();
	/*Setting A Little High So Colliding With Ground Floor Avoided*/
	//StartPoint.Z += 20.0f;
	EndPoint = StartPoint;

	IsTraceHit = Player->GetWorld()->SweepSingleByChannel(TraceHitResult, StartPoint, EndPoint, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(TraceRadius), TraceCollisionParams);
	
	DrawDebugSphere(Player->GetWorld(), EndPoint, TraceRadius, 12, IsTraceHit ? FColor::Red : FColor::Green, false, 5);

	if (IsTraceHit && TraceHitResult.GetActor()->IsA(AStaticMeshActor::StaticClass()))
	{
		/*Casting To StaticMeshComponent For Retreving The Mesh*/
		if (UStaticMeshComponent* StaticMeshComponent = Cast <UStaticMeshComponent>(TraceHitResult.GetComponent()))
		{
			UStaticMesh* HitMesh = StaticMeshComponent->GetStaticMesh();
			for (auto AvailableMesh : MorphableMeshArray)
			{
				if (HitMesh == AvailableMesh)
				{
					SetNewMesh(Player,HitMesh);
					return;
				}
			}
		}
	}
}

void OnPropMorph::SetNewMesh(ACharacter* Player,UStaticMesh* MorphMesh)
{
	PlayerInterface->SetPlayerMesh(MorphMesh);

	SystemLocation = Player->GetActorLocation();

	if (NiagaraSystemOnMorph)UNiagaraFunctionLibrary::SpawnSystemAtLocation(Player->GetWorld(), NiagaraSystemOnMorph, SystemLocation,
	FRotator(0.0f), FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);

	//Getting The Collision Bounds And Setting To Prop Collision
	MeshBounds = MorphMesh->GetBounds();
	float CapsuleRadius = MeshBounds.BoxExtent.X;
	float CapsuleHeight = MeshBounds.BoxExtent.Z;
	PlayerInterface->SetCapsuleSize(CapsuleRadius, CapsuleHeight);

	return;
		
}
