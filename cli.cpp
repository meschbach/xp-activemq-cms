/*
 * Copyright 2018 by Mark Eschbach.
 *
 * Basic C++ CMS example
 *
 * Compilation Notes:
 *
 * + You need to provide the include path for the CMS headers.
 */

//libstdc++
#include<iostream>
#include<iomanip>
#include<memory>

//CMS
#include <activemq/library/ActiveMQCPP.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>

using namespace std;
using namespace cms;

int main( int argc, char** argv ){
    if( argc < 3 ) {
        cerr << "Usage: " << argv[0] << " connection-string" << endl;
        return -1;
    }
		auto argument = argv[1];
		auto queueName = argv[2];

		activemq::library::ActiveMQCPP::initializeLibrary();

    try {
        ConnectionFactory* connectionFactory = ConnectionFactory::createCMSConnectionFactory( argument );
        Connection* connection = connectionFactory->createConnection();
        Session* session = connection->createSession();
        Queue* queue = session->createQueue( queueName );
        MessageConsumer* consumer = session->createConsumer(queue);

        bool done = false;
        while( !done ){
            Message* unknownMessageType = consumer->receive();
            const TextMessage* message = dynamic_cast<const TextMessage*>(unknownMessageType);
            if( message == NULL ){
                cout << "[Received not a text message]" << std::endl;
            } else {
                auto body = message->getText();
                if( body == "stop" ) {
                    done = true;
                }
                cout << "[Message]" << body << std::endl;
            }
        }
    } catch( CMSException &e ){
			e.printStackTrace();
    }
    return 0;
}

