// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Logging/LogMacros.h"

// Declare our game log categories
DECLARE_LOG_CATEGORY_EXTERN(LogBatstoi, Log, All);

// Simplify logging for our games
// ---

#define BTLOG(type, msg, ...) UE_LOG(LogBatstoi, type, TEXT(msg), ##__VA_ARGS__)

#define BTLOG_DISPLAY(msg, ...) UE_LOG(LogBatstoi, Display, TEXT(msg), ##__VA_ARGS__)
#define BTLOG_WARNING(msg, ...) UE_LOG(LogBatstoi, Warning, TEXT(msg), ##__VA_ARGS__)
#define BTLOG_ERROR(msg, ...) UE_LOG(LogBatstoi, Error, TEXT(msg), ##__VA_ARGS__)
#define BTLOG_FATAL(msg, ...) UE_LOG(LogBatstoi, Fatal, TEXT(msg), ##__VA_ARGS__)
