// ----------------------------------------------------------------------------
//
// DWYW (Do What You Want) license 2020
// 
// ----------------------------------------------------------------------------
#include "AudioManager.h"
#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"
#include "../ld48WorldSettings.h"
// ----------------------------------------------------------------------------
AAudioManager::AAudioManager()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Music Audio Component"));
	_audioComponent->SetupAttachment(RootComponent);
}
// ----------------------------------------------------------------------------
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();

	if (_audioComponent != nullptr)
	{
		_audioComponent->OnAudioFinished.AddDynamic(this, &AAudioManager::OnAudioComponentFinishedPlaying);
	}

	if (_audioComponent != nullptr && _backgroundSounds.Num() > 0)
	{
		ShuffleSounds(_backgroundSounds);
		_audioComponent->SetSound(_backgroundSounds[0]);
		_audioComponent->Play();
	}
}
// ----------------------------------------------------------------------------
void AAudioManager::RestartAudio()
{
	_audioComponent->Stop();
	_audioComponent->Play();
}
// ----------------------------------------------------------------------------
void AAudioManager::ShuffleSounds(TArray<USoundBase*>& Array)
{
	if (Array.Num() == 0)
	{
		return;
	}

	int32 LastIndex = Array.Num() - 1;
	for (int32 i = 0; i <= LastIndex; ++i)
	{
		int32 j = FMath::RandRange(i, LastIndex);
		if (i != j)
		{
			Array.Swap(i, j);
		}
	}
}
// ----------------------------------------------------------------------------
void AAudioManager::OnAudioComponentFinishedPlaying()
{
	if (_audioComponent != nullptr && _backgroundSounds.Num() > 0)
	{
		ShuffleSounds(_backgroundSounds);
		_audioComponent->SetSound(_backgroundSounds[0]);
		_audioComponent->Play();
	}
}
// ----------------------------------------------------------------------------
AAudioManager* GetAudioManager(AActor* worldContextObject)
{
	if (worldContextObject == nullptr)
	{
		return nullptr;
	}

	Ald48WorldSettings* ws = Cast<Ald48WorldSettings>(worldContextObject->GetWorldSettings());
	if (ws == nullptr)
	{
		return nullptr;
	}

	return ws->GetAudioManager();
}
// ----------------------------------------------------------------------------