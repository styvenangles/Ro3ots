// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
<<<<<<< HEAD
=======
#include "Ro3otsCharacter.h"
>>>>>>> 1bbaec5 (# This is a combination of 2 commits.)
#include "Ro3otsPlayerController.generated.h"

/**
 * 
 */
 /** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class RO3OTS_API ARo3otsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARo3otsPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UNiagaraSystem* FXCursor;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

private:
	bool bInputPressed; // Input is bring pressed
	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed

};
