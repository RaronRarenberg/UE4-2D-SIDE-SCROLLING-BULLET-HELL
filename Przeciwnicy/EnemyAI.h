// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLBULLETHELL_API AEnemyAI : public AAIController
{
	GENERATED_BODY()
public:

	virtual void  Tick(float DeltaTime)override;

	virtual void Possess(APawn* InPawn)override;
	virtual void UnPossess()override;

protected:
	//Pawn
	UPROPERTY(BlueprintReadOnly, Category = "Zombie")
	AEnemy* EnemyPawn;
};
