// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

struct Message
{
	// Texture displayed | message to be displayed | time to display message for | Colour of font
	UTexture2D* tex;
	FString message;
	float time;
	FColor frontColor;

	Message()
	{
		// Set default time
		time = 5.f;
		frontColor = FColor::White;
	}

	Message(UTexture2D* iTex, FString iMessage, float iTime, FColor iFrontColor)
	{
		tex = iTex;
		message = iMessage;
		time = iTime;
		frontColor = iFrontColor;
	}

};

struct Icon
{
	FString name; UTexture2D* tex;
	
	Icon() { name = "UNKNOWN ICON"; tex = 0; }

	Icon(FString& iName, UTexture2D* iTex)
	{
		name = iName;
		tex = iTex;
	}
};

struct Widget
{
	Icon icon;
	//UClass* className;
	FVector2D pos, size;
	FString Name;

	Widget(Icon iicon, FString iName) // UClass *iClassName
	{
		icon = iicon;
		Name = iName;
		//className = iClassName;
	}

	// These are useful to determine whether a click was conceived within the icon area. 
	float left() { return pos.X; }
	float right() { return pos.X + size.X; }
	float top() { return pos.Y; }
	float bottom() { return pos.Y + size.Y; }

	bool hit(FVector2D v)
	{
		// +---+ top (0)
		// |   | 
		// +---+ bottom (2) (bottom > top)
		// L   R
		return v.X > left() && v.X < right() && v.Y > top() && v.Y < bottom();
	}
};

/**
 * 
 */
UCLASS()
class ADVENGAME_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	

public: 
	// The font used to render the text in the HUD.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
		UFont* hudFont;

	// override the defaul DrawHUD function
	virtual void DrawHUD() override;

	// T Array of messages available
	TArray<Message> messages;
	void addMessage(Message msg); // a function to add a message to display
	void DrawMessages(); // a function to draw message	
	void DrawHealthbar(); // a function to draw players health bar
	void DrawScoreBoard();

	// Draw the widgets to the HUD
	void DrawWidgets();

	// hold the information of the screen dimensions
	FVector2D dims;

	// TArray to hold information of the widgets coming in
	TArray<Widget> widgets;

	// Function to clear widgets
	void clearWidgets();

	// Add Widget to Inventory
	void addWidget(Widget widget);
	void addScore(int amount);

	// Detect and track the movement of the mouse
	void MouseMoved();

	// Widget pointer 
	Widget* heldWidget;

	int total;

};
