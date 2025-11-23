import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import glob

# === TASK 1 COMPREHENSIVE ANALYSIS ===

# Manual PDR and Throughput data calculated from scaler files directly
manual_data = {
    "Hosts": {
        "5": {"PDR": 97.5, "Throughput": 526.5},
        "50": {"PDR": 97.5, "Throughput": 5265},
        "100": {"PDR": 97.5, "Throughput": 10530},
        "250": {"PDR": 76.4, "Throughput": 20617.2},
        "300": {"PDR": 82.0, "Throughput": 26581.5},
        "350": {"PDR": 40.1, "Throughput": 15138.9}
    },
    "Message_Interval": {
        "LOW": {"PDR": 97.5, "Throughput": 49530, "Hosts": 100, "MessageLength": 500, "SendInterval": 1},
        "MEDIUM": {"PDR": 97.5, "Throughput": 98254.8, "Hosts": 100, "MessageLength": 1000, "SendInterval": 1},
        "HIGH": {"PDR": 18.2, "Throughput": 183531.6, "Hosts": 100, "MessageLength": 1000, "SendInterval": 0.1}
    }
}

def analyze_csv_files(folder_path, config_type, config_name):
    """Analyze CSV files in a given folder and return metrics"""
    results = {}
    
    # Find CSV files
    csv_files = glob.glob(os.path.join(folder_path, "*.csv"))
    
    for csv_file in csv_files:
        try:
            df = pd.read_csv(csv_file)
            filename = os.path.basename(csv_file)
            
            if "udpPacketTransmissionInfo" in filename:
                if "Delay" in df.columns:
                    results["End_to_End_Delay"] = {
                        "min": df["Delay"].min(),
                        "max": df["Delay"].max(),
                        "mean": df["Delay"].mean(),
                        "std": df["Delay"].std()
                    }
            
            elif "cwUsed" in filename:
                if "Contetion Size" in df.columns:  # Note: typo in original file
                    results["MAC_Retransmissions"] = {
                        "min": df["Contetion Size"].min(),
                        "max": df["Contetion Size"].max(),
                        "mean": df["Contetion Size"].mean(),
                        "std": df["Contetion Size"].std()
                    }
            
            elif "DataErrorRate" in filename:
                if "Error rate" in df.columns:
                    results["Data_Error_Rate"] = {
                        "min": df["Error rate"].min(),
                        "max": df["Error rate"].max(),
                        "mean": df["Error rate"].mean(),
                        "std": df["Error rate"].std()
                    }
            
            elif "HeaderErrorRate" in filename:
                if "Error rate" in df.columns:
                    results["Header_Error_Rate"] = {
                        "min": df["Error rate"].min(),
                        "max": df["Error rate"].max(),
                        "mean": df["Error rate"].mean(),
                        "std": df["Error rate"].std()
                    }
                    
        except Exception as e:
            print(f"Error reading {csv_file}: {e}")
    
    return results

def create_comprehensive_analysis():
    """Create comprehensive analysis for Task 1"""
    
    # === ANALYSIS 1: Varying Host Count ===
    print("=== ANALYZING HOST COUNT CONFIGURATIONS ===")
    hosts_analysis = {}
    
    for host_count in ["5", "50", "100", "250", "300", "350"]:
        folder_path = f"task_1/Hosts/{host_count}"
        if os.path.exists(folder_path):
            print(f"\nAnalyzing {host_count} hosts...")
            csv_metrics = analyze_csv_files(folder_path, "Hosts", host_count)
            
            # Combine manual data with CSV analysis
            hosts_analysis[host_count] = {
                "Configuration": f"{host_count} Hosts",
                "PDR_Manual": manual_data["Hosts"][host_count]["PDR"],
                "Throughput_Manual": manual_data["Hosts"][host_count]["Throughput"],
                **csv_metrics
            }
    
    # === ANALYSIS 2: Varying Message Length and Send Interval ===
    print("\n=== ANALYZING MESSAGE/INTERVAL CONFIGURATIONS ===")
    message_interval_analysis = {}
    
    for load_type in ["LOW", "MEDIUM", "HIGH"]:
        folder_path = f"task_1/Message, Interval/{load_type}"
        if os.path.exists(folder_path):
            print(f"\nAnalyzing {load_type} load...")
            csv_metrics = analyze_csv_files(folder_path, "Message_Interval", load_type)
            
            # Combine manual data with CSV analysis
            message_interval_analysis[load_type] = {
                "Configuration": f"{load_type} Load",
                "PDR_Manual": manual_data["Message_Interval"][load_type]["PDR"],
                "Throughput_Manual": manual_data["Message_Interval"][load_type]["Throughput"],
                "Hosts": manual_data["Message_Interval"][load_type]["Hosts"],
                "MessageLength_Bytes": manual_data["Message_Interval"][load_type]["MessageLength"],
                "SendInterval_Seconds": manual_data["Message_Interval"][load_type]["SendInterval"],
                **csv_metrics
            }
    
    return hosts_analysis, message_interval_analysis

