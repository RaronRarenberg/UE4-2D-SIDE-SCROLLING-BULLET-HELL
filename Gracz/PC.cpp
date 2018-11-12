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
#include "PaperFlipbookComponent.h" 

// Sets default values
APC::APC() 
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/*struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>flippc;
		FConstructorStatics()
			:flippc(TEXT("PaperFlipbook'/Game/2DGraveyardPackHandcraftedArt/Sprites/PlayableBat.PlayableBat'"))
		{
		
		}
	};

	static FConstructorStatics ConstructorStatics;
	
	Flip = ConstructorStatics.flippc.Get();

	FlipComponent = PCIP.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("FlipbookComponent"));
	FlipComponent->SetFlipbook(Flip);

	CharacterSprite = PCIP.CreateDefaultSubobject <UPaperSpriteComponent>(this, TEXT("Character"));
	CharacterSprite->AttachTo(FlipComponent,"gunsock",EAttachLocation::SnapToTarget);*/
	

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Our root component 
	if (RootComponent == nullptr)
	{ 
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CharacterCore"));
	}
	PCDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("CharacterDirection"));
	PCDirection->SetupAttachment(RootComponent);
	
	//Sprite of our character
	CharacterSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PC"));
	CharacterSprite->SetupAttachment(PCDirection);

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 4.0f;
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	SpringArm->bAbsoluteRotation = true;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);

	// Create a camera and attach to our spring arm
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 1024.0f;
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
	InputComponent->BindAction("Fire1", EInputEvent::IE_Pressed, this, &APC::Fire1Pressed);
	InputComponent->BindAction("Fire1", EInputEvent::IE_Released, this, &APC::Fire1Released);
	InputComponent->BindAction("Fire2", EInputEvent::IE_Pressed, this, &APC::Fire2Pressed);
	InputComponent->BindAction("Fire2", EInputEvent::IE_Released, this, &APC::Fire2Released);
}

void APC::MoveRight(float AxisValue)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 200.0f;
}

void APC::MoveUp(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentVelocity.Z = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 200.0f;
}

void FPCInput::Fire1(bool bPressed)
{
	bFire1 = bPressed;
}

void FPCInput::Fire2(bool bPressed)
{
	bFire2 = bPressed;
}

void APC::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void APC::Fire1Pressed()
{
	APC.Fire1(true);
}
void APC::Fire1Released()
{
	APC.Fire1(false);
}
void APC::Fire2Pressed()
{
	APC.Fire2(true);
}
void APC::Fire2Released() 
{
	APC.Fire2(false);
}

UPawnMovementComponent* APC::GetMovementComponent() const
{
	return OurMovementComponent;
}

