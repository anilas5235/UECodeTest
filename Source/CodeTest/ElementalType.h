// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EElementalType : uint8
{
	ELEMET_None  UMETA(DisplayName = "None"),
	ELEMET_Fire  UMETA(DisplayName = "Fire"),
	ELEMET_Water UMETA(DisplayName = "Water"),
	ELEMET_Earth UMETA(DisplayName = "Earth"),
	ELEMET_Air   UMETA(DisplayName = "Air"),
};
