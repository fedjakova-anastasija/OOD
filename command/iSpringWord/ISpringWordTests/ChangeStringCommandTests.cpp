#include "pch.h"
#include "../ISpringWord/ChangeStringCommand.h"

TEST_CASE("Can be executed")
{ 
	std::string firstString = "first string";
	std::string secondString = "second string";
	auto changeString = std::make_unique<CChangeStringCommand>(firstString, secondString);
	changeString->Execute();
	REQUIRE(firstString == secondString);
}

TEST_CASE("Can be unexecuted")
{
	std::string firstString = "first string";
	std::string secondString = "second string";
	auto changeString = std::make_unique<CChangeStringCommand>(firstString, secondString);
	changeString->Execute();		
	changeString->Unexecute();
	REQUIRE_FALSE(firstString == secondString);
}