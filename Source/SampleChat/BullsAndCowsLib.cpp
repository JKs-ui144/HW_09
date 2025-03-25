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
	// �÷��̾ �Է��� ���ڸ� ':' �������� ����� ������ NULL, �������� Player�� ����
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

// Host�� ������ Guest�� �������� ���� ����
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


// ���� ���� ����  
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


// �÷��̾�� ���� ������ ��  
void UBullsAndCowsLib::CompareNum(FString PlayerNum, FString ServerNum , UPARAM(ref) FBallCount& BC)
{  
    FString Player;
	// �÷��̾ �Է��� ���ڸ� ':' �������� ����� ������ NULL, �������� Player�� ����
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

	// ù��° �ε��� '/' ����
	Player.RemoveAt(0);

	// ��Ʈ����ũ, �� ī��Ʈ
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
	// �α�	���
    //UE_LOG(LogTemp, Warning, TEXT("Strike : %d, Ball : %d"), BC.StrikeCount,BC.BallCount);
}