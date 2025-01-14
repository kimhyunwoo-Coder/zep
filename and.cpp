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
    UE_LOG(LogTemp, Warning, TEXT("�� �̵� �Ÿ�: %f"), totDist);
    UE_LOG(LogTemp, Warning, TEXT("�� �̺�Ʈ �߻� Ƚ��: %d"), evCnt);
}

int32 AMyActor::step()
{
    return FMath::RandRange(0, 1); // 0 �Ǵ� 1�� ��ȯ
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
    if (RandomValue <= 50) // 50% Ȯ��
    {
        UE_LOG(LogTemp, Log, TEXT("�̺�Ʈ �߻�!"));
        return 1; // �̺�Ʈ �߻�
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("�̺�Ʈ �̹߻�"));
        return 0; // �̺�Ʈ �̹߻�
    }
}

void AMyActor::move()
{
    FVector2D current = start; // ���� ��ǥ (0,0)
    FVector2D previous = current;

    for (int32 i = 0; i < 10; ++i) // 10ȸ �̵�
    {
        int32 stepX = step(); // X�� �̵�
        int32 stepY = step(); // Y�� �̵�

        // ���� ����
        // `next`�� �� ��� �ȿ����� ��ȿ��
        FVector2D next(current.X + stepX, current.Y + stepY);

        if (next.X - current.X <= 2 && next.Y - current.Y <= 2)
        {
            float dist = distance(current, next); // �̵� �Ÿ� ���
            totDist += dist; // �� �̵� �Ÿ� ������Ʈ

            UE_LOG(LogTemp, Warning, TEXT("���� %d: ���� ��ǥ: (%f, %f), �̵� �Ÿ�: %f"), i + 1, next.X, next.Y, dist);

            // �̺�Ʈ �߻� ���� Ȯ��
            evCnt += createEvent();

            previous = current;
            current = next; // ���� ��ǥ�� ������Ʈ
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("�߸��� �̵�. �ٽ� �õ�."));
        }
    }
}