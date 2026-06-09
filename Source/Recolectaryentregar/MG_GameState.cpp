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
}

void AMG_GameState::OnRep_GameActive()
{
    UE_LOG(LogTemp, Warning, TEXT("GameActive changed: %s"),
        bGameActive ? TEXT("Active") : TEXT("Inactive"));
}

void AMG_GameState::OnRep_MatchPhase()
{
    UE_LOG(LogTemp, Warning, TEXT("MatchPhase changed"));
}

void AMG_GameState::SetMatchPhase(EMatchPhase NewPhase)
{
    if (HasAuthority())
    {
        MatchPhase = NewPhase;
        bGameActive = (NewPhase == EMatchPhase::Playing);
        OnRep_MatchPhase();
    }
}

void AMG_GameState::SetCountdownValue(int32 Value)
{
    if (HasAuthority())
        CountdownValue = Value;
}

void AMG_GameState::SetMatchTimer(float Value)
{
    if (HasAuthority())
        TimeRemaining = Value;
}