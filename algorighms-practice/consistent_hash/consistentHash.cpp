#include<stdio.h>
#include<string>
#include<stdint.h>
#include<map>
#include<vector>

extern unsigned int stringHashFunction(std::string s);
void setHashFunctionSeedInt(uint32_t seed);

std::string to_string(unsigned int number)
{
    std::string s;
	if(number==0)
		s="0";
    while(number)
    {   
        char c=(number%10)+'0';
        s=c+s;
        number=number/10;                                                                                                  
    }
    return s;
}

void test_stringHash()
{
	// uint8_t seed=123456;
	// setHashFunctionSeedInt(seed);
	
	std::string s="wangjing";
	unsigned int hashValue=stringHashFunction(s);
	printf("%s hashValue %u\n", s.c_str(), hashValue);
}

class ConsistentHash{
public:
	void initNodes(std::vector<std::string> servers, unsigned int virtualNodeCnt);
	std::string getNode(std::string key);

private:
    std::string realNode(const std::string& node);

	std::map<unsigned int, std::string> nodes;
	
};

void ConsistentHash::initNodes(std::vector<std::string> servers, unsigned int vncnt)
{
	nodes.clear();
	
	for(int i=0; i<servers.size(); ++i)
	{
		std::string serverName=servers[i];
		for(unsigned int j=0; j<vncnt; ++j)
		{
			std::string vnodeName=serverName+"_vn"+to_string(j); // std::to_string(j);
			unsigned int nodeHashValue=stringHashFunction(vnodeName);
			//nodes[nodeHashValue]=vnodeName;
            nodes[nodeHashValue]=serverName;
			printf("insert node %u —— %s\n", nodeHashValue, vnodeName.c_str());
		}
	}
}

std::string ConsistentHash::getNode(std::string key)
{
	if(nodes.empty())
		return "";
	unsigned int hashValue=stringHashFunction(key);
	printf("key %s hashValue %u\n", key.c_str(), hashValue);
	std::map<unsigned int, std::string>::iterator itr=nodes.lower_bound(hashValue);
	std::string vnode;
	if(itr==nodes.end())
		vnode=nodes.begin()->second;
	else
		vnode=itr->second;
	return realNode(vnode);
//	std::string::size_type p=vnode.find('_');
//	return vnode.substr(0, p);
}

std::string ConsistentHash::realNode(const std::string& node)
{
    return node;
}

ConsistentHash g_ch;

void test_consistentHash()
{
	std::vector<std::string> servers;
	servers.push_back("192.168.11.1:9000");
	servers.push_back("192.168.11.2:9000");
	servers.push_back("192.168.11.3:9000");
	servers.push_back("192.168.11.4:9000");
	servers.push_back("192.168.11.5:9000");
	
	g_ch.initNodes(servers, 10);
	
	std::vector<std::string> keysVec;
	keysVec.push_back("wangjing");
	keysVec.push_back("norah");
	keysVec.push_back("jill");
	keysVec.push_back("elaine");
	keysVec.push_back("jenny");
	keysVec.push_back("spencer");
	keysVec.push_back("adam");
	keysVec.push_back("corner");
	keysVec.push_back("julie baker");
	std::string key;
	std::string server;
	for(int i=0; i<keysVec.size(); ++i)
	{
		key=keysVec[i];
		server=g_ch.getNode(key);
		printf("key %s get server %s\n", key.c_str(), server.c_str());
	}
}

int main()
{
	{
		test_stringHash();
	}
	
	{
		test_consistentHash();
	}
	
	return 0;
}
