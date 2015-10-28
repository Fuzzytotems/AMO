// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "AINPCController.generated.h"

/**
 * 
 */
UCLASS()
class ARENAMASTERSONLINE_API AAINPCController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAINPCController(const FObjectInitializer& ObjectInitializer);

	//UPROPERTY(EditAnywhere, Category = PlayerState)

	/* AI specific stats */
	UPROPERTY(EditAnywhere, Category = Personality)
		float Aggressiveness;
	
};
