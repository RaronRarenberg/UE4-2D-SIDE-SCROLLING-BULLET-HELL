// Fill out your copyright notice in the Description page of Project Settings.

#include "PC.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "PCMovementComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
APC::APC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Our root component 
	if (RootComponent == nullptr)
	{ 
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CharacterCore"));
	}
	PCDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("CharacterDirection"));
	PCDirection->AttachTo(RootComponent);
	
	//Sprite of our character
	CharacterSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PC"));
	CharacterSprite->AttachTo(PCDirection);

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	SpringArm->bAbsoluteRotation = true;
	SpringArm->bDoCollisionTest = false;
	SpringArm->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);

	// Create a camera and attach to our spring arm
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 2048.0f;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Create an instance of our movement component, and tell it to update the root.
	OurMovementComponent = CreateDefaultSubobject<UPCMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void APC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle movement based on our "MoveRight" and "MoveUp" axes
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void APC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &APC::ParticleToggle);
	// Respond every frame to the values of our two movement axes, "MoveRight" and "MoveUp".
	InputComponent->BindAxis("MoveX", this, &APC::MoveRight);
	InputComponent->BindAxis("MoveY", this, &APC::MoveUp);
}

void APC::MoveRight(float AxisValue)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void APC::MoveUp(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentVelocity.Z = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void APC::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void APC::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}
UPawnMovementComponent* APC::GetMovementComponent() const
{
	return OurMovementComponent;
}

