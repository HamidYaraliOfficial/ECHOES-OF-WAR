#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EchoesOfWarGameMode.generated.h"

UCLASS()
class ECHOESOFWAR_API AEchoesOfWarGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AEchoesOfWarGameMode();

	virtual void StartPlay() override;
};
