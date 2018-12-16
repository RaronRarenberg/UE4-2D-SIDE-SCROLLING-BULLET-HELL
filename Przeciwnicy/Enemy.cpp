// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "PC.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = 100.0f;
	SightDistance = 500.0f;
	SightAngle = 60.0f;
	YawSpeed = 90.0f;
	FlySpeed = 45.0f;
	AttackDistance = 100.0f;
	AttackAngle = 30.0f;
	AttackCooldown = 1.0f;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemy::ShouldAttack_Implementation()
{
	if (AActor* Target = GetTarget())
	{
		//Attack when  in range
		FVector OurLocation = GetActorLocation();
		FVector DirectionToTarget = (Target->GetActorLocation() - OurLocation).GetSafeNormal2D();
		float ToTarget = FVector::DotProduct(DirectionToTarget, GetActorForwardVector());
		if (ToTarget >= FMath::Cos(FMath::DegreesToRadians(AttackAngle)))
		{
			float DistSqXY = FVector::DistSquaredXY(Target->GetActorLocation(), OurLocation);
			if (DistSqXY <= (AttackDistance * AttackDistance))
			{
				return true;
			}
		}
	}
	return false;
}

void AEnemy::SetTarget(AActor* NewTarget)
{
	TargetActor = NewTarget;
	TargetPC = Cast<APC>(NewTarget);
}
AActor* AEnemy::GetTarget()
{
	return TargetActor;
}

APC* AEnemy::GetTargetAsPC()
{
	return TargetPC;
}