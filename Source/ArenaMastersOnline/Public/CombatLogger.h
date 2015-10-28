// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>
#include <fstream>
#include "Object.h"
#include "MovieSceneBoolTrackInstance.h"
#include <queue>
#include "CombatLogger.generated.h"
using namespace std;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ARENAMASTERSONLINE_API UCombatLogger : public UObject
{
	GENERATED_BODY()	
public:
	UFUNCTION(BlueprintCallable, Category = LoggingSystems)
		void LogString(FString stringOutput);

	UFUNCTION(BlueprintCallable, Category = LoggingSystems)
		void ChangeLoggingStatus(bool isLogging);

	UFUNCTION(BlueprintCallable, Category = LoggingSystems)
		void BeginWriting();

	UFUNCTION(BlueprintCallable, Category = LoggingSystems)
		bool HasContents();

	UFUNCTION(BlueprintCallable, Category = LoggingSystems)
		void SetLogName(FString newName);

	void WriteToDisk();
private:
	std::string logName;
	std::ofstream logFile;
	std::queue <std::string> stringsToLog;
	bool currentlyWriting = false;
};