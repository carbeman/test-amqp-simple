#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <boost/thread.hpp>
#include <queue>

using namespace std;
using namespace AmqpClient;

std::queue<int> coda;

void send()
{
    //string broker = "eureka.phy.a-tono.net";
    //string broker = "rabbitmq-clt-3.vm.a-tono.net";
    //string broker = "10.1.3.9";
    string broker = "10.41.3.51";
    //string broker = "10.50.2.2"; //"rabbitmq.eu.aws.a-tono.net";
    string exchange = "amq.direct";
    string key = "ema.test";
    string testo = "Messaggio di test";

    Channel::ptr_t channel1;
    channel1 = Channel::Create(broker.c_str());

    BasicMessage::ptr_t message = BasicMessage::Create();
    message->Body(testo);

    while(!coda.empty())
    {
        cout << "Invio messaggi... "<< endl;
        coda.pop();
        channel1->BasicPublish(exchange, key, message);
    }
       cout << "thread " << boost::this_thread::get_id() <<  " finito" << endl;
}

int main()
{

    for ( int i = 0; i < 1; ++i)
    {
        coda.push(i);
    }

    cout << "coda piena, start dei produttori" << endl;

    boost::thread_group tg;

    for ( int j = 0; j < 1; ++j)
        tg.create_thread(send);

    tg.join_all();

    return 0;
}
