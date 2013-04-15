
#ifndef USER_H_
#define USER_H_

#include <string>
#include <ctime>

class User {
public:
	User();
	User(int id, std::string name);
	virtual ~User();

	int getId() const {return id;}
	std::string getName() const {return name;}
	time_t getLastPinged() const { return lastPinged; }

	void setId(int id) { this->id = id; }
	void setName(std::string name) { this->name = name; }
	void setLastPinged(time_t t) { this->lastPinged = t; }

	bool operator==(const User& other);

private:
	int id;
	std::string name;
	time_t lastPinged;
};

#endif /* USER_H_ */
