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

		if (RandomMovementToTargets) 
		{
		
			PlatformstartRandomMovement(TargetPoint1, TargetPoint2, TargetPoint3, RandomMovementToTargets);
		
		}
		else
		{

			PlatformStartMovement(TargetPoint1, TargetPoint2);
		}

		

		

	}
}

void AMovingPlatform::BeginPlay()
{

	Super::BeginPlay();

	if (!ensure(TargetPoint1) || !ensure(TargetPoint2)) 
	{
	
		return;
	
	}

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






bool AMovingPlatform::PlatformstartRandomMovement(ATargetPointBase* TargetPointA, ATargetPointBase* TargetPointB, ATargetPointBase* TargetPointC, bool bHasRandomMovement)
{

	if (!ensure(TargetPointA) || !ensure(TargetPointB) || !ensure(TargetPointC))
	{
		return false;
	}
	bool bSuccess = false;

	if (bHasRandomMovement)
	{
		if (!bIsReaching) 
		{

			iRandomTargetPointNumber = FMath::RandRange(1, 3);

			switch (iRandomTargetPointNumber)
			{
			case 1:
				PlatformReaching = TargetPointA;
				break;
			case 2:
				PlatformReaching = TargetPointB;
				break;
			case 3:
				PlatformReaching = TargetPointC;
				break;
			}

			bIsReaching = true;

		}
		else {

			if (PlatformReaching != LastPlatformReached)
			{

				PlatformGo(PlatformReaching);


				if ( PlatformGo(PlatformReaching) )
				{

					LastPlatformReached = PlatformReaching;
					bSuccess = true;
					bIsReaching = false;

				}

			}
			else
			{
				bSuccess = false;
				bIsReaching = false;
			}

			
		}
	}
	return bSuccess;
}

void AMovingPlatform::PlatformStartMovement(ATargetPointBase* TargetPointA, ATargetPointBase* TargetPointB)
{

	if (!ensure(TargetPointA) || !ensure(TargetPointB)) { return; }



	if (!bHasReachedA)
	{
		PlatformGo(TargetPointA);

		if (PlatformGo(TargetPointA))
		{

			bHasReachedA = true;

			bHasReachedB = false;

		}

	}
	else if (!bHasReachedB)
	{
		PlatformGo(TargetPointB);

		if (PlatformGo(TargetPointB))
		{

			bHasReachedB = true;

			bHasReachedA = false;

		}


	}



	
}

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


