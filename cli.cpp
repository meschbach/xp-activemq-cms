/*
 * Copyright 2018 by Mark Eschbach.
 *
 * Basic C++ CMS example
 *
 * Compilation Notes:
 *
 * + You need to provide the include path for the CMS headers.
 * + Still need to test this...it was recreated from memory and the Apache examples.
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
    if( argc < 2 ) {
        cerr << "Usage: " << argv[0] << " connection-string" << endl;
        return -1;
    }

    try {
        ConnectionFactory connectionFactory( ConnectionFactory::createCMSConnectionFactory( argv[1] ) );
        Connection connection( connectionFactory.createConnection() );
        Session session( connection.createSession() );
        Queue queue(session);
        MessageConsumer consumer( session.createConsumer(queue) );

        bool done = false;
        while( !done ){
            Message message( consumer.receive() );
            const TextMessage message = dynamic_cast<const TextMessage>(message);
            if( message == null ){
                cout << "[Received not a text message]" << std::endl;
            } else {
                auto message = message.getText();
                if( message == "stop" ) {
                    done = true;
                }
                cout << "[Message]" << message << std::endl;
            }
        }
    } catch( CMSException &e ){
        cerr << e.printStackTrace() << endl;
    }
    return 0;
}
