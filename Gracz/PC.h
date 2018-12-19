// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperCharacter.h"
#include "PCMovementComponent.h"
#include "Missile.h"
#include "PC.generated.h"

USTRUCT(BlueprintType)
struct FPCInput
{
	GENERATED_BODY()

public:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	uint32 bFire1 : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	uint32 bFire2 : 1;

	void MoveRight(float AxisValue);
	void MoveUp(float AxisValue);
	void Fire1(bool bPressed);
	void Fire2(bool bPressed);
};

UCLASS()
class SIDESCROLLBULLETHELL_API APC : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	APC();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	const FPCInput& GetCurrentInput() const
	{
		return PCInput; 
	}
	


	//We can use our custom movement component
	class UPCMovementComponent* OurMovementComponent;

	//We can enable other classes in the engine to access the Pawn Movement Component
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	

	UFUNCTION (BlueprintCallable, Category = "Input")
	const FPCInput& GetCurrentInput() { return PCInput; }
protected:
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Missile")
	TSubclassOf<AMissile> Projectile;
	
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

private:

	//Input variables
	FVector CurrentVelocity;

	//Input functions
	void MoveRight(float AxisValue);
	void MoveUp(float AxisValue);
	void Fire1Pressed();
	void Fire1Released();
	void Fire2Pressed();
	void Fire2Released();
	void Turn(float AxisValue);

	//Direction of playable character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* PCDirection;

	// Sprite for our character
	UPROPERTY(VisibleAnywhere, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperSpriteComponent* CharacterSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
		FPCInput PCInput;

	// Time to delay between Fire1 commands.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire", meta = (AllowPrivateAccess = "true"))
		float Fire1Cooldown;

	// If this value is greater than the current game time, Fire1 is ignored because it has been fired too recently.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire", meta = (AllowPrivateAccess = "true"))
		float Fire1ReadyTime;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* FlipComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* Flip;*/


};
