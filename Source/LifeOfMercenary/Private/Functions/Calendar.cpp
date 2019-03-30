// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOfMercenary/Public/Functions/Calendar.h"


int32 UCalendar::GetYear(int32 _Date)
{
	return ((_Date - 1) / (MaxDay * MaxMonth)) + 1;
}

int32 UCalendar::GetMonth(int32 _Date)
{
	return (((_Date - 1) / MaxDay) % MaxMonth) + 1;
}

int32 UCalendar::GetDay(int32 _Date)
{
	return ((_Date - 1) % MaxDay) + 1;
}

int32 UCalendar::ConvertFStoi(FString _Date)
{
	//예외처리
	if (FCString::Atoi(*_Date) > (MaxYear * 10000) + (MaxMonth * 100) + MaxDay || FCString::Atoi(*_Date) <= 10101) return 0;

	int day = FCString::Atoi(*(_Date.Right(2)));
	if (day > MaxDay || day < 0) return 0; //예외처리

	int month = FCString::Atoi(*((_Date.Right(4)).Left(2)));
	if (month > MaxMonth || month < 0) return 0; //예외처리

	int year = FCString::Atoi(*(_Date.LeftChop(4)));
	if (year > MaxYear || year < 0) return 0; //예외처리

	return ((year - 1) * 360) + ((month - 1) * 30) + day;
}

bool UCalendar::SetDate(int32& _Date, int32 _Day)
{
	//예외처리.
	if (_Day > MaxDay * MaxMonth * MaxYear || _Day < 0) return false;

	_Date = _Day;

	return true;
}

bool UCalendar::SetDateFromFString(int32& _Date, FString _SDate)
{
	int32 tempDate = ConvertFStoi(_SDate);

	if (tempDate >= 10101) {
		_Date = tempDate - 1;

		return true;
	}
	else {
		return false;
	}
}

bool UCalendar::AddDay(int32& _Date, int32 _Day)
{
	//예외처리.
	if (_Day + _Date > MaxDay * MaxMonth * MaxYear || _Day < 0) return false;

	_Date += _Day;

	return true;
}

bool UCalendar::AddMonth(int32& _Date, int32 _Month)
{
	//예외처리
	if ((_Month * MaxDay) + _Date > MaxDay * MaxMonth * MaxYear || _Month < 0) return false;

	_Date += _Month * MaxDay;

	return true;
}

bool UCalendar::AddYear(int32& _Date, int32 _Year)
{
	//예외처리
	if ((_Year * MaxDay * MaxMonth) + _Date > MaxDay * MaxMonth * MaxYear || _Year < 0) return false;

	_Date += _Year * MaxDay * MaxMonth;

	return true;
}

