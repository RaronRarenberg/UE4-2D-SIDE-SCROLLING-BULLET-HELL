// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

class APC;

UCLASS()
class SIDESCROLLBULLETHELL_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Set this enemy's target
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetTarget(AActor* NewTarget);

	//Return target actor
	UFUNCTION(BlueprintCallable, Category = "AI")
	AActor* GetTarget();

	//Return target actor as our character
	UFUNCTION(BlueprintCallable, Category = "AI")
	APC* GetTargetAsPC();

	UFUNCTION(BlueprintNativeEvent, Category = "AI")
	void EnemyAI(float DeltaSeconds);
	virtual void EnemyAI_Implementation(float DeltaSeconds);

	//Asks enemy if he is able to hit player
	UFUNCTION(BlueprintNativeEvent, Category = "AI")
	bool ShouldAttack();
	virtual bool ShouldAttack_Implementation();

	//Animate moving
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void Fly(float DeltaSeconds, FVector DistanceWalkedThisFrame);

	//Animate attacking
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void Attack(float DeltaSeconds);

	//Add rotation input to provided yaw
	UFUNCTION(BlueprintCallable, Category = "Input", meta = (Keywords = "AddInput"))
	virtual void AddRotationInput(float DeltaYawDegrees);

	//Get rotation input
	UFUNCTION(BlueprintCallable, Category = "Input", meta = (Keywords = "ConsumeInput"))
	virtual float GetRotationInput();

	//Get and clear rotation input
	UFUNCTION(BlueprintCallable, Category = "Input", meta = (Keywords = "ConsumeInput"))
	virtual float ConsumeRotationInput();

	//Press  the attack button
	UFUNCTION(BlueprintCallable, Category = "Input", meta = (Keywords = "AddInput"))
	virtual void AddAttackInput();

	//Get the status of the attack button
	UFUNCTION(BlueprintCallable, Category = "Input", meta = (Keywords = "ConsumeInput"))
	virtual bool GetAttackInput();

	//Get and clear the status of the attack button
	UFUNCTION(BlueprintCallable, Category = "Input", meta = (Keywords = "ConsumeInput"))
	virtual bool ConsumeAttackInput();


private:
	//Actor we target
	UPROPERTY(VisibleInstanceOnly, Category = "AI")
	AActor* TargetActor;

	//Actor we target
	UPROPERTY(VisibleInstanceOnly, Category = "AI")
	APC* TargetPC;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Camera shake when you get hit
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShake> HitShake;

	//HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
	float Health;
	//How far can enemy see
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
	float SightDistance;

	//Angle of sight
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
	float SightAngle;

	//Maximum speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
	float YawSpeed;

	//Speed of our enemies
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
	float FlySpeed;

	//Speed of our enemies
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
	float FlyMaxSpeed;

	//Distance where enemy engages us
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
	float AttackDistance;

	//Your angle of attack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
	float AttackAngle;

	//Time between enemy attacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
	float AttackCooldown;

	//Time when enemy is able to attack again
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = "Enemy")
	float AttackAvailableTime;

private:
	//Rotation input
	float YawInput;

	//Attack button status
	uint32 bAttackInput : 1;

};
