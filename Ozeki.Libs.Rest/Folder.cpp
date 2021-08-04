#include "pch.h"
#include "Folder.h"

std::ostream& operator<<(std::ostream& os, const Folder& folder)
{
	switch (folder)
	{
	case Inbox:
		return os << "inbox";
	case Outbox:
		return os << "outbox";
	case Sent:
		return os << "sent";
	case NotSent:
		return os << "notsent";
	case Deleted:
		return os << "deleted";
	default:
		return os << "";
	}
}