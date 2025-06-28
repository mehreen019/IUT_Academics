#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

// Default Network Topology
//
//       10.1.1.0
// n0 -------------- n1   n2   n3   n4
//    point-to-point  |    |    |    |
//                    ================
//                      LAN 10.1.2.0

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SecondScriptExampleForLab11");

int
main(int argc, char* argv[])
{
    bool verbose = true;
    uint32_t nCsma = 3;

    CommandLine cmd(__FILE__);
    cmd.AddValue("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
    cmd.AddValue("verbose", "Tell echo applications to log if true", verbose);

    cmd.Parse(argc, argv);

    if (verbose)
    {
        LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
        LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }


    NodeContainer p2pNodes;
    p2pNodes.Create(1);

    NodeContainer engNodes;
    engNodes.Add(p2pNodes.Get(0));
    engNodes.Create(3);
    
    NodeContainer markNodes;
    markNodes.Add(p2pNodes.Get(0));
    markNodes.Create(3);
    
    NodeContainer saleNodes;
    saleNodes.Add(p2pNodes.Get(0));
    saleNodes.Create(3);
    
    NodeContainer adminNodes;
    adminNodes.Add(p2pNodes.Get(0));
    adminNodes.Create(3);
    
    NodeContainer manageNodes;
    manageNodes.Add(p2pNodes.Get(0));
    manageNodes.Create(3);

    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));


    CsmaHelper csma;
    csma.SetChannelAttribute("DataRate", StringValue("100Mbps"));
    csma.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6560)));

    NetDeviceContainer engDevices;
    engDevices = csma.Install(engNodes);
    
    NetDeviceContainer markDevices;
    markDevices = csma.Install(markNodes);
    
    NetDeviceContainer saleDevices;
    saleDevices = csma.Install(saleNodes);
    
    NetDeviceContainer adminDevices;
    adminDevices = csma.Install(adminNodes);
    
    NetDeviceContainer manageDevices;
    manageDevices = csma.Install(manageNodes);

    InternetStackHelper stack;
    stack.Install(p2pNodes.Get(0));
    for(int i=1; i<4 ; i++){
        stack.Install(engNodes.Get(i));
        stack.Install(markNodes.Get(i));
        stack.Install(saleNodes.Get(i));
        stack.Install(adminNodes.Get(i));
        stack.Install(manageNodes.Get(i));
    }

    Ipv4AddressHelper address;

    address.SetBase("192.168.20.0", "255.255.255.192");
    Ipv4InterfaceContainer markInterfaces;
    markInterfaces = address.Assign(markDevices);
    
    address.SetBase("192.168.20.64", "255.255.255.192");
    Ipv4InterfaceContainer saleInterfaces;
    saleInterfaces = address.Assign(saleDevices);
    
    address.SetBase("192.168.20.128", "255.255.255.224");
    Ipv4InterfaceContainer engInterfaces;
    engInterfaces = address.Assign(engDevices);
    
    address.SetBase("192.168.20.160", "255.255.255.224");
    Ipv4InterfaceContainer adminInterfaces;
    adminInterfaces = address.Assign(adminDevices);
    
    address.SetBase("192.168.20.192", "255.255.255.224");
    Ipv4InterfaceContainer manageInterfaces;
    manageInterfaces = address.Assign(manageDevices);
    
    
    
    

    UdpEchoServerHelper echoServer(9);

    ApplicationContainer serverApps = echoServer.Install(markNodes.Get(1));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(markInterfaces.GetAddress(1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(1));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(engNodes.Get(1));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}

