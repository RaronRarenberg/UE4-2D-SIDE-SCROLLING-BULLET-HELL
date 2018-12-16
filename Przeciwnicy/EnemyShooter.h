// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "Missile.h"
#include "PaperCharacter.h"
#include "EnemyShooter.generated.h"

USTRUCT(BlueprintType)
struct FEnemyShooterInput
{
	GENERATED_BODY()

public:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
		uint32 bFire1 : 1;
	
	void Fire1(bool bPressed);
};

UCLASS()
class SIDESCROLLBULLETHELL_API AEnemyShooter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyShooter();

	const FEnemyShooterInput& GetCurrentInput() const
	{
		return EnemyShooterInput;
	}

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	const FEnemyShooterInput& GetCurrentInput() { return EnemyShooterInput; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Missile")
	TSubclassOf<AMissile> Projectile;
private:
	void Fire1Pressed();
	void Fire1Released();

	//Direction of playable character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* EnemyShooterDirection;

	// Sprite for our enemy
	UPROPERTY(VisibleAnywhere, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* EnemySprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	FEnemyShooterInput EnemyShooterInput;

	// Time to delay between Fire1 commands.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire", meta = (AllowPrivateAccess = "true"))
		float Fire1Cooldown;

	// If this value is greater than the current game time, Fire1 is ignored because it has been fired too recently.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire", meta = (AllowPrivateAccess = "true"))
		float Fire1ReadyTime;
	
	
};
