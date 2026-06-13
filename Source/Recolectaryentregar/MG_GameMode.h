#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MG_GameMode.generated.h"

UCLASS()
class RECOLECTARYENTREGAR_API AMG_GameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMG_GameMode();
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly)
    float MatchDuration = 180.f;

    UPROPERTY(EditDefaultsOnly)
    int32 CountdownDuration = 3;

private:
    void TickCountdown();
    void TickMatchTimer();
    void EndGame();

    FTimerHandle CountdownTimerHandle;
    FTimerHandle MatchTimerHandle;

    int32 CurrentCountdown = 3;
};