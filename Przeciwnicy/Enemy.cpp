// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "SideScrollBulletHell.h"
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
	FlyMaxSpeed = 70.0f;
	AttackDistance = 100.0f;
	AttackAngle = 30.0f;
	AttackCooldown = 1.0f;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	USideScrollStaticss::PutInZPlane(this);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EnemyAI(DeltaTime);

	ConsumeMovementInputVector();
	ConsumeRotationInput();
	ConsumeAttackInput();
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::EnemyAI_Implementation(float DeltaSeconds)
{
	//If we have attack input then enemy won't move
	FVector DesiredMovement = GetAttackInput() ? FVector::ZeroVector : (FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(FlySpeed, FlyMaxSpeed), GetPendingMovementInputVector().X)) * DeltaSeconds * GetActorForwardVector();
	FVector OriginalLocation = GetActorLocation();
	FVector DesiredLoc = OriginalLocation + DesiredMovement;
	float MaxYawThisFrame = YawSpeed * DeltaSeconds;
	FRotator DesiredRot = GetActorRotation() + FRotator(0.0f, FMath::Clamp(GetRotationInput(), -MaxYawThisFrame, MaxYawThisFrame), 0.0f);

	SetActorLocationAndRotation(DesiredLoc, DesiredRot.Quaternion(), true);
	FVector DistanceWalked = GetActorLocation() - OriginalLocation;
	if (!DistanceWalked.IsNearlyZero())
	{
		Fly(DeltaSeconds, DistanceWalked);
	}

	if (AActor* Target = GetTarget())
	{
		//Attack when  in range
		FVector OurLocation = GetActorLocation();
		FVector DirectionToTarget = (Target->GetActorLocation() - OurLocation).GetSafeNormal2D();
		float ToTarget = FVector::DotProduct(DirectionToTarget, GetActorForwardVector());

		float CurrentTime = GetWorld()->GetTimeSeconds();
		if (GetAttackInput() && (AttackAvailableTime <= CurrentTime))
		{
			AttackAvailableTime = CurrentTime + AttackCooldown;
			Attack(DeltaSeconds);
			if (ToTarget >= FMath::Cos(FMath::DegreesToRadians(AttackAngle)))
			{
				float DistSqXY = FVector::DistSquaredXY(Target->GetActorLocation(), OurLocation);
				if (DistSqXY <= (AttackDistance * AttackDistance))
				{
					if (APC* TargetPC = GetTargetAsPC())
					{
						//TargetPC->DamageHealth(10.0f);
						if (APlayerController* PC = Cast<APlayerController>(TargetPC->GetController()))
						{
							PC->ClientPlayCameraShake(HitShake, 1.0f);
						}
					}
					else
					{
						SetTarget(nullptr);
					}
				}

			}

		}
	}

	else
	{
		// Look for a target. We might not do this every single frame, but for now it's OK.
		// TODO: Make this use a list of registered targets so we can handle multiplayer or add decoys.
		Target = UGameplayStatics::GetPlayerPawn(this, 0);
		float DistSqXY = FVector::DistSquaredXY(Target->GetActorLocation(), GetActorLocation());
		if (DistSqXY <= (SightDistance * SightDistance))
		{
			FVector DirectionToTarget = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
			if (FVector::DotProduct(DirectionToTarget, GetActorForwardVector()) >= FMath::Cos(FMath::DegreesToRadians(SightAngle)))
			{
				SetTarget(Target);
			}
		}
	}
}
bool AEnemy::ShouldAttack_Implementation()
{
	if (AActor* Target = GetTarget())
	{
		// Attack our target if we're in range (distance and angle). For now, we'll use our unmodified attack variables for this.
		FVector OurLocation = GetActorLocation();
		FVector DirectionToTarget = (Target->GetActorLocation() - OurLocation).GetSafeNormal2D();
		float ToTarget = FVector::DotProduct(DirectionToTarget, GetActorForwardVector());
		if (ToTarget >= FMath::Cos(FMath::DegreesToRadians(AttackAngle)))
		{
			float DistSqXY = FVector::DistSquaredXY(Target->GetActorLocation(), OurLocation);
			if (DistSqXY <= (AttackDistance * AttackDistance))
			{
				// Note that attacking cooldown isn't checked. We don't want this kind of zombie to move between attacks or think it's not attacking while waiting for the cooldown.
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

void AEnemy::AddRotationInput(float  DeltaYawDegrees)
{
	YawInput += DeltaYawDegrees;
}

float AEnemy::GetRotationInput()
{
	return YawInput;
}

float AEnemy::ConsumeRotationInput()
{
	float RetVal = YawInput;
	YawInput = 0.0f;
	return RetVal;
}

void AEnemy::AddAttackInput()
{
	bAttackInput = true;
}
bool AEnemy::GetAttackInput()
{
	return bAttackInput;
}

bool AEnemy::ConsumeAttackInput()
{
	bool bRetVal = bAttackInput;
	bAttackInput = false;
	return bRetVal;
}