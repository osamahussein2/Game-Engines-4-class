#include "Debug.h"

Debug::MessageType Debug::CurrentSev = MessageType::TYPE_NONE;
std::string Debug::OutputName = "";

void Debug::OnCreate(const std::string& name_)
{
	OutputName = name_ + ".txt"; // OutputName is equal to the "name".txt (again, could be any name we declare)
	std::ofstream out; // Declares the variable for file name
	out.open(OutputName.c_str(), std::ios::out); // This function is to open the file we want
	out.close(); // Close the file
	CurrentSev = MessageType::TYPE_INFO;
}

void Debug::SetServerity(MessageType type_)
{
	CurrentSev = type_;
}

void Debug::Info(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_INFO, "[INFO]: " + message_, fileName_, line_);
}

void Debug::Trace(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_TRACE, "[TRACE]: " + message_, fileName_, line_);
}

void Debug::Warning(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_WARNING, "[WARNING]: " + message_, fileName_, line_);
}

void Debug::Error(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_ERROR, "[ERROR]: " + message_, fileName_, line_);
}

void Debug::FatalError(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_FATAL_ERROR, "[FATAL ERROR]: " + message_, fileName_, line_);
}

void Debug::Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_)
{
	if (type_ <= CurrentSev && CurrentSev > MessageType::TYPE_NONE) {
		std::ofstream out;
		out.open(OutputName.c_str(), std::ios::app | std::ios::out); // This function is to open the file we want
		out << message_ << " in: " << fileName_ << " on line: " << line_ << std::endl;
		out.flush(); // This will flush out the buffer to make sure there's no buffer before we close the file
		out.close(); // Close the file
	}
}
