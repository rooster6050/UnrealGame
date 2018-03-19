// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StaticHelpers.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAME_API UStaticHelpers : public UObject
{
	GENERATED_BODY()

protected:
	UStaticHelpers();

public:

	static FORCEINLINE bool IsValid(class AActor* pActor)
	{
		if (!pActor || !pActor->IsValidLowLevel()) return false;
		return true;
	}
};
