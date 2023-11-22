// Fill out your copyright notice in the Description page of Project Settings.

#include "CDAICharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Player/CDPaperCharacter.h"
#include "../Platform/CDBlock.h"

ACDAICharacter::ACDAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMesh->SetSimulatePhysics(true);
	
	SetRootComponent(StaticMesh);
}

void ACDAICharacter::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ACDAICharacter::OnOverlap);
	GetWorld()->GetTimerManager().SetTimer(ForceTimer, this, &ACDAICharacter::UpdateForce, ForceUpdateTime, true);
}

void ACDAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StaticMesh->AddForce(ForceVector * ForceSpeed);
}

void ACDAICharacter::UpdateForce()
{
	ForceSpeed += ForceAcceleration;
}

void ACDAICharacter::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACDPaperCharacter* Player = Cast<ACDPaperCharacter>(OtherActor);

	if (Player)
		Player->GetCapsuleComponent()->SetSimulatePhysics(true);
	
	if (Cast<ACDBlock>(OtherActor))
		OtherActor->Destroy();
}

