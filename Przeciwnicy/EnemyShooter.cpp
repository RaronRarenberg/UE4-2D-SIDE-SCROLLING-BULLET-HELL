// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyShooter.h"
#include "Missile.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEnemyShooter::AEnemyShooter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Cooldown between shots
	Fire1Cooldown = 0.05f;

	// Our root component 
	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CharacterCore"));
	}
	EnemyShooterDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("CharacterDirection"));
	EnemyShooterDirection->SetupAttachment(RootComponent);

	//Sprite of our character
	EnemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("EnemyShooter"));
	EnemySprite->SetupAttachment(EnemyShooterDirection);

	static ConstructorHelpers::FObjectFinder<UClass> MissileClassFinder(TEXT("Blueprint'/Game/BulletHell/MissileBP.MissileBP_C'"));
	Projectile = MissileClassFinder.Object;
}

// Called when the game starts or when spawned
void AEnemyShooter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Input handler
	const FEnemyShooterInput& CurrentInput = GetCurrentInput();
	//Spawn projectile by shooting
	if (CurrentInput.bFire1)
	{
		float CurrentTime = GetWorld()->GetTimeSeconds();
		//Delay between shots
		if (Fire1ReadyTime <= CurrentTime)
		{
			FVector Loc = EnemySprite->GetComponentLocation();
			FRotator Rot = EnemySprite->GetComponentRotation();


			AMissile* NewMissile = GetWorld()->SpawnActor<class AMissile>(Projectile, Loc, Rot);
			UE_LOG(LogTemp, Warning, TEXT("FEUER!"));

			// Set the cooldown timer.
			Fire1ReadyTime = CurrentTime + Fire1Cooldown;

		}
	}
}

// Called to bind functionality to input
void AEnemyShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void FEnemyShooterInput::Fire1(bool bPressed)
{
	bFire1 = bPressed;
}

void AEnemyShooter::Fire1Pressed()
{
	EnemyShooterInput.Fire1(true);
}
void AEnemyShooter::Fire1Released()
{
	EnemyShooterInput.Fire1(false);
}
