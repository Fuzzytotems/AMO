// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaMastersOnline.h"
#include "CombatLogger.h"

void UCombatLogger::LogString(FString stringOutput)
{
	stringsToLog.push(std::string(TCHAR_TO_UTF8(*stringOutput)));
}

void UCombatLogger::ChangeLoggingStatus(bool isLogging)
{
	if (isLogging)
	{
		if (!logFile.is_open())
		{
			logFile.open(logName, ios::out | ios::app);
		}
	}
	else
	{
		if (logFile.is_open())
		{
			logFile.close();
		}
	}
	currentlyWriting = false;
}

void UCombatLogger::BeginWriting()
{
	if (!stringsToLog.empty() && logFile.is_open() && !currentlyWriting)
	{
		currentlyWriting = true;
		WriteToDisk();
	}
}

void UCombatLogger::WriteToDisk()
{
	while (!stringsToLog.empty() && logFile.is_open())
	{
		logFile << stringsToLog.front().c_str() << '\n';
		stringsToLog.pop();
	}
	currentlyWriting = false;
}

bool UCombatLogger::HasContents()
{
	return !stringsToLog.empty();
}

void UCombatLogger::SetLogName(FString newName)
{
	logName = TCHAR_TO_UTF8(*newName);
	logName.append(".txt");
}