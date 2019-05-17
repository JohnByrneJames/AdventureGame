// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "PlayerActor.h"
#include "Kismet/GameplayStatics.h"

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
	// Now Draw your stuff on the HUD
	// for example a blue line
	//DrawLine(200, 300, 400, 500, FLinearColor::Blue);
	// Or some text in the middle of the screen
	//float ScreenX = 50.0f;
	//float ScreenY = 50.0f;
	
	float TextScale = 2.0f;
	//bool bDontScale = false;
	//DrawText("Hello World", FColor::White, ScreenX, ScreenY, hudFont,
	//	TextScale, bDontScale);

	DrawMessages();
	DrawHealthbar();
	DrawWidgets();
	DrawScoreBoard();
	dims.X = Canvas->SizeX;
	dims.Y = Canvas->SizeY;
}

void AMyHUD::addMessage(Message msg)
{
	messages.Add(msg);
}

void AMyHUD::DrawMessages()
{
	// Iterate from back to front thru the list, so if we remove
	// an item while iterating, there won't be any problems
	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		// draw the background box the right size for the message
		float ow, oh, pad = 10.f;
		GetTextSize(messages[c].message, ow, oh, hudFont, 3.f); // Message[#].message, out-width, out-height, font, font-scale

		float messageH = oh + 2 * pad;
		float messageT = oh + 5 * pad;
		float x = 0, y = c * messageH;

		DrawRect(FLinearColor::Transparent, x, 510.f, Canvas->SizeX, messageH);

		DrawText(messages[c].message, messages[c].frontColor, 70.f, 510.f, hudFont, 1.5f);

		DrawTexture(messages[c].tex, x, 510.f, messageH, messageH, 0, 0, 1, 1);

		// reduce lifetime by the time that passed since last frame
		messages[c].time -= GetWorld()->GetDeltaSeconds();
		// if the message's time is up, remove it
		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}

	}
}

void AMyHUD::DrawHealthbar()
{
	// Draw Healthbar - cast to APlayerActor to check for health loss
	APlayerActor *avatar = Cast<APlayerActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Properties of the health bar, including size and width
	float barWidth = 200, barHeight = 50, barPad = 10, barMargin = 50;
	float percHp = avatar->Hp / avatar->MaxHp;
	DrawRect(FLinearColor::Gray, Canvas->SizeX - barWidth - barPad - barMargin,
		Canvas->SizeY - barHeight - barPad - barMargin, barWidth + 2 * barPad, 
		barHeight + 2 * barPad);
	DrawRect(FLinearColor(1 - percHp, percHp, 0, 1),
		Canvas->SizeX - barWidth - barMargin,
		Canvas->SizeY - barHeight - barMargin, barWidth*percHp, barHeight);

}

void AMyHUD::DrawWidgets()
{
	for (int c = 0; c < widgets.Num(); c++)
	{
		DrawTexture(widgets[c].icon.tex, widgets[c].pos.Y, widgets[c].pos.X,
			widgets[c].size.X, widgets[c].size.Y, 0, 0, 1, 1);

		DrawText(widgets[c].icon.name, FLinearColor::Black, widgets[c].pos.Y, widgets[c].pos.X,
			hudFont,2.f, false);
	}
}

void AMyHUD::addWidget(Widget widget)
{
	// find the pos of the widget based on the grid.
	// draw the icons..
	FVector2D start(200, 200), pad(12, 12);
	widget.size = FVector2D(100, 100);
	widget.pos = start;

	// compute the position here
	for (int c = 0; c < widgets.Num(); c++)
	{
		// Move the position to the right a bit
		widget.pos.X += widget.size.X + pad.X;

		// if there is no more room to the right then
		// jump to the next line
		if (widget.pos.X + widget.size.X > dims.X)
		{
			widget.pos.X = start.X;
			widget.pos.Y = widget.size.Y + pad.Y;
		}
	}

	widgets.Add(widget);
}

// MouseMoved() function is called through the class that golds the controller (mouse), this will happen in the
// Yaw() and Pitch() functions as these deal with the mouse movement in the game.
void AMyHUD::MouseMoved()
{
	// This function checks for the distance the mouse moved between the last and current 
	// frame (tick) and moves the widget by that amount.
	APlayerController *PController = GetWorld()->GetFirstPlayerController();

	float time = PController->GetInputKeyTimeDown(EKeys::LeftMouseButton);

	// This static lastMouse variable is used to store and remember this last position (lastMouse)
	static FVector2D lastMouse;
	FVector2D thisMouse, dMouse;
	PController->GetMousePosition(thisMouse.Y, thisMouse.X);
	dMouse = thisMouse - lastMouse;

	if (time > 0.f && heldWidget)
	{
		// the mouse is being held down.
		// move the widget by displacement amount
		heldWidget->pos.Y += dMouse.X;
		heldWidget->pos.X += dMouse.Y; // y inverted
	}
	
	lastMouse = thisMouse;
}

void AMyHUD::addScore(int n)
{
	total += n;
}

void AMyHUD::DrawScoreBoard()
{
	DrawText(FString("SCORE : ") + FString::FromInt(total), FColor::Black, 20.f, 50.f, hudFont, 2.0f);
}

void AMyHUD::clearWidgets()
{
	widgets.Empty();
}