
#include "User.h"

User::User() {
}

User::User(int id, std::string name) : id(id), name(name) {
}

User::~User() {
}

bool User::operator==(const User& other) {
	return id == other.id;
}

