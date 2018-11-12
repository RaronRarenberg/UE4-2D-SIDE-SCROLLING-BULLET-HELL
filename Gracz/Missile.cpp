// Fill out your copyright notice in the Description page of Project Settings.

#include "Missile.h"


// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 600.0f;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimeToVanish;
	GetWorldTimerManager().SetTimer(TimeToVanish, this, &AMissile::Explode, 0.5f);

}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Loc = GetActorLocation();
	Loc += (DeltaTime * Speed) * GetTransform().GetUnitAxis(EAxis::X);
	SetActorLocation(Loc);
}

void AMissile::Explode_Implementation()
{
	Destroy();
}