// Fill out your copyright notice in the Description page of Project Settings.

#include "Missile.h"
#include "DamageInterface.h"
#include "SideScrollBulletHell.h"
//#include "DamageInterface.h"

// Sets default values
AMissile::AMissile()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Speed = 10.0f;
	Radius = 20.0f;
	DirectDamage = 5;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	
	
	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &AMissile::Explode, 1.0f);

}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Loc = GetActorLocation();
	FVector DesiredEndLoc = Loc + DeltaTime * Speed * GetTransform().GetUnitAxis(EAxis::X);
	
	
	if (UWorld*  World = GetWorld())
	{
		FHitResult OutHit;
		FCollisionShape CollisionShape;
		CollisionShape.SetSphere(Radius);
		if (World->SweepSingleByProfile(OutHit, Loc, DesiredEndLoc, FQuat::Identity, MovementCollisionProfile, CollisionShape))
		{
			SetActorLocation(OutHit.Location);
			if (IDamageInterface* DamageActor = Cast<IDamageInterface>(OutHit.Actor.Get()))
			{
				DamageActor->ReceiveDamage(DirectDamage);
			}
			Explode();
		}
		else
		{
			SetActorLocation(DesiredEndLoc);
		}
	}
}

void AMissile::OnExplode_Implementation()
{
	Destroy();
}

void AMissile::Explode()
{
	GetWorldTimerManager().ClearTimer(ExplodeTimerHandle);
	SetActorEnableCollision(false);
	OnExplode();
}