// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "BetterGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class COSMICDESCENT_API UBetterGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetInitLaunch(bool InLaunch) { bInitLaunch = InLaunch; };

	UFUNCTION(BlueprintCallable)
	void SetMusicVolume(float InVolume) { MusicVolume = InVolume; };

	UFUNCTION(BlueprintCallable)
	void SetSFXVolume(float InVolume) { SFXVolume = InVolume; };
	
	
	UFUNCTION(BlueprintCallable)
	bool GetInitLaunch() const { return bInitLaunch; };

	UFUNCTION(BlueprintCallable)
	float GetMusicVolume() const { return MusicVolume; };
	
	UFUNCTION(BlueprintCallable)
	float GetSFXVolume() const { return SFXVolume; };

	
	UFUNCTION(BlueprintCallable)
	void SetMasterSoundMix(USoundMix* InSoundMix) { MasterSoundMix = InSoundMix; }
	
	UFUNCTION(BlueprintCallable)
	void SetMusicSoundClass(USoundClass* InSoundClass) { MusicSoundClass = InSoundClass; }

	UFUNCTION(BlueprintCallable)
	void SetSFXSoundClass(USoundClass* InSoundClass) { SFXSoundClass = InSoundClass; }

	
	UFUNCTION(BlueprintCallable)
	USoundMix* GetMasterSoundMix() const { return MasterSoundMix; }
	
	UFUNCTION(BlueprintCallable)
	USoundClass* GetMusicSoundClass() const { return MusicSoundClass; }

	UFUNCTION(BlueprintCallable)
	USoundClass* GetSFXSoundClass() const { return SFXSoundClass; }

	
	UFUNCTION(BlueprintCallable)
	static UBetterGameUserSettings* GetBetterGameUserSettings()
	{
		return Cast<UBetterGameUserSettings>(UGameUserSettings::GetGameUserSettings());
	}

	void ApplySettings(bool bCheckForCommandLineOverrides) override
	{
		Super::ApplySettings(bCheckForCommandLineOverrides);

		UGameplayStatics::SetSoundMixClassOverride(this, MasterSoundMix, MusicSoundClass, MusicVolume, 1.0f, 0.0f);
		UGameplayStatics::SetSoundMixClassOverride(this, MasterSoundMix, SFXSoundClass, SFXVolume, 1.0f, 0.0f);
	}

protected:
	UPROPERTY(Config)
	bool bInitLaunch = true;

	UPROPERTY(Config)
	float MusicVolume = 1.0f;

	UPROPERTY(Config)
	float SFXVolume = 1.0f;

	UPROPERTY()
	USoundMix* MasterSoundMix;
	
	UPROPERTY()
	USoundClass* MusicSoundClass;

	UPROPERTY()
	USoundClass* SFXSoundClass;
};