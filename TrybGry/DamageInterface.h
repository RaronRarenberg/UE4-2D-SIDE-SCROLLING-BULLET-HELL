// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageInterface.generated.h"
/**
 * 
 */
UINTERFACE(MinimalAPI)
class UDamageInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class SIDESCROLLBULLETHELL_API IDamageInterface

{
	GENERATED_IINTERFACE_BODY()

public:
	virtual void ReceiveDamage(int32 IncomingDamage) = 0;
	virtual int32 GetHealthRemaining() = 0;
};