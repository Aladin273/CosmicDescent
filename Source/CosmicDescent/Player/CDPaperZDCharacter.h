// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperZDCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

#include "CDPaperZDCharacter.generated.h"

/**
 * 
 */
UCLASS()
class COSMICDESCENT_API ACDPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ACDPaperZDCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook* IdleAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook* JumpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook* RunAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook* SlideAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	bool bFacingRight = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	bool bFlipOnInputVelocity = true;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void UpdateCharacter();

	virtual void UpdateAnimation();

	UFUNCTION(BlueprintCallable)
	virtual FVector GetInputVelocity() const;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	FVector InputVelocity = FVector::ZeroVector;
};