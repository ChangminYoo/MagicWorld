#pragma once
#include <iostream>

// boost asio 관련 헤더
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

#include "protocol.h"
//#include "Player.h"
//#include "Database\CTextTest.h"

const char SERVERIP[] = "127.0.0.1";
const unsigned short PORT = 31400;

using namespace std;

//io_service는 IO와 통신을 위해서사용 - 전역 하나만 있어도 된다
extern boost::asio::io_service g_io_service;


//extern CTextTest g_database;
