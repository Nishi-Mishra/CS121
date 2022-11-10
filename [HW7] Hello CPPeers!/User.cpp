/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "User.h"

using std::string;
using std::vector;

/*userName is empty
• userName does not start with a letter ‘a’ - ‘z’
• userName contains uppercase letters ‘A’ - ‘Z’
o In other words it should be all lowercase letters
*/
User::User(string userName) : userName{ userName }, userPosts{} {
  // TODO(student): implement constructor checks
	if (userName.empty())
		throw std::invalid_argument("Username is empty"); 
	if(!isalpha(userName.at(0)))
		throw std::invalid_argument("Username doesn't start w/ letter");
	
	for (char c : userName) {
		if (isupper(c))
			throw std::invalid_argument("Username contains a capital letter");
	}

}

string User::getUserName() {
  // TODO(student): implement getter
	return userName; 
}

vector<Post*>& User::getUserPosts() {
  // TODO(student): implement getter
	return userPosts; 
}

void User::addUserPost(Post* post) {
  // TODO(student): add post to user posts
	if (post == nullptr)
		throw std::invalid_argument("Post passed into addUserPost was nullptr"); 

	userPosts.push_back(post); 
}
