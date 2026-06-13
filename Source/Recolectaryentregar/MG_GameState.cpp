#include "MG_GameState.h"
#include "Net/UnrealNetwork.h"

void AMG_GameState::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMG_GameState, TimeRemaining);
    DOREPLIFETIME(AMG_GameState, GlobalScore);
    DOREPLIFETIME(AMG_GameState, bGameActive);
    DOREPLIFETIME(AMG_GameState, ScoreTeamRed);
    DOREPLIFETIME(AMG_GameState, ScoreTeamBlue);
    DOREPLIFETIME(AMG_GameState, MatchPhase);
    DOREPLIFETIME(AMG_GameState, CountdownValue);
    DOREPLIFETIME(AMG_GameState, FruitsTeamRed);
    DOREPLIFETIME(AMG_GameState, FruitsTeamBlue);
}

void AMG_GameState::OnRep_GameActive()
{
    UE_LOG(LogTemp, Warning, TEXT("GameActive changed: %s"),
        bGameActive ? TEXT("Active") : TEXT("Inactive"));
}

void AMG_GameState::SetMatchPhase(EMatchPhase NewPhase)
{
    MatchPhase = NewPhase;
    bGameActive = (NewPhase == EMatchPhase::Playing);
}

void AMG_GameState::SetCountdownValue(int32 NewValue)
{
    CountdownValue = NewValue;
}

void AMG_GameState::SetMatchTimer(float NewTime)
{
    TimeRemaining = NewTime;
}