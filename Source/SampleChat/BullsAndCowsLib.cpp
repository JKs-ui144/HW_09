// Fill out your copyright notice in the Description page of Project Settings.  

#include "BullsAndCowsLib.h"  
#include "Kismet/KismetSystemLibrary.h"


void UBullsAndCowsLib::resetCount(int32 Strike, int32 Ball, int32 Turn, UPARAM(ref) FBallCount& BC)
{
	BC.BallCount = Ball;
	BC.StrikeCount = Strike;
	BC.TurnCount = Turn;
}

bool UBullsAndCowsLib::ChatCheck(FString PlayerNum)
{
	FString Player;
	// 플레이어가 입력한 숫자를 ':' 기준으로 나누어서 왼쪽은 NULL, 오른쪽은 Player에 저장
	int32 Len = Player.Len();
	PlayerNum.Split(TEXT(":"), NULL, &Player);
	if (Player.IsEmpty())
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerNum is Empty"));
		return false;
	}
	if (Player[0] == '/')
	{
		return true;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Not Include '/'"));
		return false;
	}
}

// Host의 턴인지 Guest의 턴인지에 따라 리턴
int32 UBullsAndCowsLib::SetbIstHost(FString PlayerMsg)
{
	FString Player;
	PlayerMsg.Split(TEXT(":"), &Player, NULL);
	if (Player == TEXT("Host"))
	{
		return 1;
	}
	else if (Player == TEXT("Guest"))
	{
		return -1;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Not Include Host or Guest"));
		return 0;
	}
}


// 랜덤 숫자 생성  
FString UBullsAndCowsLib::MakeRandRange(FBallCount BC)
{  
   TArray<int32> numbers;
   while (numbers.Num() < 4)  
   {  
       int32 RandNumber = FMath::RandRange(1, 9);  
       bool alreadyget = numbers.Contains(RandNumber);  
       if (alreadyget == false)  
       {  
           numbers.Emplace(RandNumber);
       }  
   }  
   //UE_LOG(LogTemp, Warning, TEXT("%d%d%d"), numbers[0], numbers[1], numbers[2]);  
   BC.RandNum = FString::Printf(TEXT("%d%d%d"), numbers[0], numbers[1], numbers[2]);  

   return BC.RandNum;
}  


// 플레이어와 랜덤 숫자의 비교  
void UBullsAndCowsLib::CompareNum(FString PlayerNum, FString ServerNum , UPARAM(ref) FBallCount& BC)
{  
    FString Player;
	// 플레이어가 입력한 숫자를 ':' 기준으로 나누어서 왼쪽은 NULL, 오른쪽은 Player에 저장
    PlayerNum.Split(TEXT(":"), NULL, &Player);

	int32 Len = Player.Len();
	if (Player.IsEmpty())
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerNum is Empty"));
		return;
	}
	if (Player[0] != '/' || Len != 4)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Not Include '/' or Wrong input number length"));
		return;
	}

	// 첫번째 인덱스 '/' 제거
	Player.RemoveAt(0);

	// 스트라이크, 볼 카운트
    for (int32 i = 0; i < Player.Len(); i++)
    {
		if (Player[i] == ServerNum[i])
		{
			BC.StrikeCount++;
		}
		else
		for (int32 j = 0; j < Player.Len(); j++)
		{
			if (Player[i] == ServerNum[j])
			{
				BC.BallCount++;
			}
		}
    }
	BC.TurnCount--;
	// 로그	출력
    //UE_LOG(LogTemp, Warning, TEXT("Strike : %d, Ball : %d"), BC.StrikeCount,BC.BallCount);
}