def create_visualizations(hosts_analysis, message_interval_analysis):
    """Create comprehensive visualizations for Task 1"""
    
    # === CHART 1: Host Count Analysis ===
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(16, 12))
    fig.suptitle('Task 1: Performance Analysis - Varying Host Count', fontsize=16, fontweight='bold')
    
    host_counts = [int(h) for h in hosts_analysis.keys()]
    
    # PDR vs Host Count
    pdr_values = [hosts_analysis[h]["PDR_Manual"] for h in hosts_analysis.keys()]
    ax1.plot(host_counts, pdr_values, marker='o', linestyle='-', color='blue', linewidth=2, markersize=8)
    ax1.set_title('Packet Delivery Ratio (PDR) vs Number of Hosts', fontweight='bold')
    ax1.set_xlabel('Number of Hosts')
    ax1.set_ylabel('PDR (%)')
    ax1.grid(True, alpha=0.3)
    ax1.set_ylim(0, 100)
    
    # Throughput vs Host Count
    throughput_values = [hosts_analysis[h]["Throughput_Manual"] for h in hosts_analysis.keys()]
    ax2.plot(host_counts, throughput_values, marker='s', linestyle='-', color='green', linewidth=2, markersize=8)
    ax2.set_title('Throughput vs Number of Hosts', fontweight='bold')
    ax2.set_xlabel('Number of Hosts')
    ax2.set_ylabel('Throughput (bytes/sec)')
    ax2.grid(True, alpha=0.3)
    
    # End-to-End Delay vs Host Count (if available)
    delay_means = []
    for h in hosts_analysis.keys():
        if "End_to_End_Delay" in hosts_analysis[h]:
            delay_means.append(hosts_analysis[h]["End_to_End_Delay"]["mean"])
        else:
            delay_means.append(0)
    
    if any(d > 0 for d in delay_means):
        ax3.plot(host_counts, delay_means, marker='^', linestyle='-', color='red', linewidth=2, markersize=8)
        ax3.set_title('End-to-End Delay vs Number of Hosts', fontweight='bold')
        ax3.set_xlabel('Number of Hosts')
        ax3.set_ylabel('Delay (seconds)')
        ax3.grid(True, alpha=0.3)
    else:
        ax3.text(0.5, 0.5, 'Delay data not available', ha='center', va='center', transform=ax3.transAxes)
        ax3.set_title('End-to-End Delay vs Number of Hosts', fontweight='bold')
    
    # MAC Retransmissions vs Host Count (if available)
    retransmission_means = []
    for h in hosts_analysis.keys():
        if "MAC_Retransmissions" in hosts_analysis[h]:
            retransmission_means.append(hosts_analysis[h]["MAC_Retransmissions"]["mean"])
        else:
            retransmission_means.append(0)
    
    if any(r > 0 for r in retransmission_means):
        ax4.plot(host_counts, retransmission_means, marker='d', linestyle='-', color='orange', linewidth=2, markersize=8)
        ax4.set_title('MAC Retransmissions vs Number of Hosts', fontweight='bold')
        ax4.set_xlabel('Number of Hosts')
        ax4.set_ylabel('Retransmissions')
        ax4.grid(True, alpha=0.3)
    else:
        ax4.text(0.5, 0.5, 'Retransmission data not available', ha='center', va='center', transform=ax4.transAxes)
        ax4.set_title('MAC Retransmissions vs Number of Hosts', fontweight='bold')
    
    plt.tight_layout()
    plt.savefig('task1_hosts_analysis.png', dpi=300, bbox_inches='tight')
    
    # === CHART 2: Message/Interval Analysis ===
    fig2, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(16, 12))
    fig2.suptitle('Task 1: Performance Analysis - Varying Message Length and Send Interval', fontsize=16, fontweight='bold')
    
    load_types = list(message_interval_analysis.keys())
    x_pos = np.arange(len(load_types))
    
    # PDR vs Load Type
    pdr_values = [message_interval_analysis[lt]["PDR_Manual"] for lt in load_types]
    ax1.plot(x_pos, pdr_values, marker='o', linestyle='-', color='blue', linewidth=2, markersize=8)
    ax1.set_title('Packet Delivery Ratio (PDR) vs Load Type', fontweight='bold')
    ax1.set_xlabel('Load Type')
    ax1.set_ylabel('PDR (%)')
    ax1.set_xticks(x_pos)
    ax1.set_xticklabels(load_types)
    ax1.set_ylim(0, 100)
    
    # Throughput vs Load Type
    throughput_values = [message_interval_analysis[lt]["Throughput_Manual"] for lt in load_types]
    ax2.plot(x_pos, throughput_values, marker='s', linestyle='-', color='green', linewidth=2, markersize=8)
    ax2.set_title('Throughput vs Load Type', fontweight='bold')
    ax2.set_xlabel('Load Type')
    ax2.set_ylabel('Throughput (bytes/sec)')
    ax2.set_xticks(x_pos)
    ax2.set_xticklabels(load_types)
    
    # Message Length vs Load Type
    message_lengths = [message_interval_analysis[lt]["MessageLength_Bytes"] for lt in load_types]
    ax3.plot(x_pos, message_lengths, marker='^', linestyle='-', color='red', linewidth=2, markersize=8)
    ax3.set_title('Message Length vs Load Type', fontweight='bold')
    ax3.set_xlabel('Load Type')
    ax3.set_ylabel('Message Length (bytes)')
    ax3.set_xticks(x_pos)
    ax3.set_xticklabels(load_types)
    
    # Send Interval vs Load Type
    send_intervals = [message_interval_analysis[lt]["SendInterval_Seconds"] for lt in load_types]
    ax4.plot(x_pos, send_intervals, marker='d', linestyle='-', color='orange', linewidth=2, markersize=8)
    ax4.set_title('Send Interval vs Load Type', fontweight='bold')
    ax4.set_xlabel('Load Type')
    ax4.set_ylabel('Send Interval (seconds)')
    ax4.set_xticks(x_pos)
    ax4.set_xticklabels(load_types)
    
    plt.tight_layout()
    plt.savefig('task1_message_interval_analysis.png', dpi=300, bbox_inches='tight')
    
    # === CHART 3: Message/Interval Cumulative Load Analysis ===
    fig3, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(16, 12))
    fig3.suptitle('Task 1: Message/Interval Performance Metrics vs Cumulative Network Load', fontsize=16, fontweight='bold')
    
    # Extract Message/Interval data for cumulative load analysis
    message_interval_loads = []
    message_interval_pdr = []
    message_interval_throughput = []
    message_interval_delay = []
    message_interval_retransmissions = []
    message_interval_labels = []
    
    for load_type, data in message_interval_analysis.items():
        host_count_int = data["Hosts"]
        message_length_bits = data["MessageLength_Bytes"] * 8
        send_interval = data["SendInterval_Seconds"]
        cumulative_load = host_count_int * (message_length_bits / send_interval)
        
        message_interval_loads.append(cumulative_load)
        message_interval_pdr.append(data["PDR_Manual"])
        message_interval_throughput.append(data["Throughput_Manual"])
        message_interval_labels.append(load_type)
        
        # Add delay and retransmission data if available
        if "End_to_End_Delay" in data:
            message_interval_delay.append(data["End_to_End_Delay"]["mean"])
        else:
            message_interval_delay.append(0)
            
        if "MAC_Retransmissions" in data:
            message_interval_retransmissions.append(data["MAC_Retransmissions"]["mean"])
        else:
            message_interval_retransmissions.append(0)
    
    # Sort by cumulative load for better visualization
    sorted_mi_data = sorted(zip(message_interval_loads, message_interval_pdr, message_interval_throughput, 
                                message_interval_delay, message_interval_retransmissions, message_interval_labels))
    sorted_mi_load, sorted_mi_pdr, sorted_mi_throughput, sorted_mi_delay, sorted_mi_retransmissions, sorted_mi_labels = zip(*sorted_mi_data)
    
    # PDR vs Cumulative Network Load (Message/Interval)
    ax1.plot(sorted_mi_load, sorted_mi_pdr, marker='o', linestyle='-', color='blue', linewidth=2, markersize=8)
    ax1.set_title('PDR vs Cumulative Network Load', fontweight='bold')
    ax1.set_xlabel('Cumulative Network Load (bps)')
    ax1.set_ylabel('PDR (%)')
    ax1.grid(True, alpha=0.3)
    ax1.set_ylim(0, 100)
    
    # Add data point annotations
    for i, (load, pdr, label) in enumerate(zip(sorted_mi_load, sorted_mi_pdr, sorted_mi_labels)):
        ax1.annotate(f'{label}\n({pdr:.1f}%)', (load, pdr), textcoords="offset points", 
                     xytext=(0,10), ha='center', fontsize=9, bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))
    
    # Throughput vs Cumulative Network Load (Message/Interval)
    ax2.plot(sorted_mi_load, sorted_mi_throughput, marker='s', linestyle='-', color='green', linewidth=2, markersize=8)
    ax2.set_title('Throughput vs Cumulative Network Load', fontweight='bold')
    ax2.set_xlabel('Cumulative Network Load (bps)')
    ax2.set_ylabel('Throughput (bytes/sec)')
    ax2.grid(True, alpha=0.3)
    
    # Add data point annotations
    for i, (load, throughput, label) in enumerate(zip(sorted_mi_load, sorted_mi_throughput, sorted_mi_labels)):
        ax2.annotate(f'{label}\n({throughput:,.0f})', (load, throughput), textcoords="offset points", 
                     xytext=(0,10), ha='center', fontsize=9, bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))
    
    # End-to-End Delay vs Cumulative Network Load (Message/Interval)
    if any(d > 0 for d in sorted_mi_delay):
        ax3.plot(sorted_mi_load, sorted_mi_delay, marker='^', linestyle='-', color='red', linewidth=2, markersize=8)
        ax3.set_title('End-to-End Delay vs Cumulative Network Load', fontweight='bold')
        ax3.set_xlabel('Cumulative Network Load (bps)')
        ax3.set_ylabel('Delay (seconds)')
        ax3.grid(True, alpha=0.3)
        
        # Add data point annotations
        for i, (load, delay, label) in enumerate(zip(sorted_mi_load, sorted_mi_delay, sorted_mi_labels)):
            ax3.annotate(f'{label}\n({delay:.4f}s)', (load, delay), textcoords="offset points", 
                         xytext=(0,10), ha='center', fontsize=9, bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))
    else:
        ax3.text(0.5, 0.5, 'Delay data not available', ha='center', va='center', transform=ax3.transAxes)
        ax3.set_title('End-to-End Delay vs Cumulative Network Load', fontweight='bold')
    
    # MAC Retransmissions vs Cumulative Network Load (Message/Interval)
    if any(r > 0 for r in sorted_mi_retransmissions):
        ax4.plot(sorted_mi_load, sorted_mi_retransmissions, marker='d', linestyle='-', color='orange', linewidth=2, markersize=8)
        ax4.set_title('MAC Retransmissions vs Cumulative Network Load', fontweight='bold')
        ax4.set_xlabel('Cumulative Network Load (bps)')
        ax4.set_ylabel('Retransmissions')
        ax4.grid(True, alpha=0.3)
        
        # Add data point annotations
        for i, (load, retrans, label) in enumerate(zip(sorted_mi_load, sorted_mi_retransmissions, sorted_mi_labels)):
            ax4.annotate(f'{label}\n({retrans:.1f})', (load, retrans), textcoords="offset points", 
                         xytext=(0,10), ha='center', fontsize=9, bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))
    else:
        ax4.text(0.5, 0.5, 'Retransmission data not available', ha='center', va='center', transform=ax4.transAxes)
        ax4.set_title('MAC Retransmissions vs Cumulative Network Load', fontweight='bold')
    
    plt.tight_layout()
    plt.savefig('task1_message_interval_cumulative_load.png', dpi=300, bbox_inches='tight')
    
    # === CHART 4: Overall Cumulative Network Load Analysis ===
    fig3, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(16, 12))
    fig3.suptitle('Task 1: Performance Metrics vs Cumulative Network Load', fontsize=16, fontweight='bold')
    
    # Combine all data for cumulative load analysis
    all_configs = []
    all_pdr = []
    all_throughput = []
    all_delay = []
    all_retransmissions = []
    all_cumulative_load = []
    
    # Add Host Count data
    for host_count, data in hosts_analysis.items():
        host_count_int = int(host_count)
        message_length_bits = 100 * 8  # 100 bytes = 800 bits
        send_interval = 1  # 1 second
        cumulative_load = host_count_int * (message_length_bits / send_interval)
        
        all_configs.append(f"{host_count} Hosts")
        all_pdr.append(data["PDR_Manual"])
        all_throughput.append(data["Throughput_Manual"])
        all_cumulative_load.append(cumulative_load)
        
        # Add delay and retransmission data if available
        if "End_to_End_Delay" in data:
            all_delay.append(data["End_to_End_Delay"]["mean"])
        else:
            all_delay.append(0)
            
        if "MAC_Retransmissions" in data:
            all_retransmissions.append(data["MAC_Retransmissions"]["mean"])
        else:
            all_retransmissions.append(0)
    
    # Add Message/Interval data
    for load_type, data in message_interval_analysis.items():
        host_count_int = data["Hosts"]
        message_length_bits = data["MessageLength_Bytes"] * 8
        send_interval = data["SendInterval_Seconds"]
        cumulative_load = host_count_int * (message_length_bits / send_interval)
        
        all_configs.append(f"{load_type} Load")
        all_pdr.append(data["PDR_Manual"])
        all_throughput.append(data["Throughput_Manual"])
        all_cumulative_load.append(cumulative_load)
        
        # Add delay and retransmission data if available
        if "End_to_End_Delay" in data:
            all_delay.append(data["End_to_End_Delay"]["mean"])
        else:
            all_delay.append(0)
            
        if "MAC_Retransmissions" in data:
            all_retransmissions.append(data["MAC_Retransmissions"]["mean"])
        else:
            all_retransmissions.append(0)
    
    # Sort by cumulative load for better visualization
    sorted_data = sorted(zip(all_cumulative_load, all_pdr, all_throughput, all_delay, all_retransmissions, all_configs))
    sorted_load, sorted_pdr, sorted_throughput, sorted_delay, sorted_retransmissions, sorted_configs = zip(*sorted_data)
    
    # PDR vs Cumulative Network Load
    ax1.plot(sorted_load, sorted_pdr, marker='o', linestyle='-', color='blue', linewidth=2, markersize=8)
    ax1.set_title('PDR vs Cumulative Network Load', fontweight='bold')
    ax1.set_xlabel('Cumulative Network Load (bps)')
    ax1.set_ylabel('PDR (%)')
    ax1.grid(True, alpha=0.3)
    ax1.set_ylim(0, 100)
    
    # Throughput vs Cumulative Network Load
    ax2.plot(sorted_load, sorted_throughput, marker='s', linestyle='-', color='green', linewidth=2, markersize=8)
    ax2.set_title('Throughput vs Cumulative Network Load', fontweight='bold')
    ax2.set_xlabel('Cumulative Network Load (bps)')
    ax2.set_ylabel('Throughput (bytes/sec)')
    ax2.grid(True, alpha=0.3)
    
    # End-to-End Delay vs Cumulative Network Load
    if any(d > 0 for d in sorted_delay):
        ax3.plot(sorted_load, sorted_delay, marker='^', linestyle='-', color='red', linewidth=2, markersize=8)
        ax3.set_title('End-to-End Delay vs Cumulative Network Load', fontweight='bold')
        ax3.set_xlabel('Cumulative Network Load (bps)')
        ax3.set_ylabel('Delay (seconds)')
        ax3.grid(True, alpha=0.3)
    else:
        ax3.text(0.5, 0.5, 'Delay data not available', ha='center', va='center', transform=ax3.transAxes)
        ax3.set_title('End-to-End Delay vs Cumulative Network Load', fontweight='bold')
    
    # MAC Retransmissions vs Cumulative Network Load
    if any(r > 0 for r in sorted_retransmissions):
        ax4.plot(sorted_load, sorted_retransmissions, marker='d', linestyle='-', color='orange', linewidth=2, markersize=8)
        ax4.set_title('MAC Retransmissions vs Cumulative Network Load', fontweight='bold')
        ax4.set_xlabel('Cumulative Network Load (bps)')
        ax4.set_ylabel('Retransmissions')
        ax4.grid(True, alpha=0.3)
    else:
        ax4.text(0.5, 0.5, 'Retransmission data not available', ha='center', va='center', transform=ax4.transAxes)
        ax4.set_title('MAC Retransmissions vs Cumulative Network Load', fontweight='bold')
    
    plt.tight_layout()
    plt.savefig('task1_cumulative_load_analysis.png', dpi=300, bbox_inches='tight')
    
    plt.show()

