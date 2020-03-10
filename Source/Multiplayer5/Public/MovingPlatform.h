// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

//FWD Delcarations

class ATargetPointBase;

USTRUCT(BlueprintType)
struct FMySparseClassData
{
	GENERATED_BODY();


	FMySparseClassData()
		:fSpeed(1.f)


	{}

	//The Platform Speed
	UPROPERTY(EditDefaultsOnly, meta = (GetByRef)  , meta =(DisplayName = "Speed") ,meta = (ClampMin = -3) , meta = (ClampMax = 3) , Category = "PlatformBase")
		float fSpeed;

};

/**
 * 
 */
UCLASS(BlueprintType, SparseClassDataTypes = MySparseClassData)
class MULTIPLAYER5_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	//PROPERTIES
	UPROPERTY(EditAnywhere , BlueprintReadWrite,  Category = "PlatformBase")
		ATargetPointBase* TargetPoint1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "PlatformBase")
		ATargetPointBase* TargetPoint2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase")
		ATargetPointBase* TargetPoint3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase")
		bool RandomMovementToTargets;






	//GETTERS
	UFUNCTION(BlueprintPure , Category = "PlatformBase")
	float GetPlatformSpeed();





	//FUNCTIONS

	void PlatformStartMovement(ATargetPointBase* TargetPointA, ATargetPointBase* TargetPointB);

	bool PlatformstartRandomMovement(ATargetPointBase* TargetA, ATargetPointBase* TargetB, ATargetPointBase* TargetC, bool bHasRandomMovement);

	bool PlatformGo(ATargetPointBase* TargetPoint);








	//VARIABLES

	bool bHasReachedA = false;

	bool bHasReachedB = false;


	bool bIsReaching = false;

	int32 iRandomTargetPointNumber;

	ATargetPointBase* PlatformReaching;
	ATargetPointBase* LastPlatformReached;
	


	//DELEGATES






	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;





#if WITH_EDITOR



public:

	virtual void MoveDataToSparseClassDataStruct() const override;


#endif
	

#if WITH_EDITORONLY_DATA

private:

	//The Platform Speed
	UPROPERTY()
		float fSpeed_DEPRECATED;

#endif






};
