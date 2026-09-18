#include<iostream>
#include<mysql_connection.h>
#include<mysql_driver.h>
#include<cppconn/exception.h>
#include<cppconn/resultset.h>
#include<cppconn/statement.h>

int main()
{
    try{
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection* con = driver->connect("tcp://127.0.0.1:3306","hcy","QWer!@34");

        con->setSchema("testdb");

        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT VERSION() AS v");

        if(res->next())
        {
            std::cout<<"connect success, mysql version : "<<res->getString("v")<<std::endl;

        }

        delete res;
        delete stmt;
        delete con;
    }catch(sql::SQLException& e){
        std::cerr<<"mysql error: "<<e.what()<<std::endl;
        std::cerr<<"error nember: "<<e.getErrorCode()<<std::endl;
        return 1;
    }
    return 0;
}