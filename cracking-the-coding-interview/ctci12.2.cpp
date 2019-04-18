#include<vector>
#include<string>

class Person;
class Machine;
class Server;

class Server{
public:
	std::vector<shared_ptr<Machine> > machines;
	
	Person* lookUpFriend(int machineID, int ID);
	Machine* lookUpMachine(int machineID);
};

class Machine{
public:
	int machineID;
	//std::vector<shared_ptr<Person> > persons;
	Graph *persons;
	
};


struct AdjNode{
	int idx;
	int weight;
	struct AdjNode* nextEdge;
	
	struct PersonInfo{
		int ID;
		std::string info;
		//int machineID;
	};
	
	AdjNode(int i, int w):idx(i),weight(w),nextEdge(NULL){}
};

struct VertexNode{
	int data;
	struct AdjNode* firstEdge;
	
	VertexNode():data(-1),firstEdge(NULL){}
};

class AdjGraph: public Graph{
private:
	enum { N=100 };
	VertexNode graph[N];
	//int nvex, nedge;
	
public:
	AdjGraph();
	~AdjGraph();
	//bool hasPathDFS(int a, int b);
	
	virtual void Init();
	
	virtual int FirstNeighbor(int v);
	virtual int NextNeighbor(int v, int w);
};

// class Person{
// private:
	// int ID;
	// std::string info;
	// int machineID;
	// Server* server;
	// std::vector<int> friends;
	
// public:
	// Person(int ID, int machineID);
	// ~Person();

	// std::string getInfo() { return info; }
	// void setInfo(const std::string& if) { info=if; }
	// void getFriends(std::vector<int> &friends);
	// int getID() { return ID; }
	// int getMachinedID() { return machineID; }
	// void addFriend(int id);
	
// };

// Person::Person(int id, int mid):ID(id),machineID(mid)
// {}

// void Person::getFriends(std::vector<int> &fds)
// {
	// fds.clear();
	// fds.reserve(friends.size());
	// fds.assign(friends.begin(), friends.end());
// }

// void Person::addFriend(int id)
// {
	// friends.push_back(id);
// }

void Server::lookUpFriend(int machineID, int id)
{
	
}
