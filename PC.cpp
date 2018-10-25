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

// Sets default values
APC::APC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Our root component will be a sphere that reacts to physics
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Create and position a mesh component so we can see where our sphere is
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/StarterContent/Shapes/Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	// Create a particle system that we can activate or deactivate
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	// Create a camera and attach to our spring arm
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
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
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
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

