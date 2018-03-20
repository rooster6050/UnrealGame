// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#include "RTSHud.h"
#include "Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Public/CanvasItem.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"
#include "UnrealGame/Character/RTSBaseCharacter.h"

FVector2D ARTSHud::GetMousePos2D()
{
	float posX, posY;
	GetOwningPlayerController()->GetMousePosition(posX, posY);

	return FVector2D(posX, posY);
}

void ARTSHud::RenderLine(FVector2D startCoord, FVector2D endCoord)
{
	if (IsCanvasValid_WarnIfNot())
	{
		FCanvasLineItem LineItem(FVector2D(startCoord.X, startCoord.Y), FVector2D(endCoord.X, endCoord.Y));
		const FLinearColor LineColor(0.1f, 1.0f, 0.1f, 0.5f);
		const float LineThickness = 1.0f;
		LineItem.SetColor(LineColor);
		LineItem.LineThickness = LineThickness;
		Canvas->DrawItem(LineItem);
	}
}

void ARTSHud::HandleSelection()
{
	// Note: Runs every frame

	// If we have found units last frame: deselect them
	if (m_pFoundUnits.Num() > 0)
	{
		for (int i = 0; i < m_pFoundUnits.Num(); ++i)
		{
			m_pFoundUnits[i]->SetDeselected();
		}
	}
	m_pFoundUnits.Empty();

	// Find new actors in box for this frame

	bool bFindNonCollidingActors = false;
	bool bActorMustBeFullyEnclosed = false;
	GetActorsInSelectionRectangle<ARTSBaseCharacter>(m_vInitialPoint, m_vCurrentPoint, m_pFoundUnits, bFindNonCollidingActors, bActorMustBeFullyEnclosed);

	// Mark as selected
	if (m_pFoundUnits.Num() > 0)
	{
		for (int i = 0; i < m_pFoundUnits.Num(); ++i)
		{
			m_pFoundUnits[i]->SetSelected();
		}
	}
}

void ARTSHud::DrawHUD()
{
	if (m_bStartSelecting)
	{
		m_vCurrentPoint = GetMousePos2D();

		RenderLine(m_vInitialPoint, FVector2D(m_vInitialPoint.X, m_vCurrentPoint.Y));
		RenderLine(m_vInitialPoint, FVector2D(m_vCurrentPoint.X, m_vInitialPoint.Y));

		RenderLine(m_vCurrentPoint, FVector2D(m_vInitialPoint.X, m_vCurrentPoint.Y));
		RenderLine(m_vCurrentPoint, FVector2D(m_vCurrentPoint.X, m_vInitialPoint.Y));

		const FLinearColor boxColour(0.1f, 1.0f, 0.1f, 0.15f);
		DrawRect(boxColour, m_vInitialPoint.X, m_vInitialPoint.Y,
			m_vCurrentPoint.X - m_vInitialPoint.X,
			m_vCurrentPoint.Y - m_vInitialPoint.Y);

		HandleSelection();
	}
}


