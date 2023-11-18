// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "CDPaperCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPaperFlipbook;

/**
 * 
 */
UCLASS()
class COSMICDESCENT_API ACDPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	ACDPaperCharacter();

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
	bool bFlipOnVelocity = true;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void UpdateCharacter();
	
	virtual void UpdateAnimation();

public:
	UFUNCTION(BlueprintCallable)
	virtual FVector GetInputVelocity() const;

	UFUNCTION(BlueprintCallable)
	virtual FVector GetRelativeVelocity() const;

	UFUNCTION(BlueprintCallable)
	void Slide();

	UFUNCTION(BlueprintCallable)
	bool isSliding();

private:
	void StartSliding();
	void StopSliding();

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	FTimerHandle SlideTimer;
	bool bIsSliding = false;
	float SlideDuration = 0.5f;
	float SlideMultiplier = 5.0f;
	float SlideDeleration = 128.f;
	float DefaultDeleration = 2048.f;

	FVector InputVelocity = FVector::ZeroVector;
};