#include "MyActor.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/Array.h"
#include "Engine/Engine.h"

AMyActor::AMyActor()
{
    PrimaryActorTick.bCanEverTick = true;
    start = FVector2D(0, 0);
    evCnt = 0;
    totDist = 0;
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();
    move();
    UE_LOG(LogTemp, Warning, TEXT("총 이동 거리: %f"), totDist);
    UE_LOG(LogTemp, Warning, TEXT("총 이벤트 발생 횟수: %d"), evCnt);
}

int32 AMyActor::step()
{
    return FMath::RandRange(0, 1); // 0 또는 1을 반환
}

float AMyActor::distance(FVector2D first, FVector2D second)
{
    float dx = first.X - second.X;
    float dy = first.Y - second.Y;
    return FMath::Sqrt(dx * dx + dy * dy);
}

int32 AMyActor::createEvent()
{
    int32 RandomValue = FMath::RandRange(1, 100);
    if (RandomValue <= 50) // 50% 확률
    {
        UE_LOG(LogTemp, Log, TEXT("이벤트 발생!"));
        return 1; // 이벤트 발생
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("이벤트 미발생"));
        return 0; // 이벤트 미발생
    }
}

void AMyActor::move()
{
    FVector2D current = start; // 시작 좌표 (0,0)
    FVector2D previous = current;

    for (int32 i = 0; i < 10; ++i) // 10회 이동
    {
        int32 stepX = step(); // X축 이동
        int32 stepY = step(); // Y축 이동

        // 지역 변수
        // `next`는 이 블록 안에서만 유효함
        FVector2D next(current.X + stepX, current.Y + stepY);

        if (next.X - current.X <= 2 && next.Y - current.Y <= 2)
        {
            float dist = distance(current, next); // 이동 거리 계산
            totDist += dist; // 총 이동 거리 업데이트

            UE_LOG(LogTemp, Warning, TEXT("스텝 %d: 현재 좌표: (%f, %f), 이동 거리: %f"), i + 1, next.X, next.Y, dist);

            // 이벤트 발생 여부 확인
            evCnt += createEvent();

            previous = current;
            current = next; // 다음 좌표로 업데이트
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("잘못된 이동. 다시 시도."));
        }
    }
}