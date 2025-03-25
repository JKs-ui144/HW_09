// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BullsAndCowsLib.generated.h"

USTRUCT(BlueprintType)
struct FBallCount
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, Category = "BallManager")
	int32 StrikeCount;
	UPROPERTY(BlueprintReadWrite, Category = "BallManager")
	int32 BallCount;

	UPROPERTY(BlueprintReadWrite,Category = "BallManager")
	int32 TurnCount;
	UPROPERTY(BlueprintReadWrite, Category = "BallManager")
	FString RandNum;

	UPROPERTY(BlueprintReadWrite, Category = "BallManager")
	bool bIsHost;

	FBallCount()
		: StrikeCount(0),
		BallCount(0),
		TurnCount(0),
		RandNum(""),
		bIsHost(true)
	{
	}
};
/**
 * 
 */
UCLASS()
class SAMPLECHAT_API UBullsAndCowsLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GenerateRandNum")
	static FString MakeRandRange(FBallCount BC);
	
	UFUNCTION(BlueprintCallable, Category = "GenerateRandNum")
	static void CompareNum(FString PlayerNum, FString ServerNum, UPARAM(ref) FBallCount& BC);

	UFUNCTION(BlueprintCallable, Category = "GenerateRandNum")
	static void resetCount(int32 Strike, int32 Ball, int32 Turn, UPARAM(ref) FBallCount& BC);

	UFUNCTION(BlueprintCallable, Category = "GenerateRandNum")
	static bool ChatCheck(FString PlayerNum);

	UFUNCTION(BlueprintCallable, Category = "GenerateRandNum")
	static int32 SetbIstHost(FString PlayerMsg);
protected:
	const FString GuestNum;

	const FString HostNum;

};
