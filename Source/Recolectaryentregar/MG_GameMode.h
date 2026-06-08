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

    UFUNCTION()
    void CheckVictoryCondition();

    UFUNCTION()
    void EndGame(bool bWinner);

    UPROPERTY(EditDefaultsOnly)
    float MatchDuration = 120.f;

private:
    FTimerHandle MatchTimerHandle;
};