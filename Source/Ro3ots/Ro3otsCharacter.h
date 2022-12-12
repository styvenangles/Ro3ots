// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "AttackSystem.h"
#include "Ro3otsCharacter.generated.h"

UCLASS(config=Game)
class ARo3otsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARo3otsCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category = "Collision")
		TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditAnywhere, Category = "Trace")
		float TraceRadius = 100.0f;

<<<<<<< HEAD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
		int Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
		float AttackSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
		float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
		float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
		float MouvementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool isInRangeToAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool canAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		int attackInstances = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact")
		AActor* targetActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact")
		FVector actorLocation;

	UFUNCTION()
		void AttackSelectedEnemy(AActor* Enemy);

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

=======
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool isMovingToAttack = false;

	UFUNCTION(BlueprintImplementableEvent)
		void AttackEnemy(AActor* Enemy);

	UFUNCTION()
		void SetBooleanVariable(FString variableName);

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

>>>>>>> 1bbaec5 (# This is a combination of 2 commits.)
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY()
		float interval;

	float attackTimer = 0.0f;
		
};

