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
	virtual void Tick(float DeltaTime) override;

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

	//Asks enemy if he is able to hit player
	UFUNCTION(BlueprintNativeEvent, Category = "AI")
	bool ShouldAttack();
	virtual bool ShouldAttack_Implementation();

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

	//Distance where enemy engages us
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
		float AttackDistance;

	//Your angle of attack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
		float AttackAngle;

	//Time between enemy attacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "0.0"))
		float AttackCooldown;

};
