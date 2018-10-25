// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "PC.generated.h"

UCLASS()
class SIDESCROLLBULLETHELL_API APC : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
	
	//Input functions
	void MoveRight(float AxisValue);
	void MoveUp(float AxisValue);
	void Turn(float AxisValue);
	void ParticleToggle();

	//Input variables
	FVector CurrentVelocity;

	//Keeps track of Particle System Component
	UParticleSystemComponent *OurParticleSystem;

	//We can use our custom movement component
	class UPCMovementComponent* OurMovementComponent;

	//We can enable other classes in the engine to access the Pawn Movement Component
	virtual UPawnMovementComponent* GetMovementComponent() const override;
};
