// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"

void AEnemyAI::Tick(float DeltaTime)
{
	if (EnemyPawn)
	{
		if (AActor* Target = EnemyPawn->GetTarget())
		{
			FVector DirectionToTarget = (Target->GetActorLocation() - EnemyPawn->GetActorLocation()).GetSafeNormal2D();
			float ToTarget = FVector::DotProduct(DirectionToTarget, EnemyPawn->GetActorForwardVector());
			float SidewaysToTarget = FVector::DotProduct(DirectionToTarget, EnemyPawn->GetActorRightVector());
			float DeltaYawDesired = FMath::Atan2(SidewaysToTarget, ToTarget);
		
		}

		if (EnemyPawn->ShouldAttack())
		{
			EnemyPawn->AddAttackInput();
		}
		else
		{
			//Fastest when facing target
			EnemyPawn->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), FMath::GetMappedRangeValueClamped(FVector2D(-0.707f, 0.707f), FVector2D(0.0f, 1.0f), ToTarget));
			//
			EnemyPawn->AddRotationInput(DeltaYawDesired);
		}
		
	}
}

void AEnemyAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	EnemyPawn = Cast<AEnemy>(GetPawn());
}

void AEnemyAI::UnPossess()
{
	Super::UnPossess();
	EnemyPawn = nullptr;
}


