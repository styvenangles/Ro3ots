// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ro3otsCharacter.generated.h"

UCLASS(config=Game)
class ARo3otsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARo3otsCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, Category = "Collision")
		TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditAnywhere, Category = "Trace")
		float TraceRadius = 100.0f;

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
		bool isMovingToAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool isInRangeToAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact")
		AActor* targetActor;

	UFUNCTION()
		void AttackSelectedEnemy(AActor* Enemy);

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	bool canAttack = false;

	float attackTimer = 0.0f;

};

