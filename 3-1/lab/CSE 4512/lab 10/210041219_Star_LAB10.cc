#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("task1");

int
main(int argc, char* argv[])
{
	CommandLine cmd(__FILE__);
	cmd.Parse(argc, argv);

	Time::SetResolution(Time::NS);
	LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    
	NodeContainer nodes;
	nodes.Create(4);
    
	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));
    
	NetDeviceContainer devices[3];
	for(int i = 0; i < 3; i++){
    	devices[i] = pointToPoint.Install( nodes.Get(0), nodes.Get(i+1) );
	}
    
	InternetStackHelper stack;
	stack.Install(nodes);
    
	Ipv4AddressHelper address[3];
	address[0].SetBase("192.9.19.0", "255.255.255.192");
	address[1].SetBase("192.9.19.64", "255.255.255.192");
	address[2].SetBase("192.9.19.128", "255.255.255.192");
    
	Ipv4InterfaceContainer interfaces[3];
	for(int i = 0; i < 3; i++){
    	interfaces[i] = address[i].Assign(devices[i]);
	}

	UdpEchoServerHelper echoServer(9);
    
	ApplicationContainer serverApps = echoServer.Install(nodes.Get(0));
    
	serverApps.Start(Seconds(1.0));
	serverApps.Stop(Seconds(10.0));
    
	for(int i = 0; i < 3; i++){
    	UdpEchoClientHelper echoClient(interfaces[i].GetAddress(0), 9);
    	echoClient.SetAttribute("MaxPackets", UintegerValue(2));
    	echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    	echoClient.SetAttribute("PacketSize", UintegerValue(1024));
   	 
    	ApplicationContainer clientApps = echoClient.Install(nodes.Get(i+1));
    	clientApps.Start(Seconds(i * 2 + 2.0));
    	clientApps.Stop(Seconds(10.0));
	}
    
    
    
	for(int i = 0; i < 3; i++){
    	UdpEchoServerHelper echoServer(9);
    
    	ApplicationContainer serverApps = echoServer.Install(nodes.Get(i+1));
    
    	serverApps.Start(Seconds(1.0));
    	serverApps.Stop(Seconds(20.0));
	}
    
	for(int i = 0; i < 3; i++){
    	UdpEchoClientHelper echoClient(interfaces[i].GetAddress(1), 9);
    	echoClient.SetAttribute("MaxPackets", UintegerValue(2));
    	echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    	echoClient.SetAttribute("PacketSize", UintegerValue(1024));
   	 
    	ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
    	clientApps.Start(Seconds(i * 2 + 10.0));
    	clientApps.Stop(Seconds(20.0));
	}
    
	Simulator::Run();
	Simulator::Destroy();
	return 0;
    
}

