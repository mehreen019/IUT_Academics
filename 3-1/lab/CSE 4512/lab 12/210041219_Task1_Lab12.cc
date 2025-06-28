#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-apps-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-routing-table-entry.h"
#include "ns3/ipv4-static-routing-helper.h"
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

NS_LOG_COMPONENT_DEFINE("RipSimpleRoutingLab12");

void
TearDownLink(Ptr<Node> nodeA, Ptr<Node> nodeB, uint32_t interfaceA, uint32_t interfaceB)
{
    nodeA->GetObject<Ipv4>()->SetDown(interfaceA);
    nodeB->GetObject<Ipv4>()->SetDown(interfaceB);
}

int
main(int argc, char* argv[])
{
    bool verbose = false;
    bool printRoutingTables = false;
    bool showPings = false;
    std::string SplitHorizon("PoisonReverse");

    CommandLine cmd(__FILE__);
    cmd.AddValue("verbose", "turn on log components", verbose);
    cmd.AddValue("printRoutingTables",
                 "Print routing tables at 30, 60 and 90 seconds",
                 printRoutingTables);
    cmd.AddValue("showPings", "Show Ping reception", showPings);
    cmd.AddValue("splitHorizonStrategy",
                 "Split Horizon strategy to use (NoSplitHorizon, SplitHorizon, PoisonReverse)",
                 SplitHorizon);
    cmd.Parse(argc, argv);

    if (verbose)
    {
        LogComponentEnableAll(LogLevel(LOG_PREFIX_TIME | LOG_PREFIX_NODE));
        LogComponentEnable("RipSimpleRouting", LOG_LEVEL_INFO);
        LogComponentEnable("Rip", LOG_LEVEL_ALL);
        LogComponentEnable("Ipv4Interface", LOG_LEVEL_ALL);
        LogComponentEnable("Icmpv4L4Protocol", LOG_LEVEL_ALL);
        LogComponentEnable("Ipv4L3Protocol", LOG_LEVEL_ALL);
        LogComponentEnable("ArpCache", LOG_LEVEL_ALL);
        LogComponentEnable("Ping", LOG_LEVEL_ALL);
    }

    if (SplitHorizon == "NoSplitHorizon")
    {
        Config::SetDefault("ns3::Rip::SplitHorizon", EnumValue(Rip::NO_SPLIT_HORIZON));
    }
    else if (SplitHorizon == "SplitHorizon")
    {
        Config::SetDefault("ns3::Rip::SplitHorizon", EnumValue(Rip::SPLIT_HORIZON));
    }
    else
    {
        Config::SetDefault("ns3::Rip::SplitHorizon", EnumValue(Rip::POISON_REVERSE));
    }

    NS_LOG_INFO("Create nodes.");
    
    NodeContainer p2pNodes;
    p2pNodes.Create(5);

    NodeContainer engNodes;
    engNodes.Add(p2pNodes.Get(0));
    engNodes.Create(3);
    
    NodeContainer markNodes;
    markNodes.Add(p2pNodes.Get(1));
    markNodes.Create(3);
    
    NodeContainer saleNodes;
    saleNodes.Add(p2pNodes.Get(2));
    saleNodes.Create(3);
    
    NodeContainer adminNodes;
    adminNodes.Add(p2pNodes.Get(3));
    adminNodes.Create(3);
    
    NodeContainer manageNodes;
    manageNodes.Add(p2pNodes.Get(4));
    manageNodes.Create(3);
    
    Ptr<Node> central = CreateObject<Node>();
    Names::Add("CentralNode", central);
    
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

    NetDeviceContainer p2pDevices[4];
    for(int i=0; i<4 ; i++){
        p2pDevices[i] = pointToPoint.Install(p2pNodes.Get(i), p2pNodes.Get(i + 1));   
    }
    
    NetDeviceContainer extraDevices[2];
    extraDevices[0] = pointToPoint.Install(p2pNodes.Get(2), central);
    extraDevices[1] = pointToPoint.Install(p2pNodes.Get(3), central);

    NS_LOG_INFO("Create channels.");
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
    
    NS_LOG_INFO("Create IPv4 and routing");
    RipHelper ripRouting;
    
    for(int i=0; i<5 ; i++){
        ripRouting.ExcludeInterface(p2pNodes.Get(i), 0);
    }
    
    ripRouting.SetInterfaceMetric(central, 0, 10);
    ripRouting.SetInterfaceMetric(p2pNodes.Get(2), 3, 10);
    
    ripRouting.SetInterfaceMetric(central, 1, 10);
    ripRouting.SetInterfaceMetric(p2pNodes.Get(3), 3, 10);
    
    Ipv4ListRoutingHelper listRH;
    listRH.Add(ripRouting, 0);

    InternetStackHelper stack1;
    stack1.SetIpv6StackInstall(false);
    stack1.SetRoutingHelper(listRH);
    
    for(int i=0; i<5 ; i++){
        stack1.Install(p2pNodes.Get(i));
    }
    
    stack1.Install(central);
    
    InternetStackHelper stack2;
    stack2.SetIpv6StackInstall(false);
    
    for(int i=1; i<4 ; i++){
        stack2.Install(engNodes.Get(i));
        stack2.Install(markNodes.Get(i));
        stack2.Install(saleNodes.Get(i));
        stack2.Install(adminNodes.Get(i));
        stack2.Install(manageNodes.Get(i));
    }

    NS_LOG_INFO("Assign IPv4 Addresses.");
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
    
    address.SetBase("192.168.20.224", "255.255.255.252");
    Ipv4InterfaceContainer p2pInterfaces0;
    p2pInterfaces0 = address.Assign(p2pDevices[0]);
    
    address.SetBase("192.168.20.228", "255.255.255.252");
    Ipv4InterfaceContainer p2pInterfaces1;
    p2pInterfaces1 = address.Assign(p2pDevices[1]);
    
    address.SetBase("192.168.20.232", "255.255.255.252");
    Ipv4InterfaceContainer p2pInterfaces2;
    p2pInterfaces2 = address.Assign(p2pDevices[2]);
    
    address.SetBase("192.168.20.236", "255.255.255.252");
    Ipv4InterfaceContainer p2pInterfaces3;
    p2pInterfaces3 = address.Assign(p2pDevices[3]);
    
    address.SetBase("192.168.20.240", "255.255.255.252");
    Ipv4InterfaceContainer extraInterfaces1;
    extraInterfaces1 = address.Assign(extraDevices[0]);
    
    address.SetBase("192.168.20.244", "255.255.255.252");
    Ipv4InterfaceContainer extraInterfaces2;
    extraInterfaces2 = address.Assign(extraDevices[1]);
    
    for(int i=1; i<4 ; i++){
        Ptr<Ipv4StaticRouting> staticRouting;
        staticRouting = Ipv4RoutingHelper::GetRouting<Ipv4StaticRouting>(
            engNodes.Get(i)->GetObject<Ipv4>()->GetRoutingProtocol());
        staticRouting->SetDefaultRoute("192.168.20.129", 1);
        
        staticRouting = Ipv4RoutingHelper::GetRouting<Ipv4StaticRouting>(
            markNodes.Get(i)->GetObject<Ipv4>()->GetRoutingProtocol());
        staticRouting->SetDefaultRoute("192.168.20.1", 1);
        
        staticRouting = Ipv4RoutingHelper::GetRouting<Ipv4StaticRouting>(
            saleNodes.Get(i)->GetObject<Ipv4>()->GetRoutingProtocol());
        staticRouting->SetDefaultRoute("192.168.20.65", 1);
        
        staticRouting = Ipv4RoutingHelper::GetRouting<Ipv4StaticRouting>(
            adminNodes.Get(i)->GetObject<Ipv4>()->GetRoutingProtocol());
        staticRouting->SetDefaultRoute("192.168.20.161", 1);
        
        staticRouting = Ipv4RoutingHelper::GetRouting<Ipv4StaticRouting>(
            manageNodes.Get(i)->GetObject<Ipv4>()->GetRoutingProtocol());
        staticRouting->SetDefaultRoute("192.168.20.193", 1);
    }
    
    if (printRoutingTables)
    {
        Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper>(&std::cout);

        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(30.0), p2pNodes.Get(0), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(30.0), p2pNodes.Get(1), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(30.0), p2pNodes.Get(2), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(30.0), p2pNodes.Get(3), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(30.0), p2pNodes.Get(4), routingStream);

        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(60.0), p2pNodes.Get(0), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(60.0), p2pNodes.Get(1), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(60.0), p2pNodes.Get(2), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(60.0), p2pNodes.Get(3), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(60.0), p2pNodes.Get(4), routingStream);

        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(90.0), p2pNodes.Get(0), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(90.0), p2pNodes.Get(1), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(90.0), p2pNodes.Get(2), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(90.0), p2pNodes.Get(3), routingStream);
        Ipv4RoutingHelper::PrintRoutingTableAt(Seconds(90.0), p2pNodes.Get(4), routingStream);
    }
    
    NS_LOG_INFO("Create Applications.");
    uint32_t packetSize = 1024;
    Time interPacketInterval = Seconds(1.0);
    PingHelper ping(Ipv4Address("192.168.20.66"));

    ping.SetAttribute("Interval", TimeValue(interPacketInterval));
    ping.SetAttribute("Size", UintegerValue(packetSize));
    if (showPings)
    {
        ping.SetAttribute("VerboseMode", EnumValue(Ping::VerboseMode::VERBOSE));
    }
    ApplicationContainer apps = ping.Install(markNodes.Get(1));
    apps.Start(Seconds(1.0));
    apps.Stop(Seconds(110.0));

    AsciiTraceHelper ascii;
    csma.EnableAsciiAll(ascii.CreateFileStream("rip-simple-routing.tr"));
    csma.EnablePcapAll("rip-simple-routing", true);

    Simulator::Schedule(Seconds(40), &TearDownLink, p2pNodes.Get(2), p2pNodes.Get(3), 1, 1);

    /* Now, do the actual simulation. */
    NS_LOG_INFO("Run Simulation.");
    Simulator::Stop(Seconds(131.0));
    Simulator::Run();
    Simulator::Destroy();
    NS_LOG_INFO("Done.");
    
    return 0;
}

