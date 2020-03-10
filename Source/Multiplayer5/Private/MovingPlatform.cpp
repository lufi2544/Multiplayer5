// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Components/StaticMeshComponent.h"
#include "TargetPointBase.h"


AMovingPlatform::AMovingPlatform() 
{

	PrimaryActorTick.bCanEverTick = true;

	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	

}

void AMovingPlatform::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (HasAuthority())
	{

		
			PlatformMoveToTatgets(TargetsToReach, RandomMovementToTargets);
		
	}
}

void AMovingPlatform::BeginPlay()
{

	Super::BeginPlay();



	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}



}

//GETTERS





float AMovingPlatform::GetPlatformSpeed()
{
	return GetfSpeed();
}








//FUNCTIONS



bool AMovingPlatform::PlatformGo(ATargetPointBase* TargetPointA)
{
	bool bHasReached = false;

	FVector vCurrentActorLocation = GetActorLocation();

	FVector vTarget1Location = TargetPointA->GetActorLocation();

	FVector nvDistanceToTargetPointA = (vTarget1Location - vCurrentActorLocation).GetSafeNormal();

	FVector vLocationToReach = nvDistanceToTargetPointA * vTarget1Location;




	SetActorLocation(vCurrentActorLocation + nvDistanceToTargetPointA * GetfSpeed());

	if (GetActorLocation().Equals(vTarget1Location, 2.f))
	{

		bHasReached = true;

	}


	return bHasReached;
}




bool AMovingPlatform::PlatformMoveToTatgets(TArray<ATargetPointBase*> Targets, bool bHasRandomMovement)
{
	bool bSuccess = false;


	if (Targets.Num() > 0) 
	{
	
		if (!bHasRandomMovement) 
		{
		
			if (!bIsReaching) 
			{
				if (!ensure(Targets[ArrayCounter])) { return false; }

				PlatformReaching = Targets[ArrayCounter];

				bIsReaching = true;
			
			}
			else
			{
				PlatformGo(PlatformReaching);

				if (PlatformGo(PlatformReaching))
				{
					bSuccess = true;
					bIsReaching = false;
					ArrayCounter++;

					if (ArrayCounter == Targets.Num()) 
					{
					
						ArrayCounter = 0;

					}


				}

				
			}
		
		
		}
		else
		{

			if (!bIsReaching) 
			{

				ArrayCounter = FMath::RandRange(0, Targets.Num()-1);

				if (!ensure(Targets[ArrayCounter])) { return false; }
				
				PlatformReaching = Targets[ArrayCounter];
				
				bIsReaching = true;
			}
			else
			{

				if (PlatformReaching != LastPlatformReached) 
				{
					PlatformGo(PlatformReaching);

					if (PlatformGo(PlatformReaching)) 
					{
						LastPlatformReached = PlatformReaching;
						bIsReaching = false;
						bSuccess = true;

					}
				
				}
				else 
				{
					bIsReaching = false;
					bSuccess = false;
				
				}


			}



		}
		

	}
	else
	{

		bSuccess = false;
	}


	return bSuccess;
}





//SPARSECLASSDATA






#if WITH_EDITOR

	void AMovingPlatform::MoveDataToSparseClassDataStruct() const 
	{
		UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());
		if (BPClass == nullptr || BPClass->bIsSparseClassDataSerializable == true)
		{
			return;
		}

		Super::MoveDataToSparseClassDataStruct();
	
	
	
	

#if WITH_EDITORONLY_DATA
	// Unreal Header Tool (UHT) will create GetMySparseClassData automatically.
	FMySparseClassData* SparseClass = GetMySparseClassData();

	// Modify these lines to include all Sparse Class Data properties.
	SparseClass->fSpeed = fSpeed_DEPRECATED;
	

#endif
}

#endif // WITH_EDITOR


