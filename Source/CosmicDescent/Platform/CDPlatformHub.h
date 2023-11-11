// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CDPlatformHub.generated.h"

UCLASS()
class COSMICDESCENT_API ACDPlatformHub : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACDPlatformHub();

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> PlatformPayload;

	TArray<AActor*> PlatformArray;

	bool PrevRight = true;

	int32 PrevIndex = 0;

	int32 Random = 0;

    UPROPERTY(EditAnywhere)
    int32 Count = 10;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnPlatform();

	void DeletePlatform();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FRotator Rotation;
	FVector Location;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
