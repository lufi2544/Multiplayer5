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
		:fName("Name_None")


	{}

	//The Platform Speed
	UPROPERTY(EditDefaultsOnly, meta = (GetByRef)  , meta =(DisplayName = "PlatformName")  , Category = "PlatformBase")
		FName fName;

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


	//Targets that the platform will move between
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "PlatformBase")
		TArray<ATargetPointBase*>TargetsToReach;

	// If true The Platform will move between the given Targets with a random movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase")
		bool RandomMovementToTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase")
		bool CanMove;

	UPROPERTY(EditAnywhere , Category = "PlatformBase" , meta = (ClampMin = -2.f) ,  meta = (ClampMax = 2.f) , meta = (DisplayName = "Speed"))
	float fSpeed = 1.f;

	//Targets that the platform will move between when we push a button
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase")
		TArray<ATargetPointBase*>TargetsToReachOnButonPush;

	UPROPERTY(EditAnywhere , Category = "PlatformBase")
		bool IsButtonActive;


	//GETTERS
	UFUNCTION(BlueprintPure , Category = "PlatformBase")
	FName GetPlatformName();





	//FUNCTIONS

	/*Change the targets to reach by the platform based on a button being pushed*/
	UFUNCTION(BlueprintCallable , category ="PlatformBase")
	bool OnControlButtonPushed(bool bIsButtonactive);



	bool PlatformGo(ATargetPointBase* TargetPoint);

	bool PlatformMoveToTatgets(TArray<ATargetPointBase*> Targets, bool bHasRandomMovement);








	//VARIABLES


	bool bIsReaching = false;

	int32 ArrayCounter = 0;

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
		FName fName_DEPRECATED;

#endif






};
