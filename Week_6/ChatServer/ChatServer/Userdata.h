#pragma once
#include<vector>
#include<iostream>
#include<string>
#include "ClientSocket.h"


struct userinfo
{
	char cUserName[20];
	char csMsg[100];
};

struct channel {
	std::string sName;
	std::vector<CClientSocket*> channelClient;
};