def create_summary_csv(hosts_analysis, message_interval_analysis):
    """Create comprehensive summary CSV with all metrics"""
    
    # Prepare data for CSV
    summary_data = []
    
    # Add Host Count Analysis
    for host_count, data in hosts_analysis.items():
        # Calculate Cumulative Network Load (bps)
        host_count_int = int(host_count)
        message_length_bits = 100 * 8  # 100 bytes = 800 bits
        send_interval = 1  # 1 second
        cumulative_load = host_count_int * (message_length_bits / send_interval)
        
        row = {
            "Configuration_Type": "Host_Count",
            "Configuration_Name": data["Configuration"],
            "Host_Count": host_count_int,
            "PDR_Manual": data["PDR_Manual"],
            "Throughput_Manual": data["Throughput_Manual"],
            "Message_Length_Bytes": 100,  # Fixed for host count analysis
            "Send_Interval_Seconds": 1,   # Fixed for host count analysis
            "Cumulative_Network_Load_bps": cumulative_load
        }
        
        # Add CSV-derived metrics if available
        if "End_to_End_Delay" in data:
            row.update({
                "Delay_Min": data["End_to_End_Delay"]["min"],
                "Delay_Max": data["End_to_End_Delay"]["max"],
                "Delay_Mean": data["End_to_End_Delay"]["mean"],
                "Delay_Std": data["End_to_End_Delay"]["std"]
            })
        
        if "MAC_Retransmissions" in data:
            row.update({
                "Retransmissions_Min": data["MAC_Retransmissions"]["min"],
                "Retransmissions_Max": data["MAC_Retransmissions"]["max"],
                "Retransmissions_Mean": data["MAC_Retransmissions"]["mean"],
                "Retransmissions_Std": data["MAC_Retransmissions"]["std"]
            })
        
        if "Data_Error_Rate" in data:
            row.update({
                "Data_Error_Min": data["Data_Error_Rate"]["min"],
                "Data_Error_Max": data["Data_Error_Rate"]["max"],
                "Data_Error_Mean": data["Data_Error_Rate"]["mean"],
                "Data_Error_Std": data["Data_Error_Rate"]["std"]
            })
        
        if "Header_Error_Rate" in data:
            row.update({
                "Header_Error_Min": data["Header_Error_Rate"]["min"],
                "Header_Error_Max": data["Header_Error_Rate"]["max"],
                "Header_Error_Mean": data["Header_Error_Rate"]["mean"],
                "Header_Error_Std": data["Header_Error_Rate"]["std"]
            })
        
        summary_data.append(row)
    
    # Add Message/Interval Analysis
    for load_type, data in message_interval_analysis.items():
        # Calculate Cumulative Network Load (bps)
        host_count_int = data["Hosts"]
        message_length_bits = data["MessageLength_Bytes"] * 8  # Convert bytes to bits
        send_interval = data["SendInterval_Seconds"]
        cumulative_load = host_count_int * (message_length_bits / send_interval)
        
        row = {
            "Configuration_Type": "Message_Interval",
            "Configuration_Name": data["Configuration"],
            "Host_Count": host_count_int,
            "PDR_Manual": data["PDR_Manual"],
            "Throughput_Manual": data["Throughput_Manual"],
            "Message_Length_Bytes": data["MessageLength_Bytes"],
            "Send_Interval_Seconds": data["SendInterval_Seconds"],
            "Cumulative_Network_Load_bps": cumulative_load
        }
        
        # Add CSV-derived metrics if available
        if "End_to_End_Delay" in data:
            row.update({
                "Delay_Min": data["End_to_End_Delay"]["min"],
                "Delay_Max": data["End_to_End_Delay"]["max"],
                "Delay_Mean": data["End_to_End_Delay"]["mean"],
                "Delay_Std": data["End_to_End_Delay"]["std"]
            })
        
        if "MAC_Retransmissions" in data:
            row.update({
                "Retransmissions_Min": data["MAC_Retransmissions"]["min"],
                "Retransmissions_Max": data["MAC_Retransmissions"]["max"],
                "Retransmissions_Mean": data["MAC_Retransmissions"]["mean"],
                "Retransmissions_Std": data["MAC_Retransmissions"]["std"]
            })
        
        if "Data_Error_Rate" in data:
            row.update({
                "Data_Error_Min": data["Data_Error_Rate"]["min"],
                "Data_Error_Max": data["Data_Error_Rate"]["max"],
                "Data_Error_Mean": data["Data_Error_Rate"]["mean"],
                "Data_Error_Std": data["Data_Error_Rate"]["std"]
            })
        
        if "Header_Error_Rate" in data:
            row.update({
                "Header_Error_Min": data["Header_Error_Rate"]["min"],
                "Header_Error_Max": data["Header_Error_Rate"]["max"],
                "Header_Error_Mean": data["Header_Error_Rate"]["mean"],
                "Header_Error_Std": data["Header_Error_Rate"]["std"]
            })
        
        summary_data.append(row)
    
    # Create DataFrame and save
    summary_df = pd.DataFrame(summary_data)
    summary_df.to_csv('task1_comprehensive_summary.csv', index=False)
    
    print(f"\n✅ Comprehensive summary saved to 'task1_comprehensive_summary.csv'")
    print(f"📊 Summary contains {len(summary_df)} configurations with all metrics")
    
    return summary_df

