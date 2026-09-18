#include<iostream>
#include<mysql_connection.h>
#include<mysql_driver.h>
#include<cppconn/exception.h>
#include<cppconn/resultset.h>
#include<cppconn/statement.h>
#include<cppconn/prepared_statement.h>

int main()
{
    try{
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection* con = driver->connect("tcp://127.0.0.1:3306","hcy","QWer!@34");

        con->setSchema("testdb");


        sql::Statement* stmt = con->createStatement();
        stmt->execute(
            "CREATE TABLE IF NOT EXISTS users("
            " id INT AUTO_INCREMENT PRIMARY KEY, "
            "name VARCHAR(50) NOT NULL, "
            "age INT"
            ")"
        );
        std::cout<<" table users create success"<<std::endl;

        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO users (name,age) VALUES (?, ?)"
        );
        pstmt->setString(1,"ZhangSan");
        pstmt->setInt(2,30);
        pstmt->executeUpdate();

        pstmt->setString(1,"LiSi");
        pstmt->setInt(2,25);
        pstmt->executeUpdate();

        std::cout<<"insert success"<<std::endl;

        sql::Statement* stmt2 = con->createStatement();
        sql::ResultSet* res = stmt2->executeQuery("SELECT id, name, age FROM users");

        while(res->next())
        {
            std::cout<<"ID: "<<res->getInt("id")
                        <<", Name: "<<res->getString("name")
                        <<", Age: "<<res->getInt("age")<<std::endl;
        }

        sql::PreparedStatement* updateStmt = con->prepareStatement(
            "UPDATE users SET age = ? WHERE name = ?"
        ); 

        updateStmt->setInt(1,31);
        updateStmt->setString(2,"Alice");
        updateStmt->executeUpdate();


        sql::PreparedStatement* delStmt = con->prepareStatement(
            "DELETE FROM users WHERE name = ?"
        ); 

        delStmt->setString(1,"ZhangSan");
        delStmt->executeUpdate();

        std::cout<<"update and delete success"<<std::endl;

        res = stmt2->executeQuery("SELECT id, name, age FROM users");
        while(res->next())
        {
            std::cout<<"ID: "<<res->getInt("id")
                        <<", Name: "<<res->getString("name")
                        <<", Age: "<<res->getInt("age")<<std::endl;
        }

        delete stmt;
        delete stmt2;
        delete pstmt;
        delete con;
        delete res;
        delete updateStmt;
        delete delStmt;

    }catch(sql::SQLException& e){
        std::cerr<<"mysql error: "<<e.what()<<std::endl;
        std::cerr<<"error nember: "<<e.getErrorCode()<<std::endl;
        return 1;
    }
    return 0;
}