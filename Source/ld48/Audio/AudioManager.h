// ----------------------------------------------------------------------------
//
// DWYW (Do What You Want) license 2020
// 
// ----------------------------------------------------------------------------
#pragma once
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"
// ----------------------------------------------------------------------------
class UAudioComponent;
class USoundBase;
// ----------------------------------------------------------------------------
/**
 * 
 */
UCLASS()
class LD48_API AAudioManager : public AActor
{
	GENERATED_BODY()

public:
	AAudioManager();

	virtual void BeginPlay() override;

	void RestartAudio();

private:
	void ShuffleSounds(TArray<USoundBase*>& Array);

	UFUNCTION()
	void OnAudioComponentFinishedPlaying();

private:
	UPROPERTY(EditAnywhere)
	UAudioComponent* _audioComponent;

	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> _backgroundSounds;
};
// ----------------------------------------------------------------------------
AAudioManager* GetAudioManager(UObject* worldContextObject);
// ----------------------------------------------------------------------------