def main():
    """Main execution function"""
    print("🚀 Starting Task 1 Comprehensive Analysis...")
    
    # Perform analysis
    hosts_analysis, message_interval_analysis = create_comprehensive_analysis()
    
    # Create visualizations
    print("\n📈 Creating visualizations...")
    create_visualizations(hosts_analysis, message_interval_analysis)
    
    # Create summary CSV
    print("\n💾 Creating comprehensive summary CSV...")
    summary_df = create_summary_csv(hosts_analysis, message_interval_analysis)
    
    # Display summary
    print("\n📋 ANALYSIS SUMMARY:")
    print("=" * 50)
    
    print("\n🏠 HOST COUNT ANALYSIS:")
    for host_count, data in hosts_analysis.items():
        print(f"  {host_count} Hosts: PDR={data['PDR_Manual']:.1f}%, Throughput={data['Throughput_Manual']:,.0f} bytes/sec")
    
    print("\n📨 MESSAGE/INTERVAL ANALYSIS:")
    for load_type, data in message_interval_analysis.items():
        print(f"  {load_type}: PDR={data['PDR_Manual']:.1f}%, Throughput={data['Throughput_Manual']:,.0f} bytes/sec")
        print(f"    Config: {data['Hosts']} hosts, {data['MessageLength_Bytes']}B, {data['SendInterval_Seconds']}s interval")
    
    print("\n✅ Analysis complete! Check the generated files:")
    print("  - task1_hosts_analysis.png")
    print("  - task1_message_interval_analysis.png")
    print("  - task1_message_interval_cumulative_load.png")
    print("  - task1_cumulative_load_analysis.png")
    print("  - task1_comprehensive_summary.csv")

if __name__ == "__main__":
    main() 